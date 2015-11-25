/** \addtogroup Resources
 *  \ingroup Core
 *  @{
 */
 
#ifndef CACATUIDAE_CORE_RESOURCE_SHADER_RESOURCE_H 
#define CACATUIDAE_CORE_RESOURCE_SHADER_RESOURCE_H 

#include <string>
#include "IResource.h"

namespace cac 
{
     /** Contains the shaders required for a shader program
     * 
     * @sa IRenderer 
     */
 
    struct ShaderResource : public IResource
    {
	std::string vertexShader = "";
	std::string fragmentShader = "";
	std::string geometryShader = "";
    };
}
#endif

 
 
 /** @}*/