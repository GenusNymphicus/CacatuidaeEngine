/** \addtogroup Resources
 *  \ingroup Core
 *  @{
 */
 
#ifndef CACATUIDAE_CORE_RESOURCE_LOADER_H
#define CACATUIDAE_CORE_RESOURCE_LOADER_H

#include <fstream>
#include <map>
#include "ResourcePackage.h"
#include "TextureResource.h"
#include "FontResource.h"

namespace cac 
{
     /** Loads all Resources into a ResourcePackage
     * Contains the information for a single glyph loaded with the ResourceLoader.
     * 
     * @sa ResourcePackage 
     * @sa IResource
     */
    class ResourceLoader 
    {
    public:
	/** Loads the package path in a ResourcePackage
	* Contains the information for a single glyph loaded with the ResourceLoader.
	* Since the file pointer will be moved during reading, it necessary to load the files
	* in the following order.
	* - load Fonts
	* - load Textures
	* - load Audios
	* - load Shaders
	* 
	* @sa ResourcePackage 
	* 
	* @param[in] packagePath The path to the Packagefile.  
	* 
	* @return ResourcePackage return the filled ResourcePackage with all loaded Resources
	*/
	ResourcePackage loadPackage(std::string packagePath);
	
    private:
	/** Loads the FontResource inside the ResourcePackage
	* It loads the required information needed to load fonts.
	* 
	* The file has to comply with a specific order.
	* - 1 byte number of Fonts contained in the Package
	* - 1 byte for the length of the font name [nameLength]
	* - [nameLength] bytes for the font name
	* - 1 byte for the font size used to save the font
	* - 2 bytes for the font texture height
	* - 2 bytes for the font texture width
	* - 4 bytes for the font texture data count [dataCount]
	* - [dataCount] bytes for the font texture data
	* - 2bytes for the number of the glyphs [glyphCount]
	* - [glyphCount] * 7 * 4 bytes for the required Glyphinformations
	* 
	* @sa FontResource 
	* 
	* @param[in] packageFile File handle with the current pointer at the fonts position
	* 
	* @return all loaded Fonts bundled in a std::vector
	*/
	std::vector<FontResource> loadFonts(std::ifstream& packageFile);
	
	/** Loads the TextureResource inside the ResourcePackage
	* It loads the required information needed to load textures, used by meshes.
	* 
	* The file has to comply with a specific order.
	* - 1 byte number of textures contained in the Package
	* - 1 byte for the length of the texture name [nameLength]
	* - [nameLength] bytes for the texture name
	* - 1 byte for the texture format(uses alpha or not)
	* - 2 bytes for the texture height
	* - 2 bytes for the texture width
	* - 4 bytes for the texture data count [dataCount]
	* - [dataCount] bytes for the texture data
	* 
	* @sa TextureResource 
	* @param[in] packageFile File handle with the current pointer at the textures position
	* 
	* @return all loaded Textures bundled in a std::vector
	*/
	std::vector<TextureResource> loadTextures(std::ifstream& packageFile);
	
	/** NOT IMPLEMENTED
	*/
	void loadShaders(std::ifstream& packageFile);
	
	/** NOT IMPLEMENTED
	*
	* Contains the information for a single glyph loaded with the ResourceLoader.
	* @sa ResourcePackage 
	* 
	* @param[in] packagePath The path to the Packagefile.  
	* 
	* @param[out] ResourcePackage return the filled ResourcePackage with all loaded Resources
	*/
	void loadAudio(std::ifstream& packageFile);
	
	/** Helper method for converting the binary Data
	 * Converts the binary data into a 4-byte unsigned integer. 
	 * It will move the cursor in the file handle by numberOfBytes
	 * 
	 * @param[in] packageFile File handle with the current pointer at the textures position
	 * @param[in] numberOfBytes number of Bytes to read. Max. 4 bytes
	 * 
	*/
	uint32_t readBytesToUInt32(std::ifstream& packageFile, unsigned int numberOfBytes);
    };
}
#endif

 
 /** @}*/