/** \addtogroup Resources
 *  \ingroup Core
 *  @{
 */
 

#ifndef CACATUIDAE_CORE_RESOURCES_MESH_RESOURCE_H 
#define CACATUIDAE_CORE_RESOURCES_MESH_RESOURCE_H 

#include <string>
#include "Graphics/GraphicStructs.h"
#include "IResource.h"

namespace cac 
{
     /** Loaded Meshresource used for  rendering
     * Contains the information for mesh rendering, like the geometric data.
     * The Renderable reference the MeshResource via it's name.
     * 
     * @sa IRenderer 
     * @sa IResource 
     * @sa Renderable
     * @sa ResourceLoader
     */
    struct MeshResource : public IResource
    {
	std::vector<Vertex> vertices;   /*!< VertexData. Includes the  spatial position and the uv points */
	std::vector<short> indices;   /*!< Optional. Contains the order in which the vertices are rendered. If it's empty, the vertex order will be their array index */
 
    };
}
#endif

 /** @}*/