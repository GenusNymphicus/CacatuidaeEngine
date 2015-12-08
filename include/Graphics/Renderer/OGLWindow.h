/** \addtogroup Graphic
 *  @{
 */

#ifndef CACATUIDAE_GRAPHICS_OGLWINDOW_H
#define CACATUIDAE_GRAPHICS_OGLWINDOW_H

#include <string>
#include "IWindow.h"

struct GLFWwindow;
namespace cac
{	
	/** OpenGL window-implementation using GLFW3
	* Uses GLFW3 and glew for the window and context creation.  
	*/
	class OGLWindow : public IWindow
	{
	public:
	    OGLWindow();
	    
	    /** Window creation
	     * Creates a new window and context using GLFW
	     * This can be called multiple times on the same object, 
	     * but it will discard the old window by doing so. 
	     * The renderer might have to reload previous 
	     * created ressources due the context change.
	     * 
	     * @returns true for success or false for failure
	     * @sa OGLRenderer.h
	     */
	    virtual bool create(WindowDesc description);
	    virtual bool initialize(WindowDesc description);
	    virtual bool shouldClose();
	    virtual void swapBuffers();
	    GLFWwindow* getContext() { return context; }
	protected:
	    WindowDesc description;
	    GLFWwindow* context;
	};
}

#endif

/** @}*/
