#ifndef CACATUIDAE_GRAPHICS_RENDER_ENGINE_H
#define CACATUIDAE_GRAPHICS_RENDER_ENGINE_H

#include <map>

#include "IWindow.h"
#include "Renderable.h"
#include "Text.h"
#include "Font.h"
#include "RenderTechnique.h"
#include "TextureResource.h"
#include "FontResource.h"
#include "ShaderResource.h"
#include "MeshResource.h"

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
	
	//texture, position, size, rotation, technique related informations  / rendertechnique
	void render(const cac::Renderable& renderable, cac::RenderTechnique renderTechnique);
	void render(const cac::Text& text, cac::RenderTechnique renderTechnique);
	bool loadTexture(TextureResource resource);
	bool loadShaderProgram(ShaderResource resource);
	bool loadMesh(MeshResource mesh);
	bool loadFont(FontResource);
	
	void setCamera(Camera* camera);
	
	void unloadTexture(std::string name);
	
    private:
	Renderer renderer;
	std::map<std::string, MeshResource> meshResources;
	std::map<std::string, TextureResource> textureResources;
	std::map<std::string, FontResource> fontResources;
	std::map<std::string, ShaderResource> shaderResources;
	
//	std::map<std::string, Font> fonts;
	
    };
}

// Required due the template class. Needed to avoid "unresolved references" linking errors.
#include "Graphic/RenderEngine.cpp"

#endif