// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

//Use middle mouse button to reorient view
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

     float clearColor[] = { 0.35f, 0.35f, 0.35f, 0.0f };

     printf("Initializing shaders and objects.\n");
     // build and compile shaders
     // -------------------------
     Shader shader("./resources/shaders/stencil_testing.vs", "./resources/shaders/stencil_testing.fs");
     Shader shaderSingleColor("./resources/shaders/stencil_testing.vs", "./resources/shaders/stencil_single_color.fs");

     // set up vertex data (and buffer(s)) and configure vertex attributes
     // ------------------------------------------------------------------
     float cubeVertices[] = {
          // positions          // texture Coords
         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
          0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

         -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
     };
     float planeVertices[] = {
         // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
          5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
         -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
         -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

          5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
         -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
          5.0f, -0.5f, -5.0f,  2.0f, 2.0f
     };

     // cube VAO
     unsigned int cubeVAO, cubeVBO;
     glGenVertexArrays(1, &cubeVAO);
     glGenBuffers(1, &cubeVBO);
     glBindVertexArray(cubeVAO);
     glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
     glEnableVertexAttribArray(0);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(1);
     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
     glBindVertexArray(0);
     // plane VAO
     unsigned int planeVAO, planeVBO;
     glGenVertexArrays(1, &planeVAO);
     glGenBuffers(1, &planeVBO);
     glBindVertexArray(planeVAO);
     glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
     glEnableVertexAttribArray(0);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(1);
     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
     glBindVertexArray(0);

     // load textures
     // -------------
     unsigned int cubeTexture = loadTexture("./resources/textures/container.jpg");
     unsigned int floorTexture = loadTexture("./resources/textures/metal.png");

     // shader configuration
     // --------------------
     shader.use();
     shader.setInt("texture1", 0);
     //glEnable(GL_DEPTH_TEST);
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

          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          glEnable(GL_DEPTH_TEST);
          glDepthFunc(GL_LESS);
          engineX->camera->computeMatricesFromInputs();

          // create transformations
          glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
          glm::mat4 view          = glm::mat4(1.0f);
          glm::mat4 projection    = glm::mat4(1.0f);

          view = engineX->camera->processViewMatrix();
          projection = glm::perspective(glm::radians(*engineX->camera->Zoom), (float)engineX->window_w / (float)engineX->window_h, cameraProp.x, cameraProp.y);

          shaderSingleColor.use();
          model = glm::mat4(1.0f);
          shaderSingleColor.setMat4("view", view);
          shaderSingleColor.setMat4("projection", projection);


          shader.use();
          shader.setMat4("view", view);
          shader.setMat4("projection", projection);
          // draw floor as normal, but don't write the floor to the stencil buffer, we only care about the containers. We set its mask to 0x00 to not write to the stencil buffer.
          glStencilMask(0x00);
          // floor
          glBindVertexArray(planeVAO);
          glBindTexture(GL_TEXTURE_2D, floorTexture);
          shader.setMat4("model", glm::mat4(1.0f));
          glDrawArrays(GL_TRIANGLES, 0, 6);
          glBindVertexArray(0);
          // cubes
          // 1st. render pass, draw objects as normal, writing to the stencil buffer
          // --------------------------------------------------------------------
          glStencilFunc(GL_ALWAYS, 1, 0xFF);
          glStencilMask(0xFF);
          // cubes
          glBindVertexArray(cubeVAO);
          glActiveTexture(GL_TEXTURE0);
          glBindTexture(GL_TEXTURE_2D, cubeTexture);
          model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
          shader.setMat4("model", model);
          glDrawArrays(GL_TRIANGLES, 0, 36);
          model = glm::mat4(1.0f);
          model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
          shader.setMat4("model", model);
          glDrawArrays(GL_TRIANGLES, 0, 36);
          // floor
          // 2nd. render pass: now draw slightly scaled versions of the objects, this time disabling stencil writing.
          // Because the stencil buffer is now filled with several 1s. The parts of the buffer that are 1 are not drawn, thus only drawing
          // the objects' size differences, making it look like borders.
          // -----------------------------------------------------------------------------------------------------------------------------
          glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
          glStencilMask(0x00);
          glDisable(GL_DEPTH_TEST);
          shaderSingleColor.use();
          float scale = 1.1;
          // cubes
          glBindVertexArray(cubeVAO);
          glBindTexture(GL_TEXTURE_2D, cubeTexture);
          model = glm::mat4(1.0f);
          model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
          model = glm::scale(model, glm::vec3(scale, scale, scale));
          shaderSingleColor.setMat4("model", model);
          glDrawArrays(GL_TRIANGLES, 0, 36);
          model = glm::mat4(1.0f);
          model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
          model = glm::scale(model, glm::vec3(scale, scale, scale));
          shaderSingleColor.setMat4("model", model);
          glDrawArrays(GL_TRIANGLES, 0, 36);
          glBindVertexArray(0);
          glStencilMask(0xFF);
          glStencilFunc(GL_ALWAYS, 0, 0xFF);
          glEnable(GL_DEPTH_TEST);

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

     //delete_object(lo_rectangle);

     glfwDestroyWindow(engineX->window);
     glfwTerminate();

     return 0;
}
