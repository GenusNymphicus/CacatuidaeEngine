/** \addtogroup Graphic
 *  @{
 */

#ifndef CACATUIDAE_GRAPHICS_GLSLSHADERMANAGER_H
#define CACATUIDAE_GRAPHICS_GLSLSHADERMANAGER_H

#include <string>
#include <map>
#include <GL/glew.h>

namespace cac
{	    
	class GLSLShaderManager
	{
	public:
	    GLSLShaderManager();
	    ~GLSLShaderManager();
	    void unload();
		
	    bool createProgram(std::string programName, std::string vertexShader, std::string fragmentShader, std::string geometryShader = "");
	    
	    GLuint getShaderProgram(std::string programName) { return shaderPrograms[programName]; }
	    GLuint getAttribLocation(std::string attribName) { return vertexAttribLocations[attribName]; }
	    
	private:
	    void setAttribLocations();
	    bool compileShader(GLuint shaderID, std::string shaderCode);
	    
	    std::map<std::string, GLuint> shaderPrograms;
	    std::map<std::string, GLuint> vertexAttribLocations;
	};
}

#endif

/** @}*/
