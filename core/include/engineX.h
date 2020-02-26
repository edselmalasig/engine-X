#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imguistyleserializer.h"

#include "camera.h"
#include "gcwuiControls.h"

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
// About OpenGL function loaders: modern OpenGL doesn't have a standard header file and requires individual function pointers to be loaded manually.
// Helper libraries are often used for this purpose! Here we are supporting a few common ones: gl3w, glew, glad.
// You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>
#include <iostream>

class EngineX
{
public:
     //GLFW Variables
     char glsl_version[50];
     static int window_w;
     static int window_h;
     static GLFWwindow* window;

     //ImGuiIO * io = NULL;
     bool show_demo_window;
     bool show_another_window;
     static bool show_ui;
     ImVec4 clear_color;

     //camera and controls
     static Camera * camera;
     bool isPressing;

     // mouse interface
     double * mousePosX;
     double * mousePosY;

     EngineX(Camera * cam);
     void init_glfw();
     void init_ImGui( );
     static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
     void ImGui_Loop();
     void processInput(GLFWwindow *window);
     static void rotateView();
     static void reshapeFunc( int w, int h);
     static void panView();
     static GLFWmousebuttonfun mouseButtonFunc( GLFWwindow * window, int button, int action, int mods);
     static GLFWcursorposfun mouseFunc(double xpos, double ypos);
     static GLFWscrollfun scrollBackFunc(GLFWwindow *window, double xOffset, double yOffset);
     static void editModeFunc( GLFWwindow * window, int key, int scancode, int action);
     static GLFWkeyfun moveFunc(GLFWwindow * window, int key, int scancode, int action);

     /*
     *
     *    Object Picking Section
     *
     */
     void Get3DRayUnderMouse(glm::vec3* v1, glm::vec3* v2);
     bool RaySphereCollision(glm::vec3 vSphereCenter, float fSphereRadius, glm::vec3 vA, glm::vec3 vB);
     void ScreenPosToWorldRay(
     	int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
     	int screenWidth, int screenHeight,  // Window size, in pixels
     	glm::mat4 ViewMatrix,               // Camera position and orientation
     	glm::mat4 ProjectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
     	glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
     	glm::vec3& out_direction            // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
     );
     bool RayAABBIntersection(
     	glm::vec3 ray_origin,        // Ray origin, in world space
     	glm::vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
     	glm::vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
     	glm::vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
     	glm::mat4 ModelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
     	float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB
     );
};

#endif
