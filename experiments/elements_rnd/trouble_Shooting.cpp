// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

//Use middle mouse button to rotate view
//Use WASD to walk through scene

/*

*/

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imguistyleserializer.h"
#include "EngineX.h"
#include "Geometry.h"
#include "Model.h"
#include "ui.h"

#include <stdio.h>
#include <string.h>
#include <memory>

struct coordinates
{
     glm::vec3 coords;
     GLfloat radians;
     float near;
     float far;
     float angle;
};

int main(int, char**)
{
     printf("Initializing.\n");
     //initialize the Camera class
     int fbWidth = 1920;
     int fbHeight = 1080;
     Camera * camera = new Camera(fbWidth, fbHeight);
     EngineX * engineX = new EngineX(camera);

     engineX->init_glfw();
     engineX->init_ImGui();

     glm::vec4 viewModel( 1.0f, 1.0f, 1.0f, 0.0f);
     glm::vec3 * cameraPosition = engineX->camera->getPositionVector();
     glm::vec3 * cameraFront = engineX->camera->getFrontVector();
     glm::vec3 * cameraHeadsUp = engineX->camera->getHeadsUpVector();
     glm::vec3 cameraProp( 0.1f, 100.0f, *engineX->camera->Zoom);

     printf("Starting main loop.\n");
     //---------------------------------------
     // Main loop
     bool show_demo_window = false;

     float backgroundColor[4];

     backgroundColor[0]=0.35f; backgroundColor[1]=0.35f; backgroundColor[2]=0.35f; backgroundColor[3]=0.0f;

     printf("Initializing shaders and objects.\n");

     float cube_vertices[] = {
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
     unsigned int VAO, VBO, EBO, VAO_2, VBO_2, EBO_2;

     glGenVertexArrays(1, &VAO);
     glGenBuffers(1, &VBO);
     glGenBuffers(1, &EBO);

     glBindVertexArray(VAO);

     glBindBuffer(GL_ARRAY_BUFFER, VBO);

     glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_quads_indices), cube_quads_indices, GL_STATIC_DRAW);

     // set the vertex attribute pointers
     glEnableVertexAttribArray(0);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
     glBindVertexArray(0);

     glGenVertexArrays(1, &VAO_2);
     glGenBuffers(1, &VBO_2);
     glGenBuffers(1, &EBO_2);

     glBindVertexArray(VAO_2);

     glBindBuffer(GL_ARRAY_BUFFER, VBO_2);

     glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_2);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_quads_edges), cube_quads_edges, GL_STATIC_DRAW);

     // set the vertex attribute pointers
     glEnableVertexAttribArray(0);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
     glBindVertexArray(0);


     Shader o_shader = Shader("../../resources/shaders/cube_quads.vs", "../../resources/shaders/cube_quads.fs");
     //o_shader.use();
     Geometry * cubelight = new Geometry();
     cubelight->shader = new Shader("../../resources/shaders/light_materials.vs", "../../resources/shaders/light_materials.fs");
     cubelight->enable_shader();
     cubelight->init_cube();

     glm::vec3 cubelightPos(1.2f, 1.0f, 2.0f);

     // variables for selected objects.
     std::string selectedType = "container";
     int selectedIndex = -2;

     printf("glfw main loop.\n");
     while (!glfwWindowShouldClose(engineX->window))
     {
          GLfloat currentFrame = (GLfloat) glfwGetTime();
          engineX->camera->deltaTime = currentFrame - engineX->camera->lastFrame;
          engineX->camera->lastFrame = currentFrame;

          glfwPollEvents();

          displayUI(engineX->camera, show_demo_window, backgroundColor, selectedIndex, selectedType);

          glfwMakeContextCurrent(engineX->window);
          glfwGetFramebufferSize(engineX->window, &engineX->window_w, &engineX->window_h);
          glViewport(0, 0, engineX->window_w, engineX->window_h);
          glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
          glEnable(GL_DEPTH_TEST);

          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          glEnable(GL_CULL_FACE);
          glCullFace(GL_BACK);

          engineX->camera->computeMatricesFromInputs();

          // create transformations
          glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
          glm::mat4 view          = glm::mat4(1.0f);
          glm::mat4 projection    = glm::mat4(1.0f);

          view = engineX->camera->processViewMatrix();
          projection = glm::perspective(glm::radians(*engineX->camera->Zoom), (float)engineX->window_w / (float)engineX->window_h, cameraProp.x, cameraProp.y);

          model = glm::mat4(1.0f);

          glEnable(GL_PRIMITIVE_RESTART);
          glPrimitiveRestartIndex(0xFFFFFFFE);

          o_shader.use();
          glBindVertexArray(VAO_2);
          //obj.enable_shader();
          o_shader.setMat4("projection", projection);
          o_shader.setMat4("view", view);
          o_shader.setMat4("model", model);

          glLineWidth(1.1f);
          glPointSize(1.1f);
          int rendermode = 0;
          o_shader.setInt("mode", rendermode);
          o_shader.setVec3("objectColor", 0.0f, 0.0f, 1.0f);

          glDrawElements(GL_LINES, sizeof(cube_quads_edges)/sizeof(cube_quads_edges[0]), GL_UNSIGNED_INT, 0);
          glBindVertexArray(0);
          glDisable(GL_PRIMITIVE_RESTART);
          //std::cout << sizeof(edges)/sizeof(edges[0]) << std::endl;
          rendermode = 4;
          o_shader.use();
          o_shader.setInt("mode", rendermode);
          o_shader.setVec3("objectColor", 0.45f, 0.45f, 0.45f);
          o_shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
          glm::mat4 scale = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
          o_shader.setMat4("model", scale);
          glBindVertexArray(VAO);
          glDrawElements(GL_TRIANGLES, sizeof(cube_quads_indices)/sizeof(cube_quads_indices[0]), GL_UNSIGNED_INT, 0);
          glBindVertexArray(0);

          cubelight->enable_shader();
          cubelight->shader->setMat4("projection", projection);
          cubelight->shader->setMat4("view", view);

          model = glm::mat4(1.0f);
          model = glm::translate(model, cubelightPos);
          model = glm::scale(model, glm::vec3(0.2f));
          cubelight->shader->setMat4("model", model);
          cubelight->draw_cube(GL_TRIANGLES);

          if(engineX->show_ui == true)
          ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

          glfwMakeContextCurrent(engineX->window);
          glfwSwapBuffers(engineX->window);
     }

     // Cleanup
     ImGui_ImplOpenGL3_Shutdown();
     ImGui_ImplGlfw_Shutdown();
     ImGui::DestroyContext();

     //delete_object;
     cubelight->delete_object();
     glfwDestroyWindow(engineX->window);
     glfwTerminate();

     return 0;
}
