#ifndef CACATUIDAE_GRAPHICS_OGLTEXTURE_H
#define CACATUIDAE_GRAPHICS_OGLTEXTURE_H

#include <GL/glew.h>
#include <vector>
#include "Graphics/GraphicStructs.h"

namespace cac 
{
    struct OGLTexture
    {
	GLuint textureId = 0;
	bool hasAlpha;
	int width;
	int height;
    };
}
#endif