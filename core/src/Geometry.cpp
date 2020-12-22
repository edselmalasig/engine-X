#include "Geometry.h"
#include <stdio.h>
#include <iostream>
#include <string.h>

Geometry::Geometry()
{
     model = glm::mat4(1.0f);
}

Geometry::Geometry(float verts[])
{
     //vertices = verts; Consider implementing this
}

void Geometry::init_triangle()
{
     glGenVertexArrays(1, &VAO);

     // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
     glBindVertexArray(VAO);
     glGenBuffers(1, &VBO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

     //vertices
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(0);

     //color
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
     glEnableVertexAttribArray(1);

     //lo_shader->use();

}

void Geometry::init_cube()
{
     glGenVertexArrays(1, &VAO);
     glBindVertexArray(VAO);
     glGenBuffers(1, &VBO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(0);

     //lo_shader->use();
}

void Geometry::init_cube_wnml()
{
     glGenVertexArrays(1, &VAO);
     glBindVertexArray(VAO);
     glGenBuffers(1, &VBO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(cube_wnml), cube_wnml, GL_STATIC_DRAW);

     // vertex vap
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(0);
     // normal data vap
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
     glEnableVertexAttribArray(1);
}

void Geometry::init_cube_wntc()
{
     glGenVertexArrays(1, &VAO);
     glBindVertexArray(VAO);
     glGenBuffers(1, &VBO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(cube_wntc), cube_wntc, GL_STATIC_DRAW);

     //vertex vap
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(0);
     //normal data vap
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
     glEnableVertexAttribArray(1);
     // texcoords
     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
     glEnableVertexAttribArray(2);
}

void Geometry::init_cube_wnml_fixed()
{
     glGenVertexArrays(1, &VAO);
     glBindVertexArray(VAO);
     glGenBuffers(1, &VBO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(cube_wnml), cube_wnml, GL_STATIC_DRAW);

     //vertex vap
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(0);
     //normal data vap
     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
     glEnableVertexAttribArray(1);

     //lo_shader->use();
}

void Geometry::init_object()
{
     glGenVertexArrays(1, &VAO);
     glGenBuffers(1, &VBO);
     glGenBuffers(1, &EBO);

     // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
     glBindVertexArray(VAO);

     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

     // position attribute
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(0);
     // color attribute... SEEMS to like this disabled if transform to vertex shader is applied
     glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
     glEnableVertexAttribArray(2);
     // texture coord attribute
     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
     glEnableVertexAttribArray(1);

}

void Geometry::init_texture(int i, char * texturefpath)
{
     glGenTextures(1, &texture[i]);
     glBindTexture(GL_TEXTURE_2D, texture[i]);

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
               glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_w, texture_h, 0, GL_BGR, GL_UNSIGNED_BYTE, FreeImage_GetBits(textureFileIn));
               glGenerateMipmap(GL_TEXTURE_2D);
          }
          if(format == FIF_PNG)
          {
               glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_w, texture_h, 0, GL_BGRA, GL_UNSIGNED_BYTE, FreeImage_GetBits(textureFileIn));
               glGenerateMipmap(GL_TEXTURE_2D);

          }
          else
          {
               std::cout << "Failed to load texture" << std::endl;
          }
     }
}

void Geometry::init_shader(const char *vertexShaderSource, const char * fragmentShaderSource)
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

void Geometry::enable_shader()
{
     lo_shader->use();
}

void Geometry::draw_triangle()
{
     //glEnable(GL_CULL_FACE);
     //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
     // draw our triiangle
     //glLineWidth(1.5f);
     //glUseProgram(shaderProgram);
     lo_shader->use();
     glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
     glDrawArrays(GL_TRIANGLES, 0, 3);
     glBindVertexArray(0); // no need to unbind it every time
}

void Geometry::draw_object()
{
     //printf("Drawing object.");
     //glEnable(GL_CULL_FACE);
     //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
     //glLineWidth(1.5f);
     // draw our object
     //glUseProgram(shaderProgram);
     //if(textureFileIn!=NULL)

     lo_shader->use();
     glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
     glBindVertexArray(0);
}

void Geometry::draw_cube(GLenum mode)
{
     enable_shader();
     glBindVertexArray(VAO);
     glDrawArrays(mode, 0, 36);
     glBindVertexArray(0); // no need to unbind it every time
}

void Geometry::updateBuffData(){
     enable_shader();
     glBindVertexArray(VAO);

     glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(0);


}
void Geometry::renderTexLayer(int i)
{
     for(int ii = 0; ii <= i; ii++)
     {
          glActiveTexture(GL_TEXTURE0+ii);
          glBindTexture(GL_TEXTURE_2D, texture[ii]);
     }
}

void Geometry::delete_object()
{
     glDeleteVertexArrays(1, &VAO);
     glDeleteBuffers(1, &VBO);
     glDeleteBuffers(1, &EBO);
}
