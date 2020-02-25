// mouse picker class

#ifndef MOUSE_PICKER_H
#define MOUSE_PICKER_H

#include "camera.h"
#include "initialize.h"
// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/ext.hpp"

void Get3DRayUnderMouse(glm::vec3* v1, glm::vec3* v2)
{
/*
	POINT mp; GetCursorPos(&mp);
	ScreenToClient(appMain.hWnd, &mp);
	RECT rect; GetClientRect(appMain.hWnd, &rect);
	mp.y = rect.bottom-mp.y;
*/
     double mousePosX, mousePosY;

     glfwGetCursorPos(gcwui_C->window, &mousePosX, &mousePosY);
     mousePosY = gcwui_C->g_cnc->display_h - mousePosY;
	glm::vec4 viewport = glm::vec4(0.0f, 0.0f, gcwui_C->g_cnc->display_w, gcwui_C->g_cnc->display_h);

	*v1 = glm::unProject(glm::vec3(float(mousePosX), float(mousePosY), 0.0f), gcwui_C->g_cnc->getViewMatrix(), gcwui_C->g_cnc->getProjectionMatrix(), viewport);
	*v2 = glm::unProject(glm::vec3(float(mousePosX), float(mousePosY), 1.0f), gcwui_C->g_cnc->getViewMatrix(), gcwui_C->g_cnc->getProjectionMatrix(), viewport);
}

/*-----------------------------------------------

Name:    RaySphereCollision

Params:  vSphereCenter - guess what it is
	     fSphereRadius - guess what it is
		 vA, vB - two points of ray

Result:  Checks if a ray given by two points
		 collides with sphere.

/*---------------------------------------------*/

bool RaySphereCollision(glm::vec3 vSphereCenter, float fSphereRadius, glm::vec3 vA, glm::vec3 vB)
{
	// Create the vector from end point vA to center of sphere
	glm::vec3 vDirToSphere = vSphereCenter - vA;

	// Create a normalized direction vector from end point vA to end point vB
	glm::vec3 vLineDir = glm::normalize(vB-vA);

	// Find length of line segment
	float fLineLength = glm::distance(vA, vB);

	// Using the dot product, we project the vDirToSphere onto the vector vLineDir
	float t = glm::dot(vDirToSphere, vLineDir);

	glm::vec3 vClosestPoint;
	// If our projected distance from vA is less than or equal to 0, the closest point is vA
	if (t <= 0.0f)
		vClosestPoint = vA;
	// If our projected distance from vA is greater thatn line length, closest point is vB
	else if (t >= fLineLength)
		vClosestPoint = vB;
	// Otherwise calculate the point on the line using t and return it
	else
		vClosestPoint = vA+vLineDir*t;

	// Now just check if closest point is within radius of sphere
	return glm::distance(vSphereCenter, vClosestPoint) <= fSphereRadius;
}

#endif
