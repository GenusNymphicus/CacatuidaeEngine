#ifndef CACATUIDAE_GRAPHICS_CAMERA_H
#define CACATUIDAE_GRAPHICS_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace cac 
{
    struct Camera
    {
    public:
        Camera() 
        {
        }

        glm::mat4 getMatrix() { return projectionMatrix; }

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
        
    private:
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
	
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