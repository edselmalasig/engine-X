#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imguistyleserializer.h"

#include "camera.h"

#include <stdio.h>
#include <string.h>
#include <memory.h>
// About OpenGL function loaders: modern OpenGL doesn't have a standard header file and requires individual function pointers to be loaded manually.
// Helper libraries are often used for this purpose! Here we are supporting a few common ones: gl3w, glew, glad.
// You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

class gcw_UI_Controls
{
public:
    gcw_UI_Controls();

    //GLFW Variables
    char glsl_version[50];
    GLFWwindow* window;

    //ImGuiIO * io = NULL;
    bool show_demo_window = false;
    bool show_another_window;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    //camera and controls
    Camera * g_cnc;
    bool show_ui = true;
    char cstr[20] = "inside struct.\0";
    int display_w;
    int display_h;
    bool isPressing = false;
};

//GC_UIC Instance
#if defined (WIN32)
gcw_UI_Controls * gcw_UIC = new gcw_UI_Controls();
#elif defined (LINUX) || defined (MACOS)
inline gcw_UI_Controls * gcw_UIC = new gcw_UI_Controls();
#endif
//GLFW Controls
void init_glfw();
GLFWkeyfun moveFunc( GLFWwindow * window, int key, int scancode, int action);
GLFWmousebuttonfun mouseButtonFunc( GLFWwindow * window, int button, int action, int mods);
void editModeFunc( GLFWwindow * window, int key, int scancode, int action);
GLFWcursorposfun mouseFunc(double xpos, double ypos);
GLFWscrollfun scrollBackFunc(GLFWwindow *window, double xOffset, double yOffset);
void reshapeFunc( int w, int h);

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void glfw_error_callback(int error, const char* description);

void rotateView();
void panView();
//GUI
void init_ImGui();
void ImGui_Loop();

#endif
