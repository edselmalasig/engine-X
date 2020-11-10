#include <GL/glew.h>
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


void loadTexture(char * texturefpath, FIBITMAP * textureFileIn, unsigned int texture)
{
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  //texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // call this ONLY when linking with FreeImage as a static library
  #ifdef FREEIMAGE_LIB
  FreeImage_Initialise();
  #endif // FREEIMAGE_LIB

  // initialize your own FreeImage error handler

  //FreeImage_SetOutputMessage(FreeImageErrorHandler);

  // print version & copyright infos

  printf("FreeImage version : %s", FreeImage_GetVersion());
  printf("\n");
  printf(FreeImage_GetCopyrightMessage());
  printf("\n");
  FREE_IMAGE_FORMAT format = FreeImage_GetFileType(texturefpath,0);
  // Load the source image
  textureFileIn = FreeImage_Load(format, texturefpath, 0);
  int texture_w = FreeImage_GetWidth(textureFileIn);
  int texture_h = FreeImage_GetHeight(textureFileIn);
  int nrChannels;

  BYTE * bits;
  bits = FreeImage_GetBits(textureFileIn);
  if(textureFileIn)
  {
    if(format == FIF_JPEG)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_w, texture_h, 0,
        GL_BGR, GL_UNSIGNED_BYTE, FreeImage_GetBits(textureFileIn));
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    if(format == FIF_PNG)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_w, texture_h, 0,
          GL_BGRA, GL_UNSIGNED_BYTE, FreeImage_GetBits(textureFileIn));
          glGenerateMipmap(GL_TEXTURE_2D);
    }
  }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

void renderTexLayer(int i, unsigned int texture[])
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture[i]);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture[i+1]);
}
