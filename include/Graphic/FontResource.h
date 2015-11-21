#ifndef CACATUIDAE_GRAPHIC_FONT_RESOURCE_H 
#define CACATUIDAE_GRAPHIC_FONT_RESOURCE_H 

#include "Core/IResource.h"

namespace cac 
{
    
    struct GlyphInformation
	{
	    unsigned int advanceX, advanceY;
	    unsigned int bitmapWidth, bitmapHeight;
	    unsigned int bitmapLeft, bitmapTop;
	    unsigned int textureX;
	};

	
    struct FontResource : public IResource 
    {
	unsigned int fontSize;
	unsigned int textureHeight;
	unsigned int textureWidth;
	std::map<char, GlyphInformation> glyphs;
	std::vector<char> data;
    };
}
#endif