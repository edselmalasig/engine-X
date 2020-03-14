

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
void button_callback(GLFWwindow* win, int bt, int action, int mods);
void cursor_callback(GLFWwindow* win, double x, double y);
void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
void char_callback(GLFWwindow* win, unsigned int key);
void error_callback(int err, const char* desc);
void resize_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
/* -------------------------------------------- */
int win_w = 1280;
int win_h = 720;
/* -------------------------------------------- */
int main() {
     glfwSetErrorCallback(error_callback);
     if(!glfwInit()) {
          printf("Error: cannot setup glfw.\n");
          exit(EXIT_FAILURE);
     }
     glfwWindowHint(GLFW_SAMPLES, 4);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
     glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);
     glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
     GLFWwindow* win = NULL;
     int w = win_w;
     int h = win_h;
     win = glfwCreateWindow(w, h, "Primitive restart v1.0", NULL, NULL);
     if(!win) {
          glfwTerminate();
          exit(EXIT_FAILURE);
     }
     glfwSetFramebufferSizeCallback(win, resize_callback);
     glfwSetKeyCallback(win, key_callback);
     glfwSetCharCallback(win, char_callback);
     glfwSetCursorPosCallback(win, cursor_callback);
     glfwSetMouseButtonCallback(win, button_callback);
     glfwSetScrollCallback(win, scroll_callback);
     glfwMakeContextCurrent(win);
     glfwSwapInterval(1);
     GLenum err = glewInit();
     if (err != GLEW_OK) {
          printf("Cannot load GL.\n");

          exit(1);
     }
     // ----------------------------------------------------------------
     // THIS IS WHERE YOU START CALLING OPENGL FUNCTIONS, NOT EARLIER!!
     // ----------------------------------------------------------------
     /* Fill our vertex and index buffers. 0xFFFF is our primitive restart value. */
     float vertices[] = {
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
     GLuint edges[] = {
          3, 2,
          0xFFFFFFFE,
          2, 6,
          0xFFFFFFFE,
          6, 7,
          0xFFFFFFFE,
          7, 3
     };
     unsigned int VBO, VAO, EBO;
     glGenVertexArrays(1, &VAO);
     glGenBuffers(1, &VBO);
     glGenBuffers(1, &EBO);
     // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
     glBindVertexArray(VAO);

     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(edges), edges, GL_STATIC_DRAW);

     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(0);

     // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
     glBindBuffer(GL_ARRAY_BUFFER, 0);

     // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
     //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

     // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
     // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
     glBindVertexArray(0);
     /* ==================================================== */
     /* DRAW SHADER                                          */
     /* ==================================================== */
     const char* dvss = ""
     "#version 330 core\n"
     "layout (location = 0) in vec3 aPos;\n"
     "void main()\n"
     "{\n"
     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
     "}\0";
     GLuint draw_vs = glCreateShader(GL_VERTEX_SHADER);
     glShaderSource(draw_vs, 1, (const char**)&dvss, NULL);
     glCompileShader(draw_vs);
     const char* dfss = ""
     "#version 330 core\n"
     "out vec4 FragColor;\n"
     "void main()\n"
     "{\n"
     "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
     "}\n\0";
     GLuint draw_fs = glCreateShader(GL_FRAGMENT_SHADER);
     glShaderSource(draw_fs, 1, (const char**)&dfss, NULL);
     glCompileShader(draw_fs);
     GLuint draw_prog = glCreateProgram();
     glAttachShader(draw_prog, draw_vs);
     glAttachShader(draw_prog, draw_fs);
     glLinkProgram(draw_prog);
     float pm[16] = { 0.0f };
     pm[0] = 2.0 / win_w;
     pm[5] = 2.0f / -win_h;
     pm[10] = -1.0f;
     pm[12] = -1.0;
     pm[13] = 1.0f;
     pm[15] = 1.0f;
     GLint u_pm = glGetUniformLocation(draw_prog, "u_pm");
     GLint u_color = glGetUniformLocation(draw_prog, "u_color");
     glUseProgram(draw_prog);
     glUniformMatrix4fv(u_pm, 1, GL_FALSE, pm);
     glUniform3f(u_color, 1.0f, 1.0f, 1.0f);
     /* ==================================================== */
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     while(!glfwWindowShouldClose(win)) {
          glBindFramebuffer(GL_FRAMEBUFFER, 0);
          glViewport(0, 0, w, h);
          glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          /*
          This is where we enable primitive restart; Note that we have one draw call
          but we're drawing multiple separate GL_LINE_STRIPs.
          */
          glEnable(GL_PRIMITIVE_RESTART);
          glPrimitiveRestartIndex(0xFFFFFFFE);
          glUseProgram(draw_prog);
          glBindVertexArray(VAO);

          glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, (GLvoid*)0);
          glfwSwapBuffers(win);
          glfwPollEvents();
     }
     glfwTerminate();
     return EXIT_SUCCESS;
}
void char_callback(GLFWwindow* win, unsigned int key) {
}
void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
     if (GLFW_RELEASE == action) {
          return;
     }
     switch(key) {
          case GLFW_KEY_SPACE: {
               break;
          }
          case GLFW_KEY_ESCAPE: {
               glfwSetWindowShouldClose(win, GL_TRUE);
               break;
          }
     };
}
void resize_callback(GLFWwindow* window, int width, int height) {
}
void cursor_callback(GLFWwindow* win, double x, double y) {
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
}
void button_callback(GLFWwindow* win, int bt, int action, int mods) {
     double mx = 0.0;
     double my = 0.0;
     glfwGetCursorPos(win, &mx, &my);
     if (GLFW_PRESS == action) {
     }
     else if (GLFW_RELEASE == action) {
     }
}
void error_callback(int err, const char* desc) {
     printf("GLFW error: %s (%d)\n", desc, err);
}
