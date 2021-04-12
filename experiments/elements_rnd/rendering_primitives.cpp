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

#include "PrimitiveData.h"
#include "Primitive.h"

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
     Camera camera = Camera(fbWidth, fbHeight);
     EngineX * engineX = new EngineX(&camera);

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

     Primitive cube(cube_quads_vertices, cube_quads_indices, cube_quads_edges);
     cube.prim_shader = new Shader("../../resources/shaders/cube_quads.vs", "../../resources/shaders/cube_quads.fs");
     cube.initObject();
     cube.initEdges();
     /*
     for(int i=0; i < cube.vertexList.size(); i++)
     {
       std::cout << cube.vertexList[i].Position.x << " " << cube.vertexList[i].Position.y << " " << cube.vertexList[i].Position.z << std::endl;

     }
     for(int i=0; i < 24; i+=3)
     {
       std::cout << cube.debug_data[i] << " " << cube.debug_data[i+1] << " " << cube.debug_data[i+2] << std::endl;
     }
     for(int i=0; i < cube.faceIndices.size(); i++)
     {
       std::cout <<cube.faceIndices[i] << " ";
     }
     std::cout << std::endl;
     for(int i=0; i < 71; i++)
     {
       std::cout << i+1 << " " << cube.primEdges[i] << std::endl;
     }
     */
     Geometry * cubelight = new Geometry();
     cubelight->shader = new Shader("../../resources/shaders/light_materials.vs", "../../resources/shaders/light_materials.fs");
     cubelight->enableShader();
     cubelight->initCube();

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

          cube.prim_shader->use();
          //obj.enable_shader();
          cube.prim_shader->setMat4("projection", projection);
          cube.prim_shader->setMat4("view", view);
          cube.prim_shader->setMat4("model", model);

          glLineWidth(1.1f);
          glPointSize(1.1f);
          int rendermode = 0;
          cube.prim_shader->setInt("mode", rendermode);
          cube.prim_shader->setVec3("objectColor", 0.0f, 0.0f, 1.0f);
          cube.drawEdges();

          rendermode = 4;
          cube.prim_shader->setInt("mode", rendermode);
          cube.prim_shader->setVec3("objectColor", 0.45f, 0.45f, 0.45f);
          cube.prim_shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
          glm::mat4 scale = glm::scale(model, glm::vec3(0.99f, 0.99f, 0.99f));
          cube.prim_shader->setMat4("model", scale);
          cube.drawObject();

          cubelight->enableShader();
          cubelight->shader->setMat4("projection", projection);
          cubelight->shader->setMat4("view", view);

          model = glm::mat4(1.0f);
          model = glm::translate(model, cubelightPos);
          model = glm::scale(model, glm::vec3(0.2f));
          cubelight->shader->setMat4("model", model);
          cubelight->drawCube(GL_TRIANGLES);

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
     cubelight->deleteObject();
     glfwDestroyWindow(engineX->window);
     glfwTerminate();

     return 0;
}
