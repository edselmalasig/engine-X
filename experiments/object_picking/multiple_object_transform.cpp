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
#include "ImGuizmo.h"
#include "EngineX.h"
#include "Geometry.h"

#include <stdio.h>
#include <string.h>
#include <memory>

void EditTransform(const Camera * camera, float * matrix, float * view, float * proj)
{
     static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::ROTATE);
     static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);

     if (ImGui::IsKeyPressed(90))
     mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
     if (ImGui::IsKeyPressed(69))
     mCurrentGizmoOperation = ImGuizmo::ROTATE;
     if (ImGui::IsKeyPressed(82)) // r Key
     mCurrentGizmoOperation = ImGuizmo::SCALE;
     if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
     mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
     ImGui::SameLine();
     if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
     mCurrentGizmoOperation = ImGuizmo::ROTATE;
     ImGui::SameLine();
     if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
     mCurrentGizmoOperation = ImGuizmo::SCALE;
     float matrixTranslation[3], matrixRotation[3], matrixScale[3];

     ImGuizmo::DecomposeMatrixToComponents(matrix, matrixTranslation, matrixRotation, matrixScale);
     ImGui::InputFloat3("Tr", matrixTranslation, 3);
     ImGui::InputFloat3("Rt", matrixRotation, 3);
     ImGui::InputFloat3("Sc", matrixScale, 3);

     ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, matrix);

     if (mCurrentGizmoOperation != ImGuizmo::SCALE)
     {
          if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
          mCurrentGizmoMode = ImGuizmo::LOCAL;
          ImGui::SameLine();
          if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
          mCurrentGizmoMode = ImGuizmo::WORLD;
     }
     static bool useSnap(false);
     if (ImGui::IsKeyPressed(83))
     useSnap = !useSnap;
     ImGui::Checkbox("", &useSnap);
     ImGui::SameLine();
     /*
     vec_t snap;
     switch (mCurrentGizmoOperation)
     {
     case ImGuizmo::TRANSLATE:
     snap = config.mSnapTranslation;
     ImGui::InputFloat3("Snap", &snap.x);
     break;
     case ImGuizmo::ROTATE:
     snap = config.mSnapRotation;
     ImGui::InputFloat("Angle Snap", &snap.x);
     break;
     case ImGuizmo::SCALE:
     snap = config.mSnapScale;
     ImGui::InputFloat("Scale Snap", &snap.x);
     break;
}
*/

