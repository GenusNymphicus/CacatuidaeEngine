#include "Graphics/RenderEngine.h"
#include <Graphics/Camera.h>
#include <iostream>


template<class Renderer> bool cac::RenderEngine<Renderer>::initialize(cac::WindowDesc windowDescription)
{
    return renderer.initialize(windowDescription);
}

template<class Renderer> void cac::RenderEngine<Renderer>::setShaderAttributeLocation(std::string name, int location)
{
    renderer.setShaderAttributeLocation(name, location);
}

template<class Renderer> void cac::RenderEngine<Renderer>::clearScreen()
{
    renderer.clearBuffers();
}

template<class Renderer> void cac::RenderEngine<Renderer>::clearScreen(float r, float g, float b)
{
    renderer.setClearColor(r, g, b);
    renderer.clearBuffers();
}
template<class Renderer> void cac::RenderEngine<Renderer>::render(const cac::Renderable& renderable)
{
    render(renderable, defaultRenderTechnique);
}

template<class Renderer> void cac::RenderEngine<Renderer>::render(const cac::Renderable& renderable, cac::RenderTechnique renderTechnique)
{
    short numberOfPasses = renderTechnique.getNumberOfRenderpasses();
    for(short currentPass = 0; currentPass<numberOfPasses; currentPass++)
    {
	renderer.bindShaderProgram(renderTechnique.getRenderpass(currentPass));
	renderer.render(renderable);
    }
}

template<class Renderer> void cac::RenderEngine<Renderer>::render(const cac::Text& text)
{
    render(text, defaultTextTechnique);
}
template<class Renderer> void cac::RenderEngine<Renderer>::render(const cac::Text& text, cac::RenderTechnique renderTechnique)
{
    cac::Renderable renderable;
    renderable.mesh = text.mesh;
    if(!fontResources.count(text.font))
    {
	std::cout<<"Font "<<text.font<<" not loaded!"<<std::endl;
	return;
    }
    const FontResource& font = fontResources[text.font];
    
    float advanceX = text.posX;
    float advanceY = text.posY;
    
    //TODO: [PERFORMANCE] caching for the texts.
    for(int i = 0; i<text.textString.size(); i++)
    {
	const GlyphInformation& glyph = font.glyphs.at(text.textString[i]);
	float textureX = (float)glyph.textureX / font.textureWidth;

	renderable.texture = font.name;
	renderable.posX = advanceX + glyph.bitmapLeft + textureX;
	renderable.posY = advanceY + font.textureHeight - glyph.bitmapTop;
	renderable.posZ = text.posZ;
	
	renderable.scaleX = text.scaleX * glyph.bitmapWidth;
	renderable.scaleY = text.scaleY * glyph.bitmapHeight;
	renderable.scaleZ = text.scaleZ;
	
	renderable.texRectX = textureX * text.scaleX;
	renderable.texRectY = 0;
	renderable.texRectWidth = (float) glyph.bitmapWidth / font.textureWidth;
	renderable.texRectHeight = (float) glyph.bitmapHeight / font.textureHeight;
	
	renderable.setColor(text.colorR, text.colorG, text.colorB, text.colorA);
	advanceX += glyph.advanceX;
	
	render(renderable, renderTechnique);
    }
    
    short numberOfPasses = renderTechnique.getNumberOfRenderpasses();
    for(short currentPass = 0; currentPass<numberOfPasses; currentPass++)
    {
	renderer.bindShaderProgram(renderTechnique.getRenderpass(currentPass));
	renderer.render(renderable);
    }
}

template<class Renderer> bool cac::RenderEngine<Renderer>::loadTexture(TextureResource resource)
{
    if(textureResources.count(resource.name) == 0)
    {
	textureResources[resource.name] = resource;
	return renderer.createTexture(resource.name, resource.width, resource.height, resource.data, resource.hasAlpha);
    }
    else 
    {
	std::cout<<"Texture "<<resource.name<<" already loaded!"<<std::endl;
	return false;
    }
}
template<class Renderer> bool cac::RenderEngine<Renderer>::loadFont(FontResource resource)
{
    if(fontResources.count(resource.name) == 0)
    {
	fontResources[resource.name] = resource;
	
	return renderer.createTexture(resource.name, resource.textureWidth, resource.textureHeight, resource.data, 1);

    }
    else 
    {
	std::cout<<"Font "<<resource.name<<" already loaded!"<<std::endl;
	return false;
    }
}


template<class Renderer> bool cac::RenderEngine<Renderer>::loadShaderProgram(cac::ShaderResource resource)
{
    if(shaderResources.count(resource.name) == 0)
    {
	shaderResources[resource.name] = resource;
	return renderer.createShaderProgram(resource.name, resource.vertexShader, resource.fragmentShader, resource.geometryShader);
    }
    else 
    {
	std::cout<<"Shader "<<resource.name<<" already loaded!"<<std::endl;
	return false;
    }
}

template<class Renderer> bool cac::RenderEngine<Renderer>::loadMesh(cac::MeshResource resource)
{
    if(meshResources.count(resource.name) == 0)
    {
	meshResources[resource.name] = resource;
	return renderer.createMesh(resource.name, resource.vertices, resource.indices);
    }
    else 
    {
	std::cout<<"Mesh "<<resource.name<<" already loaded!"<<std::endl;
	return false;
    }
}

template<class Renderer> void cac::RenderEngine<Renderer>::setCamera(cac::Camera& cam) 
{
    renderer.setCamera(cam); 
}

template<class Renderer> void cac::RenderEngine<Renderer>::updateScreen()
{
    renderer.swapBuffers();
}

template<class Renderer> void cac::RenderEngine<Renderer>::setDefaultRenderTechnique(cac::RenderTechnique technique)
{
    defaultRenderTechnique = technique;
}

template<class Renderer> void cac::RenderEngine<Renderer>::setDefaultTextTechnique(cac::RenderTechnique technique)
{
    defaultTextTechnique = technique;
}

