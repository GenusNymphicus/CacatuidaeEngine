#ifndef CACATUIDAE_GRAPHICS_RENDER_ENGINE_H
#define CACATUIDAE_GRAPHICS_RENDER_ENGINE_H

#include <map>

#include "IWindow.h"
#include "Renderable.h"
#include "RenderTechnique.h"
#include "TextureResource.h"

namespace cac 
{
    template<class Renderer> class RenderEngine 
    {
    public:
	bool initialize(WindowDesc windowDescription);
	
	void clearScreen();
	void updateScreen();
	//texture, position, size, rotation, technique related informations  / rendertechnique
	void render(Renderable renderable, RenderTechnique renderTechnique);
	bool loadTexture(TextureResource resource);

	void unloadTexture(std::string name);

    private:
	Renderer renderer;
	std::map<std::string, TextureResource> textureResources;
    };
}

// Required due the template class. Needed to avoid "unresolved references" linking errors.
#include "Graphic/RenderEngine.cpp"

#endif