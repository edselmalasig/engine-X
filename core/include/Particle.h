#ifndef PARTICLE_H
#define PARTICLE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

/*
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
*/

#include "EngineX.h"
//#include "texture.h"
//#include "fip_ImageOperations.h"
#include "shader.h"


class Particle{

public:

  Shader * shader;
  GLuint VBO, VAO, EBO;
  GLfloat * bufferdata;

  int shaderProgram;

  Particle();

  Particle(const char * vspath, const char * fspath, int buffsize);

  void genVA();
  void genBuff();
  void bindVA();
  void bindBuff();

  void initBuffer();

  void updateBuffData(int size);
  void updateVAP(GLint index, GLint size, GLenum type, GLboolean normalize, GLsizei stride, const GLvoid * pointer);

  void initParticles(int index, int size, GLenum type, GLboolean normalize, GLsizei stride, const GLvoid * pointer);
  //  void initShader(const char *vertexShaderSource, const char * fragmentShaderSource);
  // unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
  // unsigned int STB_TextureFromFile(const char* path, const std::string& directory, bool gamma);
  glm::mat4 view;
  glm::mat4 projection;
  glm::mat4 model;
  glm::vec4 incolor;
  GLdouble time;
  GLint timeLoc;
  GLint modelLoc;
  GLint viewLoc;
  GLint projLoc;
  GLint incolorLoc;
  GLint u_sprite;
  GLuint texture_id;
  GLint textureID;

};

#endif
