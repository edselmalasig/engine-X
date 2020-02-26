#ifndef GCWUICONTROLS_H
#define GCWUICONTROLS_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imguistyleserializer.h"

#include "camera.h"

#include <stdio.h>
#include <string.h>
#include <memory.h>

class gcwuiControls
{
public:
    gcwuiControls();
    gcwuiControls(Camera &cam);
    //GLFW Variables
    char glsl_version[50];
    int display_w;
    int display_h;
    GLFWwindow* window;

    //ImGuiIO * io = NULL;
    bool show_demo_window = false;
    bool show_another_window;
    bool show_ui = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    //camera and controls
    Camera * camera;
    bool isPressing = false;

    // mouse interface
    double * mousePosX;
    double * mousePosY;
};

#endif
