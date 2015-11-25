/** \addtogroup TestCases
 *  @{
 */

#include <iostream>

#include "gtest/gtest.h"
#include "Graphics/Renderer/OGLRenderer.h"
#include "Graphics/Renderer/OGLWindow.h"


/*
TEST(GraphicsEngine, renderer_initialization)
{
     cac::OGLRenderer renderer;
     
     int result = renderer.initialize(cac::WindowDesc("TITLE", 800, 600 , false));
     ASSERT_EQ(0, result);
     
     std::string vertexShader = "#version 330\n"
				"layout (location = 0) in vec3 vertex;"
				"layout (location = 1) in vec2 uv;"
				"layout (location = 2) in vec4 color;"
				"layout (location = 3) in vec4 textureRectangle;"
				"layout (location = 4) in mat4 MVP;"
				"out vec4 fragmentColor;"
				"out vec2 fragmentUV;"
				"void main()"
				"{"
				"fragmentColor = color;"
				"fragmentUV.x = textureRectangle.x + uv.x * textureRectangle.z;"
				"fragmentUV.y = textureRectangle.y + uv.y * textureRectangle.a;"
				"gl_Position = MVP* vec4(vertex, 1.0f);"
				"}";
				
     std::string fragShader =   "#version 330\n"
				"uniform sampler2D texture;"
				"in vec4 fragmentColor;"
				"in vec2 fragmentUV;"
				"out vec4 finalColor;"
				"void main()"
				"{"
				"finalColor = fragmentColor;"
				"finalColor.a = texture2D(texture, fragmentUV).r;"
				"}";
				
     ASSERT_TRUE(renderer.createShaderProgram("basicProgram", vertexShader, fragShader));
     
     
     std::vector<cac::Vertex> vertices;
     vertices.push_back(cac::Vertex(0,0,0, 0 ,0 ));
     vertices.push_back(cac::Vertex(1,1,0,0 ,1 ));
     vertices.push_back(cac::Vertex(1,0,0, 1, 0));

     
     EXPECT_TRUE(renderer.createMesh("Triangle", vertices));   
}*/

/** @}*/