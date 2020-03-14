#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
  // position
  glm::vec3 Position;
  // normal
  glm::vec3 Normal;
  // texture coordinates
  glm::vec2 TexCoords;
  // tangent
  glm::vec3 Tangent;
  // bitangent
  glm::vec3 Bitangent;
};

struct Texture {
  unsigned int id;
  string type;
  string path;
};

class Mesh {
public:
  /* Mesh Data */
  vector<Vertex> vertices;
  vector<unsigned int> indices;
  vector<unsigned int> e_indices;
  vector<unsigned int> vt_indices;
  vector<unsigned int> vn_indices;
  vector<Texture> textures;
  unsigned int VAO;

  /* Functions */
  // constructor
  Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<unsigned int> e_indices, vector<Texture> textures)
  {
    this->vertices = vertices;
    this->indices = indices;
    this->e_indices = e_indices;
    this->textures = textures;

    unsigned int VAO;
    // setup mesh
    setupMesh();
  }

  // render the mesh
  void Draw(Shader shader)
  {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    for(unsigned int i = 0; i < textures.size(); i++)
    {
      glActiveTexture(GL_TEXTURE0 + i);

      string number;
      string name = textures[i].type;
      if(name == "texture_diffuse")
        number = std::to_string(diffuseNr++);
      else if(name == "texture_specular")
        number = std::to_string(specularNr++);
      else if(name == "texture_normal")
        number = std::to_string(normalNr++);
      else if(name == "texture_height")
        number = std::to_string(heightNr++);

      glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);

      glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, e_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
  }
  void DrawEdges(Shader shader)
  {
       glEnable(GL_PRIMITIVE_RESTART);
       glPrimitiveRestartIndex(0xFFFFFFFE);
       glBindVertexArray(VAO);
       glDrawElements(GL_LINES, e_indices.size(), GL_UNSIGNED_INT, 0);
       glBindVertexArray(0);
 }

 void DrawPoints(Shader shader)
{
     //glEnable(GL_PRIMITIVE_RESTART_INDEX);
     //glPrimitiveRestartIndex(0xFFFFFFFE);
      glBindVertexArray(VAO);
      glDrawElements(GL_POINTS, e_indices.size(), GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
}

private:
  /* Render Data */
  unsigned int VBO, EBO, EDGES;

  void setupMesh()
  {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &EDGES);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, e_indices.size() * sizeof(unsigned int), &e_indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    glBindVertexArray(0);
  }
};
#endif