ImGuiIO& io = ImGui::GetIO();
ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
ImGuizmo::Manipulate(view, proj, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL, NULL);
}

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
     //lo_rectangle->lo_shader = new Shader("rectangle.vs", "rectangle.fs");
     g_cube->lo_shader = new Shader("../../resources/shaders/spotlight.vs", "../../resources/shaders/spotlight.fs");
     g_cube->enable_shader();
     g_cube->init_cube_wntc();
     g_cube->init_texture(0, "../../resources/textures/container2.png");
     g_cube->init_texture(1, "../../resources/textures/container2_specular.png");
     g_cube->lo_shader->setInt("material.diffuse", 0);
     g_cube->lo_shader->setInt("material.specular", 1);

     g_cube->lo_shader->use();
     g_cube->lo_shader->setInt("material.diffuse", 0);
     g_cube->lo_shader->setInt("material.specular", 1);

     Geometry * g_cubelamp = new Geometry();
     g_cubelamp->lo_shader = new Shader("../../resources/shaders/light_materials.vs", "../../resources/shaders/light_materials.fs");
     g_cubelamp->enable_shader();
     g_cubelamp->init_cube();

     glm::vec3 cubelampPos(1.2f, 1.0f, 2.0f);

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

     // variables for selected objects.
     std::string selectedType = "container";
     int selectedIndex = -2;
     std::vector<int> selectionVec;
     printf("glfw main loop.\n");
     while (!glfwWindowShouldClose(engineX->window))
     {
          GLfloat currentFrame = (GLfloat) glfwGetTime();
          engineX->camera->deltaTime = currentFrame - engineX->camera->lastFrame;
          engineX->camera->lastFrame = currentFrame;

          glfwWaitEvents();

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
               ImGuizmo::BeginFrame();
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

                    if( selectedIndex > -1)
                    ImGui::Text("Selection: %s - %i\n", selectedType.c_str(), selectedIndex);
                    else
                    ImGui::Text("Selection: none");

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
                    if (ImGui::Begin("Information", &p_open, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
                    {
                         ImGui::Text("engine-X overlay\n" "in the corner of the screen.\n");
                         ImGui::Separator();
                         if (ImGui::IsMousePosValid())
                         ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
                         else
                         ImGui::Text("Mouse Position: <invalid>");
                         if(selectionVec.empty()){
                              ImGui::Text("Selection: none");
                         }
                         else
                         {
                              ImGui::Text("Selection: %s - count %i", selectedType.c_str(), selectionVec.size());
                              std::string indexString;
                              for(int i=0; i < selectionVec.size(); i++){
                                   indexString += std::to_string(selectionVec.at(i)) + " ";
                              }
                              ImGui::Text("%s\n", indexString.c_str());
                              indexString = " ";
                         }

                    }
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

          g_cube->enable_shader();
          g_cube->lo_shader->setVec3("light.position", *engineX->camera->getPositionVector());
          g_cube->lo_shader->setVec3("light.direction", *engineX->camera->getFrontVector());
          g_cube->lo_shader->setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
          g_cube->lo_shader->setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));

          g_cube->lo_shader->setVec3("viewPos", *engineX->camera->getPositionVector());

          g_cube->lo_shader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
          g_cube->lo_shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
          g_cube->lo_shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
          g_cube->lo_shader->setFloat("light.constant", 1.0f);
          g_cube->lo_shader->setFloat("light.linear", 0.09f);
          g_cube->lo_shader->setFloat("light.quadratic", 0.032f);

          g_cube->lo_shader->setFloat("material.shininess", 32.0f);

          g_cube->lo_shader->setMat4("projection", projection);
          g_cube->lo_shader->setMat4("view", view);
          model = glm::mat4(1.0f);
          g_cube->lo_shader->setMat4("model", model);

          bool reprint = true;
          bool selectionBool = false;

          for (unsigned int i = 0; i < 10; i++)
          {
               // calculate the model matrix for each object and pass it to shader before drawing
               glm::mat4 model = glm::mat4(1.0f);
               glm::mat4 rotate = glm::mat4(1.0f);
               glm::mat4 translate = glm::mat4(1.0f);

               //transform model matrix with translate x rotate
               translate = glm::translate(translate, cubePositions[i]);
               float angle = 20.0f * i;
               rotate = glm::rotate(rotate, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));


               model = translate * rotate;
               g_cube->lo_shader->setMat4("model", model);

               g_cube->renderTexLayer(1);
               glPointSize(7.0f);
               g_cube->draw_cube(GL_POINTS);
               g_cube->draw_cube(GL_TRIANGLES);

               double mousePosX, mousePosY;
               int mousestate = glfwGetMouseButton(engineX->window, GLFW_MOUSE_BUTTON_LEFT);
               if(mousestate == GLFW_PRESS)
               {
                    glfwGetCursorPos(engineX->window, &mousePosX, &mousePosY);
                    glm::vec3 ray_origin;
                    glm::vec3 ray_direction;

                    engineX->ScreenPosToWorldRay(
                         mousePosX, mousePosY,
                         fbWidth, fbHeight,
                         view, projection,
                         ray_origin, ray_direction
                    );

                    //engineX->Get3DRayUnderMouse(&ray_origin, &ray_direction);
                    float intersection_distance;
                    glm::vec3 aabb_min(-0.5f, -0.5f, -0.5f);
                    glm::vec3 aabb_max( 0.5f,  0.5f,  0.5f);
                    selectionBool = engineX->RayAABBIntersection(
                         ray_origin,
                         ray_direction,
                         aabb_min,
                         aabb_max,
                         model,
                         intersection_distance
                    );

                    if ( selectionBool ){
                         selectedIndex = i;
                         selectedType = "container";
                         #include <algorithm>

                         std::vector<int>::iterator it;
                         it = find(selectionVec.begin(), selectionVec.end(), selectedIndex);
                         if(it != selectionVec.end())
                         selectionVec.erase(it);
                         else
                         selectionVec.push_back(selectedIndex);

                    }

               }
               int editState = glfwGetKey(engineX->window, GLFW_KEY_L);
               if(editState == GLFW_PRESS)
               {
                    ImGui::NewFrame();
                    ImGuizmo::BeginFrame();
                    if(selectedIndex > -1)
                    EditTransform(engineX->camera, (float *) glm::value_ptr(model),
                    glm::value_ptr(view), glm::value_ptr(projection));
                    //ImGui::End();
                    ImGuizmo::Enable(TRUE);
                    ImGui::Render();
               }
               int keystate = glfwGetKey(engineX->window, GLFW_KEY_P);
               if(keystate == GLFW_PRESS){
                    selectionVec.clear();
                    selectionBool = false;
                    selectedIndex = -1;

               }

          }
          selectionBool = false;


          model = glm::mat4(1.0f);

          g_cubelamp->enable_shader();
          g_cubelamp->lo_shader->setMat4("projection", projection);
          g_cubelamp->lo_shader->setMat4("view", view);

          model = glm::mat4(1.0f);
          model = glm::translate(model, cubelampPos);
          model = glm::scale(model, glm::vec3(0.2f));
          g_cubelamp->lo_shader->setMat4("model", model);
          g_cubelamp->draw_cube(GL_TRIANGLES);

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
     g_cube->delete_object();
     g_cubelamp->delete_object();
     glfwDestroyWindow(engineX->window);
     glfwTerminate();

     return 0;
}
