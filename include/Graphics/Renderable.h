#ifndef CACATUIDAE_GRAPHICS_Renderable_H
#define CACATUIDAE_GRAPHICS_Renderable_H


namespace cac 
{
    struct Renderable 
    {
	float posX = 0, posY = 0, posZ = 0;
	float texRectX= 0, texRectY = 0, texRectWidth = 1, texRectHeight = 1;
	std::string texture = "default";
	std::string mesh = "Quad";
	float scaleX = 1, scaleY = 1, scaleZ = 1;
	float colorR = 1, colorG = 1, colorB = 1, colorA = 1;

	void setPosition(float x, float y, float z = 0.0f) { posX = x; posY = y; posZ = z; }	
	void setScale(float x, float y, float z = 1.0f) { scaleX = x; scaleY = y; scaleZ = z; }	
	void setColor(float r, float g, float b, float a = 1.0f) { colorR = r; colorB = b; colorG = g; colorA = a; }
	void setTextureRectangle(float x, float y, float width = 1.0f, float height = 1.0f) { texRectX = x; texRectY = y; texRectWidth= width; texRectHeight= height; }
    };
}

#endif