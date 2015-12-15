#ifndef CACATUIDAE_GRAPHICS_CAMERA_H
#define CACATUIDAE_GRAPHICS_CAMERA_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace cac 
{
    struct Camera
    {
    public:
        Camera() 
        {
	    viewMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f,0.0f,0.0f));
        }

        glm::mat4 getMatrix() { return projectionMatrix*viewMatrix; }

        void setOrthogonalProjection(float left, float right, float bottom, float top, float nearPlane = -0.01f, float farPlane = -100.0f)
        {
            this->left = left;
            this->right = right;
            this->bottom = bottom;
            this->top = top;
            this->nearPlane = nearPlane;
	    this->farPlane = farPlane;
	    
	    projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
        }

	glm::vec2 getResolution() { return glm::vec2(right, bottom); }
	
	void setPosition(float x, float y, float z = 0.0f)
	{
	    position = glm::vec3(x,y,z); 
	    viewMatrix = glm::translate(glm::mat4(), position);
	}
	
        void move(float x, float y, float z = 0)
	{
	    position += glm::vec3(x,y,z);
	    viewMatrix = glm::translate(glm::mat4(), position);
	}
    private:
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
	glm::vec3 position;
	
        float 	fieldOfView = 45.0f,
                aspectRatio = 4.0f / 3.0f,
                nearPlane = 0.01f,
                farPlane = 100.0f;

        float left = 0.0f,
                right = 800.0f,
                top = 0.0f,
                bottom = 600.0f;
    };

}
#endif