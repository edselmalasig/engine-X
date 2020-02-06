#pragma once
#ifndef CAMERA_H
#define CAMERA_H
// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/ext.hpp"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UPWARD,
    DOWNWARD
};

// Default camera values
const GLfloat YAW        =  -90.0f;
const GLfloat PITCH      =  0.0f;
const GLfloat SPEED      =  3.0f;
const GLfloat SENSITIVTY =  0.25f;
const GLfloat ZOOM       =  45.0f;

class Camera
{
public:
    GLfloat deltaTime = 0.1f;
    GLfloat lastFrame = 0.0f;
    bool keys[1024];
    GLfloat lastX = 400, lastY = 300;
    bool firstMouse = true;
    int t=0;
    glm::mat4 view;
    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods

    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Eular Angles
    GLfloat Yaw;
    GLfloat Pitch;
    // Camera options
    GLfloat MovementSpeed;
    GLfloat MouseSensitivity;
    GLfloat * Zoom;
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;
    int display_w=1280;
    int display_h=800;

    //new Camera variables/
    glm::vec2 oldMousePosition;
    Camera();
		//Camera(glm::vec3 POSITION, glm::vec3 HEADSUP);
    Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch);
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ,
           GLfloat upX, GLfloat upY, GLfloat upZ,
           GLfloat yaw, GLfloat pitch);

    glm::mat4 getViewMatrix();
    glm::mat4 processViewMatrix();
    glm::mat4 getProjectionMatrix();
		glm::vec3 * getFrontVector();
		glm::vec3 * getPositionVector();
		glm::vec3 * getHeadsUpVector();

    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch);
    void ProcessMouseScroll(GLfloat yoffset);
    void computeMatricesFromInputs();

private:
    void updateCameraVectors();


};
#endif
