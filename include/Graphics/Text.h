#ifndef CACATUIDAE_GRAPHICS_GRAPHIC_TEXT_H
#define CACATUIDAE_GRAPHICS_GRAPHIC_TEXT_H

#include <glm/glm.hpp>
#include <string>

namespace cac 
{
    struct Text 
    {
    public:
	std::string textString;
	std::string font;
	std::string mesh;
	
	float posX, posY, posZ;
	float scaleX, scaleY, scaleZ;
	float colorR, colorG, colorB, colorA;
	
	void setPosition(float x, float y, float z= 0) { posX = x; posY = y; posZ = z; }
	void setColor(float r, float g, float b, float a) { colorR = r; colorG = g; colorB = b; colorA = a; }

    };
}
#endif