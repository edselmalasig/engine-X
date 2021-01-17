#ifndef Primitive_H
#define Primitive_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "shader.h"
#include "fip_ImageOperations.h"
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

#include <vector>

struct VertexP {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    // vertexID
    int ID;
    // vertex model matrix
    glm::mat4 model = glm::mat4(1.0f);
};

struct Edge{
  // start vertex
  glm::vec3 vs;
  // end vertex
  glm::vec3 ve;
  // edgeID
  int ID;
  // edge model matrix
  glm::mat4 model = glm::mat4(1.0f);
};

struct Face{
  struct Edge edge1, edge2, edge3, edge4;
};
class Primitive
{
private:



public:
  Primitive();
  Primitive(float data[]);
  Primitive(float data[], GLuint indices[]);
  Primitive(float data[], unsigned int indices[], GLuint edges[]);

  VertexP vertex;
  Edge edge;

  std::vector<VertexP> vertexList;
  std::vector<Edge> edgeList;
  std::vector<unsigned int> faceIndices;
  unsigned int primEdges[71];

  unsigned int VBO;
  unsigned int VAO;
  unsigned int EBO;

  unsigned int eVBO;
  unsigned int eVAO;
  unsigned int eEBO;

  Shader * prim_shader;

  int vertexShader;
  int fragmentShader;
  int shaderProgram;
  unsigned int texture[8];
  FIBITMAP * textureFileIn;

  void initShader(const char * vertexShaderSource, const char * fragmentShaderSource);
  void initObjectTexture(Primitive * Primitive, int i, char * texturefpath);
  void renderTexLayer(int i);

  void initObject();
  void initEdges();
  void updateObjectBuffer();
  void drawObject();
  void drawEdges();
  void deleteObject();

  void initTriangle();
  void drawTriangle();

};

#endif
