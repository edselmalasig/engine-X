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
#include "initialize.h"
#include "Geometry.h"
#include "Model.h"

#include "mouse_picker.h"

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

     init_glfw();

     init_ImGui();

     glm::vec4 viewModel( 1.0f, 1.0f, 1.0f, 0.0f);
     glm::vec3 * cameraPosition = gcwui_C->g_cnc->getPositionVector();
     glm::vec3 * cameraFront = gcwui_C->g_cnc->getFrontVector();
     glm::vec3 * cameraHeadsUp = gcwui_C->g_cnc->getHeadsUpVector();
     glm::vec3 cameraProp( 0.1f, 100.0f, *gcwui_C->g_cnc->Zoom);

     printf("Starting main loop.\n");
     //---------------------------------------
     // Main loop
     bool show_demo_window = false;

     float clearColor[4];

     clearColor[0]=0.35f; clearColor[1]=0.35f; clearColor[2]=0.35f; clearColor[3]=0.0f;

     printf("Initializing shaders and objects.\n");

     Model nanosuit = Model("nanosuit/nanosuit.obj");
     Shader nanosuitShader = Shader("model_loading.vs", "model_loading.fs");

     nanosuitShader.use();

     printf("glfw main loop.\n");
     while (!glfwWindowShouldClose(gcwui_C->window))
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
          gcwui_C->g_cnc->deltaTime = currentFrame - gcwui_C->g_cnc->lastFrame;
          gcwui_C->g_cnc->lastFrame = currentFrame;

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

                    ImGui::DragFloat("degrees Yaw", &gcwui_C->g_cnc->Yaw, 0.1f);
                    ImGui::DragFloat("degrees Pitch", &gcwui_C->g_cnc->Pitch, 0.1f);

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

          glfwMakeContextCurrent(gcwui_C->window);
          glfwGetFramebufferSize(gcwui_C->window, &gcwui_C->display_w, &gcwui_C->display_h);
          glViewport(0, 0, gcwui_C->display_w, gcwui_C->display_h);
          glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
          glEnable(GL_DEPTH_TEST);

          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          glEnable(GL_CULL_FACE);
          glCullFace(GL_BACK);

          gcwui_C->g_cnc->computeMatricesFromInputs();

          // create transformations
          glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
          glm::mat4 view          = glm::mat4(1.0f);
          glm::mat4 projection    = glm::mat4(1.0f);

          view = gcwui_C->g_cnc->processViewMatrix();
          projection = glm::perspective(glm::radians(*gcwui_C->g_cnc->Zoom), (float)gcwui_C->display_w / (float)gcwui_C->display_h, cameraProp.x, cameraProp.y);

          nanosuitShader.setMat4("projection", projection);
          nanosuitShader.setMat4("view", view);

          model = glm::translate(model, glm::vec3(0.0f, -1.55f, 0.0f));
          model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
          nanosuitShader.setMat4("model", model);
          nanosuit.Draw(nanosuitShader);

          model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

          bool selectionBool = false;
          /*{
               glm::vec3 v1, v2;
               Get3DRayUnderMouse(&v1, &v2);
               selectionBool = RaySphereCollision(glm::vec3(0.0f, 0.0f, 0.0f), 0.5f, v1, v2);
          }*/

          {
               double mousePosX, mousePosY;
               glfwGetCursorPos(gcwui_C->window, &mousePosX, &mousePosY);

               glm::vec3 ray_origin;
               glm::vec3 ray_direction;

               ScreenPosToWorldRay(
                    mousePosX, mousePosY,
                    gcwui_C->display_w, gcwui_C->display_h,
                    view, projection,
                    ray_origin, ray_direction
               );
               float intersection_distance;
               glm::vec3 aabb_min(-1.0f, -1.0f, -1.0f);
               glm::vec3 aabb_max( 1.0f,  1.0f,  1.0f);
               selectionBool = TestRayOBBIntersection(
                                                       ray_origin,
                                                       ray_direction,
                                                       aabb_min,
                                                       aabb_max,
                                                       model,
                                                       intersection_distance
                                                  );
          }

          if ( selectionBool )
          std::cout << "nanosuit has been picked. " << std::endl;// << mousePosX << " " << mousePosY << std::endl;
          else
          std::cout << "engine-X[running]" << std::endl;//mousePosX << " " << mousePosY << std::endl;

          //draw_object(lo_rectangle);
          if(gcwui_C->show_ui == true)
          ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

          glfwMakeContextCurrent(gcwui_C->window);
          glfwSwapBuffers(gcwui_C->window);
     }

     // Cleanup
     ImGui_ImplOpenGL3_Shutdown();
     ImGui_ImplGlfw_Shutdown();
     ImGui::DestroyContext();

     //delete_object(lo_rectangle);

     glfwDestroyWindow(gcwui_C->window);
     glfwTerminate();

     return 0;
}
