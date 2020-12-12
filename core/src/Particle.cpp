#include "Particle.h"

Particle::Particle()
{

};

Particle::Particle(const char * vspath, const char * fspath, int buffsize)
{
  shader = new Shader(vspath, fspath);
  bufferdata = (GLfloat *) malloc(buffsize);
};

void Particle::initParticles(int index, int size, GLenum type, GLboolean normalize, GLsizei stride, const GLvoid * pointer){
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, size, bufferdata, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(index, size, type, normalize, stride, pointer);
  glEnableVertexAttribArray(0);
};

void Particle::updateBuffData(int size){
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, size, bufferdata, GL_STATIC_DRAW);
};
/*
unsigned int Particle::TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
  std::string filename = std::string(path);
  filename = directory + '/' + filename;

  unsigned int textureID;
  FIBITMAP * textureFileIn;

  FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename.c_str(),0);
  // Load the source image
  textureFileIn = FreeImage_Load(format, filename.c_str(), 0);
  int texture_w = FreeImage_GetWidth(textureFileIn);
  int texture_h = FreeImage_GetHeight(textureFileIn);
  int nrChannels;

  BYTE * bits;
  bits = FreeImage_GetBits(textureFileIn);
  if(textureFileIn)
  {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    if(format == FIF_JPEG)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_w, texture_h, 0,
        GL_BGR, GL_UNSIGNED_BYTE, bits);
        glGenerateMipmap(GL_TEXTURE_2D);
      }
      if(format == FIF_PNG)
      {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_w, texture_h, 0,
          GL_RGBA, GL_UNSIGNED_BYTE, bits);
          glGenerateMipmap(GL_TEXTURE_2D);
        }

        //texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      }
      else
      {
        std::cout << "Failed to load texture" << std::endl;
      }
      /*
      unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
      if (data)
      {
      GLenum format;
      if (nrComponents == 1)
      format = GL_RED;
      else if (nrComponents == 3)
      format = GL_RGB;
      else if (nrComponents == 4)
      format = GL_RGBA;

      glBindTexture(GL_TEXTURE_2D, textureID);
      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      stbi_image_free(data);
    }
    else
    {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }



  return textureID;
};

unsigned int Particle::STB_TextureFromFile(const char* path, const std::string& directory, bool gamma) {
  std::string filename = std::string(path);
  filename = directory + '/' + filename;

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  if (data)
  {
    GLenum format;
    if (nrComponents == 1)
    format = GL_RED;
    else if (nrComponents == 3)
    format = GL_RGB;
    else if (nrComponents == 4)
    format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  }
  else
  {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
};
*/
