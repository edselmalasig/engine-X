#ifndef PRIMITIVE_DATA
#define PRIMITIVE_DATA

float triangle[18] = {
    // positions        // colors
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // top
};


float quad_vctc[32] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
};

unsigned int quad_indices[6] = {
    0, 1, 3,
    1, 2, 3
};

float rectangle_vertices[12] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};

unsigned int rectangle_indices[6] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

float cube[] = {
      -0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f,  0.5f, -0.5f,
       0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,

      -0.5f, -0.5f,  0.5f,
       0.5f, -0.5f,  0.5f,
       0.5f,  0.5f,  0.5f,
       0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f,

      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,

       0.5f,  0.5f,  0.5f,
       0.5f,  0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f, -0.5f,  0.5f,
       0.5f,  0.5f,  0.5f,

      -0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f, -0.5f,  0.5f,
       0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f, -0.5f,

      -0.5f,  0.5f, -0.5f,
       0.5f,  0.5f, -0.5f,
       0.5f,  0.5f,  0.5f,
       0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
};

float cube_quads_vertices[] = {
      1.000000, 1.000000, -1.000000,    // 0
      1.000000, -1.000000, -1.000000,   // 1
      1.000000, 1.000000, 1.000000,     // 2
      1.000000, -1.000000, 1.000000,    // 3
      -1.000000, 1.000000, -1.000000,   // 4
      -1.000000, -1.000000, -1.000000,  // 5
      -1.000000, 1.000000, 1.000000,    // 6
      -1.000000, -1.000000, 1.000000    // 7
};
/*
GLuint indices[] = {  // note that we start from 0!
     0, 3, 2,  // first Triangle
     0xFFFFFFFE,
     2, 1, 0   // second Triangle
};
*/
GLuint cube_quads_edges[] = {

     0, 4,
     0xFFFFFFFE,
     4, 6,
     0xFFFFFFFE,
     6, 2,
     0xFFFFFFFE,
     2, 0,
     0xFFFFFFFE,
     3, 2,
     0xFFFFFFFE,
     2, 6,
     0xFFFFFFFE,
     6, 7,
     0xFFFFFFFE,
     7, 3,
     0xFFFFFFFE,
     7, 6,
     0xFFFFFFFE,
     6, 4,
     0xFFFFFFFE,
     4, 5,
     0xFFFFFFFE,
     5, 7,
     0xFFFFFFFE,
     5, 1,
     0xFFFFFFFE,
     1, 3,
     0xFFFFFFFE,
     3, 7,
     0xFFFFFFFE,
     7, 5,
     0xFFFFFFFE,
     1, 0,
     0xFFFFFFFE,
     0, 2,
     0xFFFFFFFE,
     2, 3,
     0xFFFFFFFE,
     3, 1,
     0xFFFFFFFE,
     5, 4,
     0xFFFFFFFE,
     4, 0,
     0xFFFFFFFE,
     0, 1,
     0xFFFFFFFE,
     1, 5
};

GLuint cube_quads_indices[] = {
     0, 4, 6, 2, 0, 6,
     3, 2, 6, 7, 3, 6,
     7, 6, 4, 5, 7, 4,
     5, 1, 3, 7, 5, 3,
     1, 0, 2, 3, 1, 2,
     5, 4, 0, 1, 5, 0
};

#endif
