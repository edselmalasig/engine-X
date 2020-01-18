#include "PrimimtiveShape.h"
#include <stdio.h>
#include <iostream>

PrimitiveShape::PrimitiveShape()
{

}

PrimitiveShape::PrimitiveShape(float verts[])
{
    this-
}

PrimitiveShape::PrimitiveShape(float verts[], float color[])
{

}

PrimitiveShape::PrimitiveShape(float verts[], float color[], float indices[])
{

}

void PrimitiveShape::init_shader(const char *vertexShaderSource, const char * fragmentShaderSource, PrimitiveShape *PrimitiveShape)
{
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    PrimitiveShape->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(PrimitiveShape->vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(PrimitiveShape->vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(PrimitiveShape->vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(PrimitiveShape->vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    PrimitiveShape->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(PrimitiveShape->fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(PrimitiveShape->fragmentShader);
    // check for shader compile errors
    glGetShaderiv(PrimitiveShape->fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(PrimitiveShape->fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    PrimitiveShape->shaderProgram = glCreateProgram();
    glAttachShader(PrimitiveShape->shaderProgram, PrimitiveShape->vertexShader);
    glAttachShader(PrimitiveShape->shaderProgram, PrimitiveShape->fragmentShader);
    glLinkProgram(PrimitiveShape->shaderProgram);
    // check for linking errors
    glGetProgramiv(PrimitiveShape->shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(PrimitiveShape->shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(PrimitiveShape->vertexShader);
    glDeleteShader(PrimitiveShape->fragmentShader);

}

void PrimitiveShape::init_triangle(PrimitiveShape *PrimitiveShape)
{
    glGenVertexArrays(1, &PrimitiveShape->VAO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(PrimitiveShape->VAO);
    glGenBuffers(1, &PrimitiveShape->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, PrimitiveShape->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(PrimitiveShape->vertices), PrimitiveShape->vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    PrimitiveShape->lo_shader->use();

}

void PrimitiveShape::init_object(PrimitiveShape *PrimitiveShape)
{
    glGenVertexArrays(1, &PrimitiveShape->VAO);
    glGenBuffers(1, &PrimitiveShape->VBO);
    glGenBuffers(1, &PrimitiveShape->EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(PrimitiveShape->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, PrimitiveShape->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(PrimitiveShape->vertices), PrimitiveShape->vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, PrimitiveShape->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(PrimitiveShape->indices), PrimitiveShape->indices, GL_STATIC_DRAW);

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

void PrimitiveShape::init_object_texture(PrimitiveShape * PrimitiveShape, int i, char * texturefpath)
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

void PrimitiveShape::draw_triangle(PrimitiveShape *PrimitiveShape)
{
    //glEnable(GL_CULL_FACE);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    // draw our triiangle
    //glLineWidth(1.5f);
    //glUseProgram(PrimitiveShape->shaderProgram);
    PrimitiveShape->lo_shader->use();
    glBindVertexArray(PrimitiveShape->VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0); // no need to unbind it every time
}

void PrimitiveShape::renderTexLayer(int i)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture[i]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->texture[i+1]);
}

void PrimitiveShape::draw_object(PrimitiveShape *PrimitiveShape)
{
    //printf("Drawing object.");
    //glEnable(GL_CULL_FACE);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    //glLineWidth(1.5f);
    // draw our object
    //glUseProgram(PrimitiveShape->shaderProgram);
    //if(textureFileIn!=NULL)

    PrimitiveShape->lo_shader->use();
    glBindVertexArray(PrimitiveShape->VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void PrimitiveShape::delete_object(PrimitiveShape *PrimitiveShape)
{
    glDeleteVertexArrays(1, &PrimitiveShape->VAO);
    glDeleteBuffers(1, &PrimitiveShape->VBO);
    glDeleteBuffers(1, &PrimitiveShape->EBO);
}
