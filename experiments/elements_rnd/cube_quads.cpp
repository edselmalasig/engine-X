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

     GLuint indices[] = {
          0, 4, 6, 2, 0, 6,
          3, 2, 6, 7, 3, 6,
          7, 6, 4, 5, 7, 4,
          5, 1, 3, 7, 5, 3,
          1, 0, 2, 3, 1, 2,
          5, 4, 0, 1, 5, 0
     };
     unsigned int VAO_4, VBO_4, EBO_4, VAO_2, VBO_2, EBO_2;

     glGenVertexArrays(1, &VAO_4);
     glGenBuffers(1, &VBO_4);
     glGenBuffers(1, &EBO_4);

     glBindVertexArray(VAO_4);

     glBindBuffer(GL_ARRAY_BUFFER, VBO_4);

     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_4);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

     // set the vertex attribute pointers
     glEnableVertexAttribArray(0);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
     glBindVertexArray(0);

     glGenVertexArrays(1, &VAO_2);
     glGenBuffers(1, &VBO_2);
     glGenBuffers(1, &EBO_2);

     glBindVertexArray(VAO_2);

     glBindBuffer(GL_ARRAY_BUFFER, VBO_2);

     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_2);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(edges), edges, GL_STATIC_DRAW);

     // set the vertex attribute pointers
     glEnableVertexAttribArray(0);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
     glBindVertexArray(0);


     Shader o_shader = Shader("shaders/cube_quads.vs", "shaders/cube_quads.fs");
     //o_shader.use();
     Geometry * cubelight = new Geometry();
     cubelight->lo_shader = new Shader("shaders/light_materials.vs", "shaders/light_materials.fs");
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

                    {
                         const float DISTANCE = 10.0f;
                         static int corner = 0;
                         ImGuiIO& io = ImGui::GetIO();
                         bool p_open;
                         p_open = true;
                         if (corner != -1)
                         {
                              ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
                              ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
                              ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
                         }
                         ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
                         if (ImGui::Begin("Example: Simple overlay", &p_open, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
                         {
                              ImGui::Text("Simple overlay\n" "in the corner of the screen.\n" "(right-click to change position)");
                              ImGui::Separator();
                              if (ImGui::IsMousePosValid())
                              ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
                              else
                              ImGui::Text("Mouse Position: <invalid>");
                              if( selectedIndex > -1)
                              ImGui::Text("Selection: %s - %i\n", selectedType.c_str(), selectedIndex);
                              else
                              ImGui::Text("Selection: none");

                         }
                         ImGui::End();
                    }

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

          model = glm::mat4(1.0f);

          glEnable(GL_PRIMITIVE_RESTART);
          glPrimitiveRestartIndex(0xFFFFFFFE);

          o_shader.use();
          glBindVertexArray(VAO_2);
          //obj.enable_shader();
          o_shader.setMat4("projection", projection);
          o_shader.setMat4("view", view);
          o_shader.setMat4("model", model);

          glLineWidth(10.0f);
          glPointSize(10.0f);
          int rendermode = 0;
          o_shader.setInt("mode", rendermode);
          o_shader.setVec3("objectColor", 0.0f, 0.0f, 1.0f);

          glDrawElements(GL_LINES, sizeof(edges)/sizeof(edges[0]), GL_UNSIGNED_INT, 0);
          glBindVertexArray(0);
          glDisable(GL_PRIMITIVE_RESTART);
          //std::cout << sizeof(edges)/sizeof(edges[0]) << std::endl;
          rendermode = 4;
          o_shader.use();
          o_shader.setInt("mode", rendermode);
          o_shader.setVec3("objectColor", 0.45f, 0.45f, 0.45f);
          o_shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
          glm::mat4 scale = glm::scale(model, glm::vec3(0.99f, 0.99f, 0.99f));
          o_shader.setMat4("model", scale);
          glBindVertexArray(VAO_4);
          glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_INT, 0);
          glBindVertexArray(0);

          cubelight->enable_shader();
          cubelight->lo_shader->setMat4("projection", projection);
          cubelight->lo_shader->setMat4("view", view);

          model = glm::mat4(1.0f);
          model = glm::translate(model, cubelightPos);
          model = glm::scale(model, glm::vec3(0.2f));
          cubelight->lo_shader->setMat4("model", model);
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
