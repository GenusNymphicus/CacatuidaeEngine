#include "Graphics/Renderer/OGLRenderer.h"

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Graphics/Renderer/IWindow.h"
#include "Graphics/Camera.h"

#include <fstream>
cac::OGLRenderer::~OGLRenderer()
{
    unloadResources();
}

void cac::OGLRenderer::unloadResources()
{
    for(auto& texture : textures)
    {
	glDeleteTextures(1, &texture.second.textureId);
	texture.second.textureId = 0;
    }
    
    for(auto& mesh : meshes)
    {
	glDeleteBuffers(1, &mesh.second.mvp);
	glDeleteBuffers(1, &mesh.second.color);
	glDeleteBuffers(1, &mesh.second.vbo);
	glDeleteBuffers(1, &mesh.second.ibo);
	glDeleteBuffers(1, &mesh.second.vao);
	
	mesh.second.mvp = 0;
	mesh.second.color = 0;
	mesh.second.vbo = 0;
	mesh.second.ibo = 0;
	mesh.second.vao = 0;
    }
    
    shaderManager.unload();
}

void cac::OGLRenderer::setDepthTest(ETestMethod testMethod)
{
  switch(testMethod)
  {
    case (ETestMethod::ACCEPT_NONE): {   glDepthFunc(GL_NEVER);  break; }
    case (ETestMethod::ACCEPT_LESS): {    glDepthFunc(GL_LESS); break; }
    case (ETestMethod::ACCEPT_ALL): {   glDepthFunc(GL_ALWAYS); break; }
    default:  glDepthFunc(GL_ALWAYS);
      
  };
}


bool cac::OGLRenderer::initialize(WindowDesc windowDesc)
{
    if(!window.initialize(windowDesc))
	return false;
    
        // Enable depth test
    glEnable(GL_DEPTH_TEST);

//     enable Transparency
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    return true;
}

bool cac::OGLRenderer::updateContext(cac::WindowDesc windowDesc)
{
    if(window.create(windowDesc))
    {
	unloadResources();
	return true;
    }
    return false;
}

bool cac::OGLRenderer::createShaderProgram(std::string programName, std::string vertexShader, std::string fragmentShader, std::string geometryShader)
{
    return shaderManager.createProgram(programName, vertexShader, fragmentShader, geometryShader);
}

bool cac::OGLRenderer::createMesh(std::string name, std::vector<Vertex> vertices, std::vector<short> indices)
{
    GLenum error = glGetError();
    if(meshes[name].vao != 0)
    {
	std::cout<<"Warning: Mesh \""<<name<<"\" already exists!"<<std::endl;
	return false;
    }

    //create buffers
    glGenVertexArrays(1, &meshes[name].vao);

    glGenBuffers(1, &meshes[name].vbo);


    //bind data to buffer
    glBindVertexArray(meshes[name].vao);
    glBindBuffer(GL_ARRAY_BUFFER, meshes[name].vbo);

    
    //TODO: Destringyfy, remove magic strings and numbers
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    //shader attributes
    glEnableVertexAttribArray(shaderManager.getAttribLocation("vertex"));
    glVertexAttribPointer(shaderManager.getAttribLocation("vertex"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);

    glEnableVertexAttribArray(shaderManager.getAttribLocation("uv"));
    glVertexAttribPointer(shaderManager.getAttribLocation("uv"), 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (const GLvoid *) (3 * sizeof(GLfloat)));



    glGenBuffers(1, &meshes[name].texRectangle);
    glBindBuffer(GL_ARRAY_BUFFER, meshes[name].texRectangle);
    glEnableVertexAttribArray(shaderManager.getAttribLocation("textureRectangle"));
    glVertexAttribPointer(shaderManager.getAttribLocation("textureRectangle"), 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, NULL);
    glVertexAttribDivisor(shaderManager.getAttribLocation("textureRectangle"), 1);

    glGenBuffers(1, &meshes[name].color);
    glBindBuffer(GL_ARRAY_BUFFER, meshes[name].color);
    glEnableVertexAttribArray(shaderManager.getAttribLocation("color"));
    glVertexAttribPointer(shaderManager.getAttribLocation("color"), 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, NULL);
    glVertexAttribDivisor(shaderManager.getAttribLocation("color"), 1);


    glGenBuffers(1, &meshes[name].mvp);
    glBindBuffer(GL_ARRAY_BUFFER, meshes[name].mvp);

    for (unsigned int i = 0; i < 4; i++)
    {
	glEnableVertexAttribArray(shaderManager.getAttribLocation("MVP") + i);
	glVertexAttribPointer(shaderManager.getAttribLocation("MVP") + i, 4, GL_FLOAT, GL_FALSE, sizeof(float) *4 ,
		(const GLvoid *) (sizeof(GLfloat) * i * 4));
	glVertexAttribDivisor(shaderManager.getAttribLocation("MVP") + i, 1);
    }

    meshes[name].numberOfIndices = vertices.size();
    //unbind vao
    glBindVertexArray(0);

   
    error = glGetError();
    return error == GL_NO_ERROR;
}
bool cac::OGLRenderer::createTexture(std::string textureName, int width, int height,  std::vector<char> data, bool hasAlpha)
{
    return createTexture(textureName, width, height, data, (hasAlpha ? 4 : 3));
    
}
bool cac::OGLRenderer::createTexture(std::string textureName, int width, int height,  std::vector<char> data, int numChannels)
 {
     if(textures[textureName].textureId != 0)
     {
	 std::cout<<"Warning: Texture already exists!"<<std::endl;
	 return false;
     }
     
    GLenum error = glGetError();
	
    textures[textureName] = OGLTexture();
    glGenTextures(1, &textures[textureName].textureId);

    glBindTexture(GL_TEXTURE_2D, textures[textureName].textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT);

    bool po2X = false;
    bool po2Y = false;
    
    int roof = (width > height ? width : height);
    if(roof <= 1024)
    {
	for(int i = 2; i<=roof; i*=2)
	{
	    if(width == i)
		po2X = true;
	    if(height == i)
		po2Y = true;
	}
    }
    
    if(po2X && po2Y)
    {
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    }
    else 
    {
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    }
	
    GLint internalFormat;
    switch (numChannels)
    {
	case 1: { internalFormat = GL_RED; break; }
	case 3: { internalFormat = GL_RGB; break; }
	case 4: { internalFormat = GL_RGBA; break; }
	default: { internalFormat = GL_RGB; }
    }
    

#if EMSCRIPTEN
	if(internalFormat == GL_RED)
	{
	    std::vector<char> fontData;
	    for(unsigned int i = 0; i<data.size(); i++)
	    {
		fontData.push_back(data[i]);
		fontData.push_back(0);
		fontData.push_back(0);

	    }
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &fontData[0]);
	}
	else 
       glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, &data[0]);
