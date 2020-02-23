//
//  camera.cpp
//
//
//  Created by Edsel Malasig on 12/24/19.
//

// Std. Includes
#include <vector>
// GL Includes

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/ext.hpp"
#include "camera.h"

Camera::Camera(){
    this->Position = glm::vec3(0.0f, 0.0f, 4.5f);
		this->WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->Up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->Front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->Yaw = YAW;
    this->Pitch = PITCH;
    this->Zoom = new GLfloat(ZOOM);
    this->updateCameraVectors();
    this->MovementSpeed = SPEED;
    this->MouseSensitivity = SENSITIVTY;
}

/*
Camera::Camera(glm::vec3 POSITION, glm::vec3 HEADSUP):  Yaw(YAW), Pitch(PITCH),
					MovementSpeed( SPEED ), MouseSensitivity (SENSITIVTY)
{
		this->Position = POSITION;
		this->Front = FRONT;
		this->WorldUp  = this->Up = HEADSUP;
		Yaw = YAW;
		Pitch = PITCH;
		Zoom = new GLfloat(ZOOM);
		updateCameraVectors();
}
*/

// Constructor with vectors
Camera::Camera(glm::vec3 position, //viewDirection
               glm::vec3 up,
               GLfloat yaw,
               GLfloat pitch)
: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY),
Zoom()
{
    this->Position = position;
    this->WorldUp = up;
    this->Up = up;
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->Zoom = new GLfloat(ZOOM);
    this->updateCameraVectors();
}
// Constructor with scalar values
Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ,
               GLfloat upX, GLfloat upY, GLfloat upZ,
               GLfloat yaw, GLfloat pitch)
: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom()
{
    this->Position = glm::vec3(posX, posY, posZ);
    this->WorldUp = glm::vec3(upX, upY, upZ);
    this->Up = glm::vec3(upX, upY, upZ);
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->Zoom = new GLfloat(ZOOM);
    this->updateCameraVectors();
}

// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
glm::mat4 Camera::getViewMatrix()
{
		// glm::lookAt(position, target, up) all 3 parameter is vec3
    return ViewMatrix = glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

glm::mat4 Camera::processViewMatrix()
{
    return ViewMatrix = glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

glm::mat4 Camera::getProjectionMatrix()
{
    return ProjectionMatrix;
}

glm::vec3 * Camera::getFrontVector()
{
		return &this->Front;
}

glm::vec3 * Camera::getPositionVector()
{
		return &this->Position;
}

glm::vec3 * Camera::getHeadsUpVector()
{
		return &this->Up;
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
    GLfloat velocity = this->MovementSpeed * deltaTime;
    if (direction == FORWARD)
        this->Position += this->Front * velocity;
    if (direction == BACKWARD)
        this->Position -= this->Front * velocity;
    if (direction == LEFT){
        glm::vec3 StrafeDirection = glm::normalize(glm::cross(this->Front, this->Up));
        this->Position -= velocity * StrafeDirection;
    }
    if (direction == RIGHT){
        glm::vec3 StrafeDirection = glm::normalize(glm::cross(this->Front, this->Up));
        this->Position += velocity * StrafeDirection;
    }
    if (direction == UPWARD){
        glm::vec3 ClimbDirection = glm::normalize(glm::cross(this->Front, this->Right));
        this->Position -= ClimbDirection * velocity;
    }
    if (direction == DOWNWARD){
        glm::vec3 ClimbDirection = glm::normalize(glm::cross(this->Front, this->Right));
        this->Position += ClimbDirection * velocity;
    }

    printf("Position: %f %f %f\n", this->Position.x, this->Position.y, this->Position.z);
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    xoffset *= this->MouseSensitivity;
    yoffset *= this->MouseSensitivity;
    //viewUpdate(glm::vec2(xoffset, yoffset));

    this->Yaw   += xoffset;
    this->Pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (this->Pitch > 89.0f)
            this->Pitch = 89.0f;
        if (this->Pitch < -89.0f)
            this->Pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Eular angles
    this->updateCameraVectors();
    //this->processViewMatrix();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(GLfloat yoffset)
{
    if (*this->Zoom >= 1.0f && *this->Zoom <= 360.0f)
        *this->Zoom -= yoffset;
    if (*this->Zoom <= 1.0f)
        *this->Zoom = 1.0f;
    if (*this->Zoom >= 360.0f)
        *this->Zoom = 360.0f;
}

void Camera::computeMatricesFromInputs(){
    //glfwGetCursorPos(window, &xpos, &ypos);
    ViewMatrix = glm::lookAt(this->Position, this->Position + this->Front, this->Up);
    ProjectionMatrix = glm::perspective(glm::radians(*this->Zoom), (float)display_w / (float)display_h, 0.100f, 100.0f);
}

// PRIVATE
// Calculates the front vector from the Camera's (updated) Eular Angles
void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    front.y = sin(glm::radians(this->Pitch));
    front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    this->Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->Up    = glm::normalize(glm::cross(this->Right, this->Front));
}
