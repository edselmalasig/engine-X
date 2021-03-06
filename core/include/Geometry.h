#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "shader.h"
#include "fip_ImageOperations.h"
#include <string.h>
#include "glm/glm.hpp"
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

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

class Geometry
{
public:
     Geometry();
     Geometry(float verts[]);
     unsigned int VBO;
     unsigned int VAO;
     unsigned int EBO;
     Shader * shader;

     int vertexShader;
     int fragmentShader;
     int shaderProgram;
     unsigned int texture[8];
     FIBITMAP * textureFileIn;

     glm::mat4 model;

     float triangle[18] = {
          // positions         // colors
          0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
          -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
          0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top

     };

     float vertices[32] = {
          // positions          // colors           // texture coords
          0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
          0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
          -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
          -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
     };

     unsigned int indices[6] = {
          0, 1, 3,
          1, 2, 3
     };

     float quadrangle[12] = {
          0.5f,  0.5f, 0.0f,  // top right
          0.5f, -0.5f, 0.0f,  // bottom right
          -0.5f, -0.5f, 0.0f,  // bottom left
          -0.5f,  0.5f, 0.0f   // top left
     };

     unsigned int rectangle_ind[6] = {  // note that we start from 0!
          0, 1, 3,  // first Triangle
          1, 2, 3   // second Triangle
     };

     float cube[108] = {
          //back face
          0.5f, 0.5f, -0.5f,
          0.5f, -0.5f, -0.5f,
          -0.5f, -0.5f, -0.5f,
          -0.5f, -0.5f, -0.5f,
          -0.5f,  0.5f, -0.5f,
          0.5f,  0.5f, -0.5f,
          //front face
          -0.5f, -0.5f,  0.5f,
          0.5f, -0.5f,  0.5f,
          0.5f,  0.5f,  0.5f,
          0.5f,  0.5f,  0.5f,
          -0.5f,  0.5f,  0.5f,
          -0.5f, -0.5f,  0.5f,

          -0.5f,  0.5f,  0.5f,
          -0.5f,  0.5f, -0.5f,
          -0.5f, -0.5f, -0.5f,
          -0.5f, -0.5f, -0.5f,
          -0.5f, -0.5f,  0.5f,
          -0.5f,  0.5f,  0.5f,
          //left face
          0.5f, -0.5f, 0.5f,
          0.5f, -0.5f, -0.5f,
          0.5f,  0.5f, -0.5f,
          0.5f,  0.5f, -0.5f,
          0.5f,  0.5f,  0.5f,
          0.5f,  -0.5f,  0.5f,
          //bottom face
          -0.5f, -0.5f, -0.5f,
          0.5f, -0.5f, -0.5f,
          0.5f, -0.5f,  0.5f,
          0.5f, -0.5f,  0.5f,
          -0.5f, -0.5f,  0.5f,
          -0.5f, -0.5f, -0.5f,
          //top face
          -0.5f,  0.5f, -0.5f,
          -0.5f,  0.5f, 0.5f,
          0.5f,  0.5f,  0.5f,
          0.5f,  0.5f,  0.5f,
          0.5f,  0.5f, -0.5f,
          -0.5f,  0.5f, -0.5f,
     };

     float cubey[216] =
     {
          -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
          0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
          0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
          0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
          -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
          -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

          0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
          -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
          -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
          -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
          0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
          0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

          0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
          0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
          0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
          0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
          0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
          0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

          -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
          -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
          -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
          -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
          -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
          -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,

          -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
          0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
          0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
          0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
          -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
          -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

          -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
          0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
          0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
          0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
          -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
          -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f
     };

     float cube_wnml_fixed[180] = {
          // Back face
          -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
          0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
          -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
          -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
          // Front face
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
          0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
          0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
          -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
          // Left face
          -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
          -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
          -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
          // Right face
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
          0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
          // Bottom face
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
          0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
          // Top face
          -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
          -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
          -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left
     };

     float cube_wnml[216] = {
          //back face
          0.5f, 0.5f, -0.5f,  0.0f,  0.0f,  -1.0f,
          0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
          -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
          0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

          //front face
          -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
          -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
          -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

          //right face
          -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
          -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
          -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
          -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
          -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
          -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
          //left face
          0.5f, -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,
          0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
          0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
          0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
          0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
          0.5f,  -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
          //bottom face
          -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
          0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
          0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
          0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
          -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
          //top face
          -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
          -0.5f,  0.5f, 0.5f,  0.0f,  1.0f,  0.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
          0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
          -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
     };

     float cube_wntc[288] = {
          // positions          // normals           // texture coords
          0.5f, 0.5f, -0.5f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f,
          0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
          -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
          -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
          0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

          -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f,  0.0f,
          0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f,  0.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f,  1.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f,  1.0f,
          -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f,  1.0f,
          -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f,  0.0f,

          -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
          -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
          -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
          -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
          -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
          -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

          0.5f, -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
          0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
          0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
          0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
          0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
          0.5f,  -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

          -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
          0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
          0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
          0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
          -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

          -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
          -0.5f,  0.5f, 0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
          0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
          -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
     };

     void initTriangle();
     void initCube();
     void initCubeWNTC();
     void initCubeWNML();
     void initCubeWNML_fixed();
     void initObject();
     void initTexture(int i, char * texturefpath);

     void initShader(const char * vertexShaderSource, const char * fragmentShaderSource);

     void enableShader();
     void updateBufferData();
     void drawTriangle();
     void drawCube(GLenum mode);
     void drawObject();

     void renderTexLayer(int i);
     void deleteObject();
};

#endif
