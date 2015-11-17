#ifndef CACATUIDAE_CORE_RESOURCE_PACKAGE_H
#define CACATUIDAE_CORE_RESOURCE_PACKAGE_H

#include <vector>
#include "Graphic/TextureResource.h"

namespace cac 
{
    struct ResourcePackage 
    {
	std::string name;
	std::vector<TextureResource> textures;
    };
}
#endif