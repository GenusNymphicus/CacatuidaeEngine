#ifndef CACATUIDAE_GRAPHICS_RENDER_ENGINE_H
#define CACATUIDAE_GRAPHICS_RENDER_ENGINE_H

#include "IWindow.h"
#include "Renderable.h"

namespace cac 
{
    template<class Renderer> class RenderEngine 
    {
    public:
	bool initialize(WindowDesc windowDescription);
	
	void clearScreen();
	void updateScreen();
	
	//texture, position, size, rotation, technique related informations  / rendertechnique
	void render2D(Renderable renderable, std::string program);
	//void loadResource(IResource resource);
	
    private:
	Renderer renderer;
    };
}

// Required due the template class. Needed to avoid "unresolved references" linking errors.
#include "Graphic/RenderEngine.cpp"

#endif