/** \addtogroup Renderer
 *  \ingroup Graphics
 *  @{
 */

#ifndef CACATUIDAE_GRAPHICS_IRENDERER_H
#define CACATUIDAE_GRAPHICS_IRENDERER_H

#include <string>
#include "IWindow.h"
#include "Graphics/GraphicStructs.h"
#include "Graphics/Renderable.h"
#include "Graphics/Camera.h"
#include "ETestMethod.h"

namespace cac
{	    
	/** Interface for the renderer-implementations
	*  Provides an interface for the
	*  various renderer-implementations. A Renderer 
	*  is the interface between the GraphicsLibraries(OpenGL, DirectX, ..)
	*  and the outside. Ideally, no other file will contains the 
	*  graphicslibrary-specific code, except for the renderer-implementations.
	* 
	* @sa OGLRenderer
	*/
	class IRenderer
	{
	public:
	    /** Initialization of the graphics-library
	     *  Initialize the graphics library and also generated
	     *  the context. 
	     *  @param[in] windowDesc description for the render context
	     *  @return true for success or false if failed
	     */
	    virtual bool initialize(WindowDesc windowDesc) = 0;
	    
	    
	    /** Updates the context with new information
	     * Update the context based on the new windowDesc. 
	     * Allows to change to/from fullscreen and change the size of the context
	     * 
	     *  @param[in] windowDesc description for the render context
	     *  @return true for success or false if failed
	     */
	    virtual bool updateContext(WindowDesc windowDesc) = 0;
	    
	    /** Create a mesh from the given parameters
	    *  Generate the Mesh inlcuding its buffers from the vertices and indices.
	    *  It can be referenced by it's name later.
	    *  @sa MeshResource
	    * 
	    * @param[in] name name of the mesh. Used to reference the mesh later
	    * @param[in] vertices Vertex information of the mesh. Contains spartial position and uv corrds of the points
	    * @param[in] indices optional paramter. Dictates the order in which the vertices should be renderd. If left out, the vertices will be rendered in order of their array index
	    * @return true for success or false if failed
	    */
	    virtual bool createMesh(std::string name, std::vector<Vertex> vertices, std::vector<short> indices) = 0;
	    
	    /** Create a shader program from the given parameters
	    *  Generate the Shaderprogram by compiling and linking the passed
	    *  shader sources. It can be referenced by it's name later.
	    *  @sa ShaderResource
	    * 
	    * @param[in] programName name of the program. Used to reference the program later
	    * @param[in] vertexShader VertexShader source code
	    * @param[in] fragmentShader Fragment-/PixelShader source code
	    * @param[in] geometryShader Optional: GemetryShader source code
	    * 
	    * @return true for success or false if failed
	    */
	    virtual bool createShaderProgram(std::string programName, std::string vertexShader, std::string fragmentShader, std::string geometryShader ="") = 0; 
	   
	    /** Create a texturefrom the given parameters
	    *  Generate the texture used for meshes or the font texture.
	    *  @sa TextureResource
	    * 
	    * @param[in] textureName name of the texture. Used to reference the texture later
	    * @param[in] width width of the texture
	    * @param[in] height height of the texture
	    * @param[in] data binary data of the texture
	    * @param[in] hasAlpha if the texture has a alpha channel, it will be generated with 4 channels, otherwise it uses 3
	    * 
	    * @return true for success or false if failed
	    */
	    virtual bool createTexture(std::string textureName, int width, int height, std::vector<char> data,  bool hasAlpha = false) = 0;
	    
	    /** Create a texturefrom the given parameters
	    *  Generate the texture used for meshes or the font texture.
	    *  @sa TextureResource
	    * 
	    * @param[in] textureName name of the texture. Used to reference the texture later
	    * @param[in] width width of the texture
	    * @param[in] height height of the texture
	    * @param[in] data binary data of the texture
	    * @param[in] numChannel number of channels used by the texture. Can be 1, 3 or 4.
	    * 
	    * @return true for success or false if failed
	    */
	    virtual bool createTexture(std::string textureName, int width, int height, std::vector<char> data,  int numChannels) = 0;
	    
	    /** Swap the backbuffer
	    * Swaps the backbuffers of the render context to "update" the screen.
	    */
	    virtual void swapBuffers() = 0;
	    
	     /** Set the clear color
	    * Set the clear color for the color buffer.
	    * It's basically the backgroundcolor
	    * 
	    * @param[in] r red value of the color. Range between (0.00f - 1.00f)
	    * @param[in] g green value of the color. Range between (0.00f - 1.00f) 
	    * @param[in] b blue value of the color. Range between (0.00f - 1.00f)
	    */
	    virtual void setClearColor(float r, float g, float b)=0;
	    
	     /** clear the buffers
	    * Clears the buffers. Currently only the colorbuffer will be cleared.
	    * TODO: Depth, stencil buffers and select them via bit flag param 
	    */
	    virtual void clearBuffers()=0;
	    
	    /** Renders the renderable
	     * Bind the needed buffers used by the renderable and makes the draw call.
	     * Requires a bound shader and camera.
	     * 
	     * @param[in] renderable Contains all needed information for the render call(Transformation, texture, mesh,..)
	     */
	    virtual void render(const Renderable& renderable) = 0;
	    
	    /** Binds the shaderprogram 
	     * Binds the ShaderProgram with the passed name.
	     * @sa ShaderResource
	     * 
	     * @param[in] program ShaderProgram name
	     * @return true for success or false if failed
	     */
	    virtual bool bindShaderProgram(std::string program) = 0;
	    
	    /** Binds a texture
	     * Binds the Texture corresponding to the passed name.
	     * @sa TextureResource
	     * 
	     * @param[in] texture texture name
	     * @return true for success or false if failed
	     */
	    virtual bool bindTexture(std::string texture) = 0;
	    
	    
	    /** Enable/Disable Wireframe rendering
	     * Set the current rendering mode. It can be set to wireframe 
	     * or back to the default mode.
	     * 
	     * @param[in] wirefram true for enabled wireframe mode, false for default mode
	     */
	    virtual void setWireframe(bool wireframe) = 0;
	   
	    /** Set the ShaderAttributeLocation
	     * Sets the ShaderAttribute to a fixed location, which
	     * allows meshes to use multiple shaders without recreating them 
	     * after change.
	     * 
	     * @param[in] name name of the Attribute
	     * @param[in] location new fixed attribute location
	     * 
	     * @return true for success or false if failed
	     */ 
	    virtual bool setShaderAttributeLocation(std::string name, int location) = 0;
	    
	    /** Returns the context window
	     * The context window is needed by other modules.
	     * The input system and the game engine have to access
	     * the context to listen to specific  event calls.
	     * 
	     * @return context window
	     */
	    virtual IWindow* getWindow() = 0;
	    
	    virtual void setDepthTest(ETestMethod test) = 0;
	    
	     /** Set the current active camera
	     * Set the reference to the active camera used for the 
	     * view and projection matrix.
	     * @sa Camera
	     * 
	     * @param[in] camera 
	     */
	    void setCamera(Camera& camera) { activeCamera = &camera; }
	    
	protected:
	    Camera* activeCamera; /*!< Current active camera for the view/projection matrix calculation*/
	};
}

#endif

/** @}*/
