#ifndef CACATUIDAE_GRAPHICS_RENDER_TECHNIQUE_H
#define CACATUIDAE_GRAPHICS_RENDER_TECHNIQUE_H

#include <vector>

namespace cac 
{
    class IRenderer;
    class RenderTechnique 
    {
    public:
	void addRenderpass(std::string name) { renderPasses.push_back(name); }
	std::string getRenderpass(short index) { return renderPasses[index]; }
	short getNumberOfRenderpasses() { return renderPasses.size(); }
	
    private:
	std::vector<std::string> renderPasses;
    };
}

#endif