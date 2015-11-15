/** \addtogroup Graphic
 *  @{
 */

#ifndef CACATUIDAE_GRAPHICS_OGLRENDERER_H
#define CACATUIDAE_GRAPHICS_OGLRENDERER_H

#include <vector>
#include "IRenderer.h"
#include "OGLWindow.h"
#include "GLSLShaderManager.h"
#include "OGLMesh.h"
#include "OGLTexture.h"

namespace cac
{	
    /** Implementation of the OpenGL-renderer
    *   
    */
    class OGLRenderer : public IRenderer
    {
    public:
	/** Initialization of the graphics-library
	* 
	* @praram window reference to window object
	* @returns 0 for success or an error code
	* @sa getErrorMessage
	*/
	virtual ~OGLRenderer();
	
	virtual int initialize (WindowDesc windowDesc) override;
	virtual void updateContext(WindowDesc windowDesc) override;
	
	virtual std::string getErrorMessage(int errorCode);
	virtual bool createMesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices = std::vector<unsigned int>());
	virtual bool createShaderProgram(std::string programName, std::string vertexShader, std::string fragmentShader, std::string geometryShader =""); 
	virtual bool createTexture(std::string textureName, int width, int height, std::vector<char> data,  bool hasAlpha = false);
	virtual void swapBuffers(); 
	virtual void setClearColor(float r, float g, float b);
	virtual void clearBuffers();
	virtual void render(const Renderable& renderable);
	virtual void bindShaderProgram(std::string program);
	virtual void bindTexture(std::string texture);
	virtual void setWireFrame(bool wireframe);
	
	void unloadResources();
    private:
	OGLWindow window;
	GLSLShaderManager shaderManager;
	std::map<std::string, OGLMesh> meshes;
	std::map<std::string, OGLTexture> textures;
	GLuint boundShaderProgram = 0;
    };
    
}

#endif

/** @}*/