#else 
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, &data[0]);     
#endif
    glBindTexture(GL_TEXTURE_2D, 0);
    

    textures[textureName].hasAlpha = (numChannels == 4);
    textures[textureName].width = width;
    textures[textureName].height = height;
    
    error = glGetError();
    
  
    
    return error == GL_NO_ERROR;
 }
   
bool cac::OGLRenderer::bindTexture(std::string texture)
{
    glActiveTexture(GL_TEXTURE0);
    GLint textureLoc = glGetUniformLocation(boundShaderProgram, "texture");
    
    GLuint textureId = textures[texture].textureId;
    if(textureId == 0)
	std::cout<<"Texture "<<texture<<" not loaded!"<<std::endl;
    
    glBindTexture(GL_TEXTURE_2D, textures[texture].textureId);
    glUniform1i(textureLoc, 0);
    
    return true;
}

void cac::OGLRenderer::swapBuffers()
{
    window.swapBuffers();

}

void cac::OGLRenderer::setClearColor(float r, float g, float b)
{
    glClearColor(r, g, b, 1);
}
void cac::OGLRenderer::clearBuffers()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void cac::OGLRenderer::setWireframe(bool wireframe)
{
    if(wireframe)
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    else 
	glPolygonMode(GL_FRONT, GL_POLYGON);
}

void cac::OGLRenderer::render(const Renderable& renderable)
{
    GLenum error = glGetError();
    
    bindTexture(renderable.texture);
    
    glBindVertexArray(meshes[renderable.mesh].vao);
    
    glm::vec3 position(renderable.posX, renderable.posY, renderable.posZ);
    glm::vec3 scale(renderable.scaleX, renderable.scaleY,renderable.scaleZ);	
		    
    glm::mat4 mvp;
    mvp = glm::translate(mvp, position);
    mvp = glm::scale(mvp, scale);
    mvp = activeCamera->getMatrix() * mvp;
    
    glBindBuffer(GL_ARRAY_BUFFER, meshes[renderable.mesh].mvp);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4), &mvp[0], GL_DYNAMIC_DRAW);

    float color[] = { renderable.colorR, renderable.colorG, renderable.colorB, renderable.colorA };
    glBindBuffer(GL_ARRAY_BUFFER, meshes[renderable.mesh].color);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4, &color[0], GL_DYNAMIC_DRAW);
    
    float texRect[] = { renderable.texRectX, renderable.texRectY, renderable.texRectWidth , renderable.texRectHeight };
    
    glBindBuffer(GL_ARRAY_BUFFER, meshes[renderable.mesh].texRectangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4, &texRect[0], GL_DYNAMIC_DRAW);

    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, meshes[renderable.mesh].numberOfIndices, 1);
    error = glGetError();
    glBindVertexArray(0);
}

bool cac::OGLRenderer::bindShaderProgram(std::string program)
{
    boundShaderProgram = shaderManager.getShaderProgram(program);
    glUseProgram(boundShaderProgram);
    
    return true;
}

bool cac::OGLRenderer::setShaderAttributeLocation(std::string name, int location)
{
    shaderManager.setAttribLocation(name, location);
    
    return true;
}

cac::IWindow* cac::OGLRenderer::getWindow()
{
    return &window;
}
