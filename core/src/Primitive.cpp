

#include "Primitive.h"
#include <stdio.h>
#include <iostream>

Primitive::Primitive()
{

}

Primitive::Primitive(float data[])
{
  for(unsigned int i=0; i < sizeof(data)/sizeof(data[0]); i+=3)
  {
    vertex.Position.x = data[i];
    vertex.Position.y = data[i+1];
    vertex.Position.z = data[i+2];

    vertexList.push_back(vertex);
  }
}

Primitive::Primitive(float data[], GLuint indices[])
{
  unsigned int sz=0;

  while(data[sz] != NULL){
    sz++;
  }
  std::cout << "sizeof(data): " << sz << std::endl;

  for(unsigned int i=0; i < 24; i+=3)
  {
    vertex.Position.x = data[i];
    vertex.Position.y = data[i+1];
    vertex.Position.z = data[i+2];

    vertexList.push_back(vertex);
  }

  for(unsigned int i=0; i < 36; i++)
  {
    faceIndices.push_back(indices[i]);
  }
}

Primitive::Primitive(float data[], unsigned int indices[], GLuint edges[])
{
  for(unsigned int i=0; i < 24; i+=3)
  {
    vertex.Position.x = data[i];
    vertex.Position.y = data[i+1];
    vertex.Position.z = data[i+2];

    vertexList.push_back(vertex);
  }

  for(unsigned int i=0; i < 36; i++)
  {
    faceIndices.push_back(indices[i]);
  }
  for(int i=0, j=0; i < (72); i++, j++)
  {
    // edges array with primitive restart data
    primEdges[i] = edges[i];
  }

  for(unsigned int i = 0; i < 8; i++)
  {
    //std::cout << i << " " << vertexList[i].Position.x << " " << vertexList[i].Position.y
      //      << " " << vertexList[i].Position.z << std::endl;
  }
    // for edgeList vertices
  for(int i=0; i < 36-1; i++){

      Edge e;
      e.vs = vertexList[faceIndices[i]].Position;
      e.ve = vertexList[faceIndices[i+1]].Position;
      edgeList.push_back(e);
      std::cout << i << " " << e.vs.x << " " << e.vs.y << " " << e.vs.z << std::endl;
      std::cout << i+1 << " " << e.ve.x << " " << e.ve.y << " " << e.ve.z << std::endl;

  }
}

void Primitive::initShader(const char *vertexShaderSource, const char * fragmentShaderSource)
{
  // build and compile our shader program
  // ------------------------------------
  // vertex shader
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // fragment shader
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // link shaders
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

}

void Primitive::initObject()
{
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(VertexP), &vertexList[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, faceIndices.size() * sizeof(unsigned int), &faceIndices[0], GL_STATIC_DRAW);
  /*
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute... SEEMS to like this disabled if transform to vertex shader is applied
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(2);
  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(1);
  */
  // set the vertex attribute pointers
  // vertex Positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexP), (void*)0);
  // vertex normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexP), (void*)offsetof(VertexP, Normal));
  // vertex texture coords
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexP), (void*)offsetof(VertexP, TexCoords));
  // vertex tangent
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexP), (void*)offsetof(VertexP, Tangent));
  // vertex bitangent
  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexP), (void*)offsetof(VertexP, Bitangent));

  glBindVertexArray(0);
}

// should i use glBufferSubData

void Primitive::updateObjectBuffer()
{
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(VertexP), &vertexList[0], GL_STATIC_DRAW);
  //glBufferSubData(GL_ARRAY_BUFFER, vertexList.size()*sizeof(VertexP), sizeof(VertexP), &vertexList[0]);
  glBindVertexArray(eVAO);
  glBindBuffer(GL_ARRAY_BUFFER, eVBO);
  glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(VertexP), &vertexList[0], GL_STATIC_DRAW);
}

void Primitive::initEdges()
{
  glGenVertexArrays(1, &eVAO);
  glGenBuffers(1, &eVBO);
  glGenBuffers(1, &eEBO);

  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(eVAO);

  glBindBuffer(GL_ARRAY_BUFFER, eVBO);
  glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(VertexP), &vertexList[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(primEdges), primEdges, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexP), (void*)0);

  glBindVertexArray(0);
}

void Primitive::initObjectTexture(Primitive * Primitive, int i, char * texturefpath)
{
  glGenTextures(1, &this->texture[i]);
  glBindTexture(GL_TEXTURE_2D, this->texture[i]);

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
        GL_RGB, GL_UNSIGNED_BYTE, FreeImage_GetBits(textureFileIn));
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    if(format == FIF_PNG)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_w, texture_h, 0,
          GL_RGBA, GL_UNSIGNED_BYTE, FreeImage_GetBits(textureFileIn));
          glGenerateMipmap(GL_TEXTURE_2D);
    }
  }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

    void Primitive::renderTexLayer(int i)
    {
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, this->texture[i]);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, this->texture[i+1]);
    }

    void Primitive::drawObject()
    {
      //printf("Drawing object.");
      //glEnable(GL_CULL_FACE);
      //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      //glLineWidth(1.5f);
      // draw our object
      //glUseProgram(shaderProgram);
      //if(textureFileIn!=NULL)

      prim_shader->use();
      glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
      glDrawElements(GL_TRIANGLES, faceIndices.size(), GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
    }

    void Primitive::drawEdges()
    {
      prim_shader->use();
      glEnable(GL_PRIMITIVE_RESTART);
      glPrimitiveRestartIndex(0xFFFFFFFE);
      glLineWidth(1.1f);
      glPointSize(1.1f);
      glBindVertexArray(eVAO);
      glDrawElements(GL_LINES, sizeof(primEdges)/sizeof(primEdges[0]), GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
      glDisable(GL_PRIMITIVE_RESTART);

    }

    void Primitive::deleteObject()
    {
      glDeleteVertexArrays(1, &VAO);
      glDeleteBuffers(1, &VBO);
      glDeleteBuffers(1, &EBO);
    }
