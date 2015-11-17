#include "Graphic/RenderEngine.h"
#include <iostream>


template<class Renderer> bool cac::RenderEngine<Renderer>::initialize(cac::WindowDesc windowDescription)
{
    return renderer.initialize(windowDescription) == 0;
}

template<class Renderer> void cac::RenderEngine<Renderer>::clearScreen()
{
    renderer.clearScreen();
}

template<class Renderer> void cac::RenderEngine<Renderer>::render(cac::Renderable renderable, cac::RenderTechnique renderTechnique)
{

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

template<class Renderer> void cac::RenderEngine<Renderer>::updateScreen()
{
    renderer.swapBuffers();
}
