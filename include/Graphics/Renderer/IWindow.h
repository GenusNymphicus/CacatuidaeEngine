/** \addtogroup Graphic
 *  @{
 */

#ifndef COCKATOO_GRAPHICS_WINDOW_H
#define COCKATOO_GRAPHICS_WINDOW_H

#include <string>
namespace cac
{	
	/** Window Description needed for the Window creation
	 *  Contains the necessary information needed for the window creation.
	 *  @param title The Title of the window
	 *  @param width The width of the window
	 *  @param height The height of the window
	 *  @param fullscreen True for creation of a fullscreen window
	 */
	struct WindowDesc
	{
	    std::string title;
	    int height;
	    int width;
	    bool fullscreen; 
	    
	    /** Window Description needed for the Window creation
	    *  Contains the necessary information needed for the window creation.
	    *  The default values will create a 800x600 window.
	    * 
	    *  @param title The Title of the window
	    *  @param width The width of the window
	    *  @param height The height of the window
	    *  @param fullscreen True for creation of a fullscreen window
	    */
	    
	    WindowDesc(std::string title = "Title", int width = 800, int height = 600, bool fullscreen = false) : title(title), height(height), width(width), fullscreen(fullscreen)
	    {
	    }
	};
	
	/** Interface for the window-implementations
	* Provides an interface for the
	* various window-implementations. The window provides a valid context 
	* for the renderer and handles window/input events from the OS.  
	*/
	class IWindow
	{
	public:
	     
	    /** Window creation
	     * (Re-)create the context with the new description
	     * 
	     * 
	     * @return true for success or false for failure
	     */
	    virtual bool create(WindowDesc description) = 0;
	    
	     /** Initialize the context
	     * @return true for success or false for failure
	     */
	    virtual bool initialize(WindowDesc description) = 0;
	protected:
	    WindowDesc description;
	};
}

#endif

/** @}*/
