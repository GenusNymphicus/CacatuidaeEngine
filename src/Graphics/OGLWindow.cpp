#include "Graphics/Renderer/OGLWindow.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


cac::OGLWindow::OGLWindow()
{
    context = nullptr;
}


bool cac::OGLWindow::initialize(cac::WindowDesc description)
{
    static bool initialized = false;
    
    // Initialise GLFW
    if(!initialized && !glfwInit())
	    return false;
    
    if(!create(description))
	return false;
    
    //glew
    if(!initialized)
    {
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	
	if(err != GL_NO_ERROR)
	{
	    return false;
	}
    }

   initialized = true;
   return true;
}

bool cac::OGLWindow::create(cac::WindowDesc description)
{
    this->description = description;

    glfwWindowHint(GLFW_SAMPLES, 8);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSwapInterval(0);


    // Open a window and create its OpenGL context
    GLFWwindow* newContext = nullptr;
    
    if(!description.fullscreen)
	newContext = glfwCreateWindow(description.width, description.height, description.title.c_str(), nullptr, nullptr);
    else
    {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	description.width = mode->width;
	description.height = mode->height;
	newContext = glfwCreateWindow(mode->width, mode->height, description.title.c_str(), glfwGetPrimaryMonitor(), nullptr);
    }
    
    if(!newContext)
	return false;
    
    //Destroy old contect
    if (context != nullptr)
       glfwDestroyWindow(context);
    
    context = newContext;
    glfwMakeContextCurrent(context);

    return true;
}

bool cac::OGLWindow::shouldClose()
{
    return glfwWindowShouldClose(context);
}

void cac::OGLWindow::swapBuffers()
{
    glfwPollEvents();
    glfwSwapBuffers(context);
}





