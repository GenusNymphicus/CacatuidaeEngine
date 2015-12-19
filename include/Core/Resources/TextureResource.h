/** \addtogroup Resources
 *  \ingroup Core
 *  @{
 */
 
 
#ifndef CACATUIDAE_CORE_RESOURCES_TEXTURE_RESOURCE_H 
#define CACATUIDAE_CORE_RESOURCES_TEXTURE_RESOURCE_H 

#include "IResource.h"

namespace cac 
{
     /** Loaded Texture
     * Contains the information for a texture needed by meshes.
     * 
     * @sa ResourceLoader
     */
 
    struct TextureResource : public IResource
    {
	int width;  /*!< width of the texture */
	int height; /*!< height of the texture */
	bool hasAlpha; /*!< Tells the renderer if this texture uses 3 or 4 channels */
	std::vector<unsigned char> data; /*!< texture data as binary */
    };
}
#endif

 /** @}*/