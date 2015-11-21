#ifndef CACATUIDAE_GRAPHIC_TEXTURE_RESOURCE_H 
#define CACATUIDAE_GRAPHIC_TEXTURE_RESOURCE_H 

#include "Core/IResource.h"

namespace cac 
{
    struct TextureResource : public IResource
    {
	int width;
	int height;
	bool hasAlpha;
	std::vector<char> data;
    };
}
#endif