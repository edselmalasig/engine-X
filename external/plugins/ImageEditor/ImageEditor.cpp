#include <stdio.h>
#include <string>
#include <iostream>

#define FREEIMAGE_LIB

#include "fipHeaders.h"
#include "fip_ImageOperations.h"
#include <GL/glew.h>

int main(int argc, const char * argv[])
{

#ifdef FREEIMAGE_LIB
  FreeImage_Initialise();
#endif

  const char * imageFile = argv[1];

  printf("FreeImage version: %s Filename: %s", FreeImage_GetVersion(), argv[1]);
  printf("\n");

  FREE_IMAGE_FORMAT format = FreeImage_GetFileType(imageFile, 0);

  FIBITMAP * dib = FreeImage_Load(format, imageFile, 0);

  if (!dib)
  {
    std::cerr << "Error loading image." << std::endl;
    exit(0);
  }

  int image_width = FreeImage_GetWidth(dib);
  int image_height = FreeImage_GetHeight(dib);

  int nrChannels;

  BYTE * bits;
  bits = FreeImage_GetBits(dib);

  PrintRGBValues(dib);
  FreeImage_Save(format, dib, "resources/defaultsave.png", 0);
}
