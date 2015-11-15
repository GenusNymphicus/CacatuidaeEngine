#ifndef CACATUIDAE_GRAPHICS_GRAPHIC_STRUCTS_H
#define CACATUIDAE_GRAPHICS_GRAPHIC_STRUCTS_H

namespace cac 
{
    struct Vertex 
	{
	    float x,y,z;
	    float texCoordX,texCoordY;
	    Vertex(float x = 0, float y  = 0, float z = 0, float texCoordX = 0, float texCoordY = 0) : x(x), y(y), z(z), texCoordX(texCoordX), texCoordY(texCoordY)
	    {
	    }
	};
}
#endif