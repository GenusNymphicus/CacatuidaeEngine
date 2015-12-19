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
	
	virtual bool initialize (WindowDesc windowDesc) override;
	virtual bool updateContext(WindowDesc windowDesc) override;

	virtual bool createMesh(std::string name, std::vector<Vertex> vertices, std::vector<short> indices = std::vector<short>()) override;
	virtual bool createShaderProgram(std::string programName, std::string vertexShader, std::string fragmentShader, std::string geometryShader ="") override; 
	virtual bool createTexture(std::string textureName, int width, int height, std::vector<unsigned char> data,  bool hasAlpha = false) override;
	virtual bool createTexture(std::string textureName, int width, int height, std::vector<unsigned char> data,  int numChannels) override;
	virtual void swapBuffers() override; 
	virtual void setClearColor(float r, float g, float b) override;
	virtual void clearBuffers() override;
	virtual void render(const Renderable& renderable) override;
	virtual bool bindShaderProgram(std::string program) override;
	virtual bool bindTexture(std::string texture) override;
	virtual void setWireframe(bool wireframe) override;
	virtual bool setShaderAttributeLocation(std::string name, int location) override;
	virtual void setDepthTest(ETestMethod testMethod) override;
	
	virtual IWindow* getWindow();
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
