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
#include "texture.h"

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

     float clearColor[4];

     clearColor[0]=0.35f; clearColor[1]=0.35f; clearColor[2]=0.35f; clearColor[3]=0.0f;

     printf("Initializing shaders and objects.\n");

     Geometry * g_cube = new Geometry();
     //lo_rectangle->shader = new Shader("rectangle.vs", "rectangle.fs");
     g_cube->shader = new Shader("../../resources/shaders/light_casters.vs", "../../resources/shaders/light_casters.fs");
     g_cube->enableShader();
     g_cube->initCubeWNTC();
     g_cube->initTexture(0, "../../resources/textures/container2.png");
     g_cube->initTexture(1, "../../resources/textures/container2_specular.png");
     //g_cube->shader->setInt("material.diffuse", 0);
     //g_cube->shader->setInt("material.specular", 1);

     Geometry * g_cubelamp = new Geometry();
     g_cubelamp->shader = new Shader("../../resources/shaders/light_materials.vs", "../../resources/shaders/light_materials.fs");
     g_cubelamp->enableShader();
     g_cubelamp->initCube();

     //glm::vec3 cubelampPos(1.2f, 1.0f, 2.0f);
     // positions of the point lights
     glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
     };
    // first, configure the cube's VAO (and VBO)
     // positions all containers
     glm::vec3 cubePositions[] = {
          glm::vec3( 0.0f,  0.0f,  0.0f),
          glm::vec3( 2.0f,  5.0f, -15.0f),
          glm::vec3(-1.5f, -2.2f, -2.5f),
          glm::vec3(-3.8f, -2.0f, -12.3f),
          glm::vec3( 2.4f, -0.4f, -3.5f),
          glm::vec3(-1.7f,  3.0f, -7.5f),
          glm::vec3( 1.3f, -2.0f, -2.5f),
          glm::vec3( 1.5f,  2.0f, -2.5f),
          glm::vec3( 1.5f,  0.2f, -1.5f),
          glm::vec3(-1.3f,  1.0f, -1.5f)
     };
     // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    unsigned int diffuseMap = loadTexture("../../resources/textures/container2.png");
    unsigned int specularMap = loadTexture("../../resources/textures/container2_specular.png");

     g_cubelamp->shader->setInt("material.diffuse", 0);
     g_cubelamp->shader->setInt("material.specular", 1);


     printf("glfw main loop.\n");
     while (!glfwWindowShouldClose(engineX->window))
     {
          // Poll and handle events (inputs, window resize, etc.)
          // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
          // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
          // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
          // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
          // Poll and handle events (inputs, window resize, etc.)
          // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
          // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
          // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
          // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
          GLfloat currentFrame = (GLfloat) glfwGetTime();
          engineX->camera->deltaTime = currentFrame - engineX->camera->lastFrame;
          engineX->camera->lastFrame = currentFrame;

          glfwPollEvents();

          {
               // Start the Dear ImGui frame
               ImGui_ImplOpenGL3_NewFrame();
               ImGui_ImplGlfw_NewFrame();
               ImGui::NewFrame();

               // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).

               //Put this in a new function.
               if (show_demo_window)
               ImGui::ShowDemoWindow(&show_demo_window);

               // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
               {
                    static float f = 0.0f;
                    static int counter = 0;
                    ImGui::Begin("Coordinate Controls");
                    ImGui::Checkbox("Show Control Window", &show_demo_window);      // Edit bools storing our window open/close state

                    ImGui::ColorEdit3("Background color", clearColor); // Edit 3 floats representing a color

                    ImGui::DragFloat("View Pos X", &cameraPosition->x, 0.01);
                    ImGui::DragFloat("View Pos Y", &cameraPosition->y, 0.01);
                    ImGui::DragFloat("View Pos Z", &cameraPosition->z, 0.01);

                    ImGui::DragFloat("View Front X", &cameraFront->x, 0.01);
                    ImGui::DragFloat("View Front Y", &cameraFront->y, 0.01);
                    ImGui::DragFloat("View Front Z", &cameraFront->z, 0.01);

                    ImGui::DragFloat("View Heads Up X", &cameraHeadsUp->x, 0.01);
                    ImGui::DragFloat("View Heads Up Y", &cameraHeadsUp->y, 0.01);
                    ImGui::DragFloat("View Heads Up Z", &cameraHeadsUp->z, 0.01);

                    ImGui::DragFloat("Projection radians", &cameraProp.z, 0.5f);
                    ImGui::DragFloat("Projection zNear", &cameraProp.x, 0.01f);
                    ImGui::DragFloat("Projection zFar", &cameraProp.y, 0.01f);

                    ImGui::DragFloat("degrees Yaw", &engineX->camera->Yaw, 0.1f);
                    ImGui::DragFloat("degrees Pitch", &engineX->camera->Pitch, 0.1f);

                    ImGui::Text("\n");
                    ImGui::Text("Please modify the current style in:");
                    ImGui::Text("ImGui Test->Window Options->Style Editor");
                    static bool loadCurrentStyle = false;
                    static bool saveCurrentStyle = false;
                    static bool resetCurrentStyle = false;
                    loadCurrentStyle = ImGui::Button("Load Saved Style");
                    saveCurrentStyle = ImGui::Button("Save Current Style");
                    resetCurrentStyle = ImGui::Button("Reset Current Style");
                    if (loadCurrentStyle)   {
                         if (!ImGui::LoadStyle("./myimgui.style",ImGui::GetStyle()))   {
                              fprintf(stderr,"Warning: \"./myimgui.style\" not present.\n");
                         }
                    }
                    if (saveCurrentStyle)   {
                         if (!ImGui::SaveStyle("./myimgui.style",ImGui::GetStyle()))   {
                              fprintf(stderr,"Warning: \"./myimgui.style\" cannot be saved.\n");
                         }
                    }
                    if (resetCurrentStyle)  ImGui::GetStyle() = ImGuiStyle();

                    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                    ImGui::End();

               }

               // Rendering
               ImGui::Render();
          }

          glfwMakeContextCurrent(engineX->window);
          glfwGetFramebufferSize(engineX->window, &engineX->window_w, &engineX->window_h);
          glViewport(0, 0, engineX->window_w, engineX->window_h);
          glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
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

          g_cube->enableShader();
          //g_cube->shader->setVec3("light.position", cubelampPos);
          g_cube->shader->setMat4("projection", projection);
          g_cube->shader->setMat4("view", view);

          // world transformation
          //glm::mat4 model = glm::mat4(1.0f);
          g_cube->shader->setMat4("model", model);

          // bind diffuse map
          glActiveTexture(GL_TEXTURE0);
          glBindTexture(GL_TEXTURE_2D, diffuseMap);
          // bind specular map
          glActiveTexture(GL_TEXTURE1);
          glBindTexture(GL_TEXTURE_2D, specularMap);

          g_cube->shader->setVec3("viewPos", *engineX->camera->getPositionVector());

          // directional light
          g_cube->shader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
          g_cube->shader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
          g_cube->shader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
          g_cube->shader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
          // point light 1
          g_cube->shader->setVec3("pointLights[0].position", pointLightPositions[0]);
          g_cube->shader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
          g_cube->shader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
          g_cube->shader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
          g_cube->shader->setFloat("pointLights[0].constant", 1.0f);
          g_cube->shader->setFloat("pointLights[0].linear", 0.09);
          g_cube->shader->setFloat("pointLights[0].quadratic", 0.032);
          // point light 2
          g_cube->shader->setVec3("pointLights[1].position", pointLightPositions[1]);
          g_cube->shader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
          g_cube->shader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
          g_cube->shader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
          g_cube->shader->setFloat("pointLights[1].constant", 1.0f);
          g_cube->shader->setFloat("pointLights[1].linear", 0.09);
          g_cube->shader->setFloat("pointLights[1].quadratic", 0.032);
          // point light 3
          g_cube->shader->setVec3("pointLights[2].position", pointLightPositions[2]);
          g_cube->shader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
          g_cube->shader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
          g_cube->shader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
          g_cube->shader->setFloat("pointLights[2].constant", 1.0f);
          g_cube->shader->setFloat("pointLights[2].linear", 0.09);
          g_cube->shader->setFloat("pointLights[2].quadratic", 0.032);
          // point light 4
          g_cube->shader->setVec3("pointLights[3].position", pointLightPositions[3]);
          g_cube->shader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
          g_cube->shader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
          g_cube->shader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
          g_cube->shader->setFloat("pointLights[3].constant", 1.0f);
          g_cube->shader->setFloat("pointLights[3].linear", 0.09);
          g_cube->shader->setFloat("pointLights[3].quadratic", 0.032);
          // spotLight
          g_cube->shader->setVec3("spotLight.position", camera.Position);
          g_cube->shader->setVec3("spotLight.direction", camera.Front);
          g_cube->shader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
          g_cube->shader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
          g_cube->shader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
          g_cube->shader->setFloat("spotLight.constant", 1.0f);
          g_cube->shader->setFloat("spotLight.linear", 0.09);
          g_cube->shader->setFloat("spotLight.quadratic", 0.032);
          g_cube->shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
          g_cube->shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

          glBindVertexArray(g_cube->VAO);
          for (unsigned int i = 0; i < 10; i++)
          {
               model = glm::translate(model, cubePositions[i]);
               float angle = 20.0f * i;
               model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
               g_cube->shader->setMat4("model", model);


               g_cube->renderTexLayer(1);
               g_cube->drawCube(GL_TRIANGLES);
          }

          g_cubelamp->enableShader();
          g_cubelamp->shader->setMat4("projection", projection);
          g_cubelamp->shader->setMat4("view", view);


          glBindVertexArray(g_cubelamp->VAO);
          for (unsigned int i = 0; i < 4; i++)
          {
             model = glm::mat4(1.0f);
             model = glm::translate(model, pointLightPositions[i]);
             model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
             g_cubelamp->shader->setMat4("model", model);
             glDrawArrays(GL_TRIANGLES, 0, 36);
          }

          //draw_object(lo_rectangle);
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
     g_cube->deleteObject();
     g_cubelamp->deleteObject();
     glfwDestroyWindow(engineX->window);
     glfwTerminate();

     return 0;
}
