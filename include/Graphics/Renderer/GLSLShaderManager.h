/** \addtogroup Renderer
 *  \ingroup Graphics
 *  @{
 */

#ifndef CACATUIDAE_GRAPHICS_GLSL_SHADERMANAGER_H
#define CACATUIDAE_GRAPHICS_GLSL_SHADERMANAGER_H

#include <string>
#include <map>
#include <GL/glew.h>

namespace cac
{	    
        /** Manages the GLSL Shaderprograms
	* Offers services to generate the shaderPrograms by providing the
	* shaderSources, defines the attributelocations and manages the lifetime
	* of the shaderprograms.  
	* @sa OGLRenderer 
	*/
 
	class GLSLShaderManager
	{
	public:
	    ~GLSLShaderManager();
	    
	    /** Release all allocated Resources by the shaders
	    * Unloads all loaded shaders by calling glDeleteProgram
	    */
	    void unload();
		
	    /** Create the shaderProgram
	    * Links the vertex, fragment and geometry shadersources into
	    * a shader program, which can be referenced to with the programName.
	    *
	    * @param[in] programName Name of the shader program 
	    * @param[in] vertexShader vertexShader source code
	    * @param[in] fragmentShader fragmentShader source code
	    * @param[in] geometryShader Optional: geometryShader source code
	    * 
	    * @return true for success, false for failure.
	    */
	    bool createProgram(std::string programName, std::string vertexShader, std::string fragmentShader, std::string geometryShader = "");
	    
	    /** Return the shaderprogram ID
	     * @param[in] programName Name of the program
	     * @return the programID given by OpenGL
	    */	    
	    GLuint getShaderProgram(std::string programName) { return shaderPrograms[programName]; }
	
	    /** Set the vertex attribute locations
	    * Binds the name to a specific location. 
	    * Needed to allow the use of multiple shaders without knowing
	    * the exactly order of the attribute Locations.
	    * 
	    * @param[in] name Name of the attribute
	    * @param[in] location location of the attribute
	    */
	    void setAttribLocation(std::string name, int location);

	    /** Return the attribute location
	     * @param[in] attribName Name of the attribute
	     * @return the location of the vertex attribute
	    */	   
	    GLuint getAttribLocation(std::string attribName) { return vertexAttribLocations[attribName]; }
	
	private:
	    bool compileShader(GLuint shaderID, std::string shaderCode);
	    
	    std::map<std::string, GLuint> shaderPrograms;  /*!< the compiled and linked shader programs */
	    std::map<std::string, GLuint> vertexAttribLocations; /*!< the definded vertex attribute locations */
 
	};
}

#endif

/** @}*/
