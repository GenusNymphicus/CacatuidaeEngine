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
	std::string font = "font";
	std::string mesh = "Quad";
	
	float posX, posY, posZ;
	float scaleX = 1, scaleY = 1, scaleZ = 1;
	float colorR=0, colorG=0, colorB = 0, colorA= 1;
	
	void setPosition(float x, float y, float z= 0) { posX = x; posY = y; posZ = z; }
	void setColor(float r, float g, float b, float a) { colorR = r; colorG = g; colorB = b; colorA = a; }

    };
}
#endif