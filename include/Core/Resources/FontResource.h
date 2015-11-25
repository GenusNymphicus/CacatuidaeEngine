/** \addtogroup Resources
 *  \ingroup Core
 *  @{
 */

#ifndef CACATUIDAE_CORE_RESOURCES_FONT_RESOURCE_H 
#define CACATUIDAE_CORE_RESOURCES_FONT_RESOURCE_H 

#include "IResource.h"

namespace cac 
{
    /** Glyphspecific information
     * Contains the information for a single glyph loaded with the ResourceLoader.
     * 
     * @sa FontResource 
     * @sa ResourceLoader
     */
    struct GlyphInformation
	{
	    unsigned int advanceX, advanceY;  /*!< difference to the next glyph on the font texture */
	    unsigned int bitmapWidth, bitmapHeight; /*!< size of the glyph */
	    unsigned int bitmapLeft, bitmapTop; /*!< space between the reserved border of the glyph and the actual glyph symbol.  */
	    unsigned int textureX; /*!< x position on the font texture */
	};

    /** Loaded Fontresource used for text rendering
     * Contains the information for a loaded font.
     * The FontResource provides the information needed to generate the font texture
     * and the glyph positions on it.
     * 
     * @sa GlyphInformation 
     * @sa IResource 
     * @sa ResourceLoader
     */
    struct FontResource : public IResource 
    {
	unsigned int fontSize; /*!< font size used to generate the FontResource */
	unsigned int textureHeight; /*!< height of the font texture */
	unsigned int textureWidth; /*!< width of the font texture */
	std::map<char, GlyphInformation> glyphs; /*!< Contains the information for a single glyph, including their spartial position on the font texture */
	std::vector<char> data;  /*!< font texture as binary data */
    };
}
#endif


/** @}*/
