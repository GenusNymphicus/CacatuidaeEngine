/** \addtogroup Graphic
 *  @{
 */

#ifndef CACATUIDAE_GRAPHICS_IRENDERER_H
#define CACATUIDAE_GRAPHICS_IRENDERER_H

#include <string>
#include "IWindow.h"
#include "GraphicStructs.h"
#include "Renderable.h"
#include "Camera.h"
namespace cac
{	    
	
	/** Interface for the renderer-implementations
	*  Provides an interface for the
	*  various renderer-implementations. A Renderer 
	*  is the interface between the GraphicsLibraries(OpenGL, DirectX, ..)
	*  and the outside. Ideally, no other file will contains the 
	*  graphicslibrary-specific code, except for the renderer-implementations.
	*/
	class IRenderer
	{
	public:
	    /** Initialization of the graphics-library
	     *  Requires a window as context. 
	     * 
	     *  @throws ErrorMessage
	     *  @returns 0 for success or an error code
	     */
	    virtual int initialize(WindowDesc windowDesc) = 0;
	    virtual void updateContext(WindowDesc windowDesc) = 0;
	    
	    virtual std::string getErrorMessage(int errorCode) = 0;
	    virtual bool createMesh(std::string name, std::vector<Vertex> vertices, std::vector<short> indices) = 0;
	    virtual bool createShaderProgram(std::string programName, std::string vertexShader, std::string fragmentShader, std::string geometryShader ="") = 0; 
	    virtual bool createTexture(std::string textureName, int width, int height, std::vector<char> data,  bool hasAlpha = false) = 0;
	    virtual bool createTexture(std::string textureName, int width, int height, std::vector<char> data,  int numChannels) = 0;
	    virtual void swapBuffers() = 0;
	    virtual void setClearColor(float r, float g, float b)=0;
	    virtual void clearBuffers()=0;
	    virtual void render(const Renderable& renderable) = 0;
	    virtual void bindShaderProgram(std::string program) = 0;
	    virtual void bindTexture(std::string texture) = 0;
	    virtual void setWireFrame(bool wireframe) = 0;
	   
	    void setCamera(Camera* camera) { activeCamera = camera; }
	protected:
	    Camera* activeCamera;
	    
	    
	};
}

#endif

/** @}*/
