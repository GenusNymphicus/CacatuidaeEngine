#ifndef CACATUIDAE_GRAPHIC_SHADER_RESOURCE_H 
#define CACATUIDAE_GRAPHIC_SHADER_RESOURCE_H 

#include <string>
#include "Core/IResource.h"

namespace cac 
{
    struct ShaderResource : public IResource
    {
	std::string vertexShader = "";
	std::string fragmentShader = "";
	std::string geometryShader = "";
    };
}
#endif