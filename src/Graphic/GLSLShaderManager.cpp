#include <Graphic/GLSLShaderManager.h>
#include <iostream>
#include <GL/glew.h>
#include <vector>

namespace cac
{
    GLSLShaderManager::GLSLShaderManager()
    {
        setAttribLocations();
    }

    GLSLShaderManager::~GLSLShaderManager()
    {
	unload();
    }

    void GLSLShaderManager::unload()
    {
	for (auto iterator = shaderPrograms.begin(); iterator != shaderPrograms.end(); iterator++)
        {
            glDeleteProgram(iterator->second);
        }
        
        shaderPrograms.clear();
    }
    void GLSLShaderManager::setAttribLocations()
    {
        vertexAttribLocations["vertex"] = 0;
        vertexAttribLocations["uv"] = 1;
        vertexAttribLocations["color"] = 2;
        vertexAttribLocations["textureRectangle"] = 3;
        vertexAttribLocations["MVP"] = 4;

    }
    bool GLSLShaderManager::createProgram(std::string programName, std::string vertexShader, std::string fragmentShader, std::string geometryShader)
    {
        GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        GLuint geometryShaderId = 0;
        if(geometryShader != "")
             geometryShaderId = glCreateShader(GL_GEOMETRY_SHADER);
	
        if(!compileShader(vertexShaderId, vertexShader))
            return false;
        if(!compileShader(fragmentShaderId, fragmentShader))
            return false;
        if(geometryShaderId && !compileShader(fragmentShaderId, geometryShader))
            return false;
       
	// Link the program
	GLint result = GL_FALSE;
	int infolength;

	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderId);
	glAttachShader(programID, fragmentShaderId);


	for(auto iterator = vertexAttribLocations.begin(); iterator!=vertexAttribLocations.end(); iterator++)
	{
	    glBindAttribLocation(programID, iterator->second, iterator->first.c_str());
	}

	glLinkProgram(programID);

	// Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);

	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infolength);
	if (infolength > 0){
	    std::vector<char> ProgramErrorMessage(infolength + 1);
	    glGetProgramInfoLog(programID, infolength, NULL, &ProgramErrorMessage[0]);
	    std::cout << &ProgramErrorMessage[0]  << std::endl;;
	}

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	shaderPrograms[programName] = programID;
	return true;
        
    }


    bool  GLSLShaderManager::compileShader(GLuint shaderId, std::string shaderCode)
    {
        if(shaderCode == "")
            return false;

        char const * shaderSourcePointer = shaderCode.c_str();
        GLint result = GL_FALSE;
        int infolength;

        glShaderSource(shaderId, 1, &shaderSourcePointer, NULL);
        glCompileShader(shaderId);

        // Check Vertex Shader
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infolength);
        if (infolength > 0){
            std::vector<char> shaderErrorMessage(infolength + 1);
            glGetShaderInfoLog(shaderId, infolength, NULL, &shaderErrorMessage[0]);
            std::cout << &shaderErrorMessage[0] << std::endl;
        }

        return true;
    }


}