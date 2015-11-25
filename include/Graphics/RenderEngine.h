#ifndef CACATUIDAE_GRAPHICS_RENDER_ENGINE_H
#define CACATUIDAE_GRAPHICS_RENDER_ENGINE_H

#include <map>

#include "Renderer/IWindow.h"
#include "Renderable.h"
#include "Text.h"
#include "Font.h"
#include "RenderTechnique.h"
#include "Core/Resources/TextureResource.h"
#include "Core/Resources/FontResource.h"
#include "Core/Resources/ShaderResource.h"
#include "Core/Resources/MeshResource.h"

namespace cac 
{
    class Camera;
    template<class Renderer> class RenderEngine 
    {
    public:
	bool initialize(WindowDesc windowDescription);
	
	void clearScreen();
	void clearScreen(float r, float g, float b);
	void updateScreen();
	
	void render(const cac::Renderable& renderable);
	void render(const cac::Renderable& renderable, cac::RenderTechnique renderTechnique);
	
	void render(const cac::Text& text);
	void render(const cac::Text& text, cac::RenderTechnique renderTechnique);
	
	bool loadTexture(TextureResource resource);
	bool loadShaderProgram(ShaderResource resource);
	bool loadMesh(MeshResource mesh);
	bool loadFont(FontResource);
	void setShaderAttributeLocation(std::string name, int location);
	
	void setDefaultRenderTechnique(RenderTechnique technique);
	void setDefaultTextTechnique(RenderTechnique technique);
	void setCamera(Camera& camera);
	
	void unloadTexture(std::string name);
	
	IWindow* getWindow();
	
	
    private:
	Renderer renderer;
	std::map<std::string, MeshResource> meshResources;
	std::map<std::string, TextureResource> textureResources;
	std::map<std::string, FontResource> fontResources;
	std::map<std::string, ShaderResource> shaderResources;
	
	RenderTechnique defaultRenderTechnique;
	RenderTechnique defaultTextTechnique;
    };
}

// Required due the template class. Needed to avoid "unresolved references" linking errors.
#include "Graphics/RenderEngine.cpp"

#endif