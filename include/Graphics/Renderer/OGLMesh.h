#ifndef CACATUIDAE_GRAPHICS_OGLMESH_H
#define CACATUIDAE_GRAPHICS_OGLMESH_H

#include <GL/glew.h>
#include "Graphics/GraphicStructs.h"

namespace cac 
{
    struct OGLMesh 
    {
	GLuint mvp = 0;
        GLuint color = 0;
	
	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint ibo = 0;
	GLuint texRectangle = 0;
	unsigned int numberOfIndices = 0;
    };
}
#endif