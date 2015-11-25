/** \addtogroup Resources
 *  \ingroup Core
 *  @{
 */
 

#ifndef CACATUIDAE_CORE_RESOURCE_PACKAGE_H
#define CACATUIDAE_CORE_RESOURCE_PACKAGE_H

#include <vector>
#include "TextureResource.h"
#include "FontResource.h"

namespace cac 
{
     /** Contains the loaded ResourcePackage
     * Contains all loaded resources by the ResourceLoader.
     * 
     * @sa ResourceLoader
     */
    struct ResourcePackage 
    {
	std::string name;  /*!< name = path of the package */
 
	std::vector<TextureResource> textures; /*!< loaded textures */
	std::vector<FontResource> fonts; /*!< loaded fonts */
    };
}
#endif

 /** @}*/