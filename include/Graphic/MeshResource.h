#ifndef CACATUIDAE_GRAPHIC_MESH_RESOURCE_H 
#define CACATUIDAE_GRAPHIC_MESH_RESOURCE_H 

#include <string>
#include "GraphicStructs.h"
#include "Core/IResource.h"

namespace cac 
{
    struct MeshResource : public IResource
    {
	std::string vertexShader = "";
	std::vector<Vertex> vertices;
	std::vector<short> indices;
    };
}
#endif