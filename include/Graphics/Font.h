#ifndef CACATUIDAE_GRAPHICS_GRAPHIC_FONT_H
#define CACATUIDAE_GRAPHICS_GRAPHIC_FONT_H

//needed for Glyphinformation
#include "Core/Resources/FontResource.h"

namespace cac 
{
    struct Font 
    {
	std::map<char, GlyphInformation> glyphs;
	float yOffset;
	float textureHeight;
	float textureWidth;
    };
}

#endif