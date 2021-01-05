#ifndef _UI_
#define _UI_

#include "camera.h"
#include <stdio.h>

void displayUI(Camera * cam, bool show_demo_window, float * backgroundColor, int selectedIndex, string selectedType){
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

          ImGui::ColorEdit3("Background color", backgroundColor); // Edit 3 floats representing a color

          ImGui::DragFloat("View Pos X", &cam->getPositionVector()->x, 0.01);
          ImGui::DragFloat("View Pos Y", &cam->getPositionVector()->y, 0.01);
          ImGui::DragFloat("View Pos Z", &cam->getPositionVector()->z, 0.01);

          ImGui::DragFloat("View Front X", &cam->getFrontVector()->x, 0.01);
          ImGui::DragFloat("View Front Y", &cam->getFrontVector()->y, 0.01);
          ImGui::DragFloat("View Front Z", &cam->getFrontVector()->z, 0.01);

          ImGui::DragFloat("View Heads Up X", &cam->getHeadsUpVector()->x, 0.01);
          ImGui::DragFloat("View Heads Up Y", &cam->getHeadsUpVector()->y, 0.01);
          ImGui::DragFloat("View Heads Up Z", &cam->getHeadsUpVector()->z, 0.01);

          glm::vec3 cameraProp( 0.1f, 100.0f, *cam->Zoom);

          ImGui::DragFloat("Projection radians", &cameraProp.z, 0.5f);
          ImGui::DragFloat("Projection zNear", &cameraProp.x, 0.01f);
          ImGui::DragFloat("Projection zFar", &cameraProp.y, 0.01f);

          ImGui::DragFloat("degrees Yaw", &cam->Yaw, 0.1f);
          ImGui::DragFloat("degrees Pitch", &cam->Pitch, 0.1f);



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


#endif
