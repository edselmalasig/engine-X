#include "Geometry.h"
#include <stdio.h>
#include <iostream>
#include <string.h>

Geometry::Geometry()
{

}

Geometry::Geometry(float verts[])
{
		//vertices = verts; Consider implementing this
}

void Geometry::init_triangle(Geometry *geometry)
{
    glGenVertexArrays(1, &geometry->VAO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(geometry->VAO);
    glGenBuffers(1, &geometry->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(geometry->vertices), geometry->vertices, GL_STATIC_DRAW);

    //vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //geometry->lo_shader->use();

}

void Geometry::init_cube(Geometry *geometry)
{
    glGenVertexArrays(1, &geometry->VAO);
    glBindVertexArray(geometry->VAO);
    glGenBuffers(1, &geometry->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(geometry->cube), geometry->cube, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //geometry->lo_shader->use();
}

void Geometry::init_cube_wnml(Geometry *geometry)
{
    glGenVertexArrays(1, &geometry->VAO);
    glBindVertexArray(geometry->VAO);
    glGenBuffers(1, &geometry->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(geometry->cube_wnml), geometry->cube_wnml, GL_STATIC_DRAW);

		//vertex vap
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//normal data vap
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

    //geometry->lo_shader->use();
}

void Geometry::initobject(Geometry *geometry)
{
    glGenVertexArrays(1, &geometry->VAO);
    glGenBuffers(1, &geometry->VBO);
    glGenBuffers(1, &geometry->EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(geometry->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, geometry->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(geometry->vertices), geometry->vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(geometry->indices), geometry->indices, GL_STATIC_DRAW);

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

void Geometry::inittexture(Geometry * geometry, int i, char * texturefpath)
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

void Geometry::initshader(const char *vertexShaderSource, const char * fragmentShaderSource, Geometry *geometry)
{
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    geometry->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(geometry->vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(geometry->vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(geometry->vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(geometry->vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    geometry->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(geometry->fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(geometry->fragmentShader);
    // check for shader compile errors
    glGetShaderiv(geometry->fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(geometry->fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    geometry->shaderProgram = glCreateProgram();
    glAttachShader(geometry->shaderProgram, geometry->vertexShader);
    glAttachShader(geometry->shaderProgram, geometry->fragmentShader);
    glLinkProgram(geometry->shaderProgram);
    // check for linking errors
    glGetProgramiv(geometry->shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(geometry->shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(geometry->vertexShader);
    glDeleteShader(geometry->fragmentShader);

}

void Geometry::enableshader()
{
  this->lo_shader->use();
}

void Geometry::draw_triangle(Geometry *geometry)
{
    //glEnable(GL_CULL_FACE);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    // draw our triiangle
    //glLineWidth(1.5f);
    //glUseProgram(geometry->shaderProgram);
    geometry->lo_shader->use();
    glBindVertexArray(geometry->VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0); // no need to unbind it every time
}

void Geometry::draw_object(Geometry *geometry)
{
    //printf("Drawing object.");
    //glEnable(GL_CULL_FACE);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    //glLineWidth(1.5f);
    // draw our object
    //glUseProgram(geometry->shaderProgram);
    //if(textureFileIn!=NULL)

    geometry->lo_shader->use();
    glBindVertexArray(geometry->VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Geometry::draw_cube(Geometry *geometry)
{
		geometry->enableshader();
		glBindVertexArray(geometry->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0); // no need to unbind it every time
}

void Geometry::renderTexLayer(int i)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture[i]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->texture[i+1]);
}

void Geometry::delete_object(Geometry *geometry)
{
    glDeleteVertexArrays(1, &geometry->VAO);
    glDeleteBuffers(1, &geometry->VBO);
    glDeleteBuffers(1, &geometry->EBO);
}
