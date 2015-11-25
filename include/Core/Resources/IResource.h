/** \addtogroup Resources
 *  \ingroup Core
 *  @{
 */

#ifndef CACATUIDAE_CORE_RESOURCES_IRESOURCE_H
#define CACATUIDAE_CORE_RESOURCES_IRESOURCE_H

#include <vector>
namespace cac  
{
     /** Generic Resource base class
     * Base class for the resources.
     * The ResourceLoader loads all resources and packs them into a ResourcePackage.
     * Resources are: FontResource, MeshResource, ShaderResource, TextureResource
     * 
     * @sa FontResource
     * @sa MeshResource 
     * @sa ShaderResource 
     * @sa TextureResource 
     * @sa ResourceLoader 
     * @sa ResourcePackage
     */
    struct IResource 
    {
	std::string name;   /*!< name of the resource. It has to be unique insude it's resource type*/
    };
}
#endif

/** @}*/