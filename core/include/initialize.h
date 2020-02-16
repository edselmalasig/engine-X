#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imguistyleserializer.h"

#include "camera.h"
#include "gcwuiControls.h"

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>
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


gcwuiControls * gcwui_C = new gcwuiControls();

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GlFW Error %d: %s\n", error, description);
}

void init_ImGui( )
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(gcwui_C->window, true);
    ImGui_ImplOpenGL3_Init(gcwui_C->glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'misc/fonts/README.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);
/*
io.Fonts->AddFontFromFileTTF("../../misc/fonts/Exo2-ExtraLightExpanded.otf", 14.0f);
    io.Fonts->AddFontFromFileTTF("../../misc/fonts/ColabLig.otf", 14.0f);
    io.Fonts->AddFontFromFileTTF("../../misc/fonts/System San Francisco Display Regular.ttf", 14.0f);
    io.Fonts->AddFontFromFileTTF("../../misc/fonts/GOODDP__.ttf", 14.0f);
    io.Fonts->AddFontFromFileTTF("../../misc/fonts/SFMono-Regular.otf", 14.0f);
 */
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.13f, 0.13f, 0.13f, 0.94f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.11f, 0.11f, 0.11f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.18f, 0.62f, 0.98f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.62f, 0.31f, 0.62f, 0.40f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.68f, 0.26f, 0.98f, 0.67f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.16f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.25f, 0.60f, 0.80f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.35f, 0.81f, 0.98f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.98f, 0.60f, 0.26f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.88f, 0.66f, 0.24f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.26f, 0.98f, 0.31f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.73f, 0.26f, 0.98f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.51f, 0.20f, 0.71f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.77f, 0.06f, 0.98f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.21f, 0.57f, 0.99f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.17f, 0.59f, 1.00f, 0.81f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(1.00f, 0.38f, 0.61f, 0.72f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.98f, 0.26f, 0.78f, 1.00f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.39f, 0.35f, 0.58f, 0.86f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.56f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.47f, 0.83f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    gcwui_C->show_demo_window = false;
    gcwui_C->show_another_window = false;
    gcwui_C->clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void ImGui_Loop()
{

    if(gcwui_C->show_ui)
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (gcwui_C->show_demo_window)
            ImGui::ShowDemoWindow(&gcwui_C->show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Control Window", &gcwui_C->show_demo_window);      // Edit bools storing our window open/close state

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&gcwui_C->clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);


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

        // 3. Show another simple window.
        if (gcwui_C->show_another_window)
        {
            ImGui::Begin("Another Window", &gcwui_C->show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                gcwui_C->show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void reshapeFunc( int w, int h)
{
    // save the new window size
    gcwui_C->display_w = w; gcwui_C->display_h = h;
    // map the view port to the client area
    glViewport( 0, 0, w, h );

}



void rotateView()
{
    //printf("MMB pressed rotating view. ");
    double xpos, ypos;
    glfwGetCursorPos(gcwui_C->window, &xpos, &ypos);
    //printf("Mouse pos: %f %f\n", xpos, ypos);
    if(gcwui_C->g_cnc->firstMouse)
    {
        gcwui_C->g_cnc->lastX = xpos;
        gcwui_C->g_cnc->lastY = ypos;
        gcwui_C->g_cnc->firstMouse = false;
    }

    GLfloat xoffset = xpos - gcwui_C->g_cnc->lastX;
    GLfloat yoffset = gcwui_C->g_cnc->lastY - ypos;  // Reversed since y-coordinates go from bottom to left

    gcwui_C->g_cnc->lastX = xpos;
    gcwui_C->g_cnc->lastY = ypos;

    gcwui_C->g_cnc->ProcessMouseMovement(xoffset, yoffset, true);
}

void panView()
{
    double xpos, ypos;
    glfwGetCursorPos(gcwui_C->window, &xpos, &ypos);
    //printf("Mouse pos: %f %f\n", xpos, ypos);
    if(gcwui_C->g_cnc->firstMouse)
    {
        gcwui_C->g_cnc->lastX = xpos;
        gcwui_C->g_cnc->lastY = ypos;
        gcwui_C->g_cnc->firstMouse = false;
    }

    //GLfloat xoffset = xpos - gcwui_C->g_cnc->lastX;
    //GLfloat yoffset = gcwui_C->g_cnc->lastY - ypos;

    if(xpos > gcwui_C->g_cnc->lastX)
    {
        gcwui_C->g_cnc->ProcessKeyboard(LEFT, gcwui_C->g_cnc->deltaTime);
    }
    else if(xpos < gcwui_C->g_cnc->lastX)
    {
        gcwui_C->g_cnc->ProcessKeyboard(RIGHT, gcwui_C->g_cnc->deltaTime);
    }

    if(ypos > gcwui_C->g_cnc->lastY)
    {
        gcwui_C->g_cnc->ProcessKeyboard(DOWNWARD, gcwui_C->g_cnc->deltaTime);
    }
    else if(ypos < gcwui_C->g_cnc->lastY)
    {
        gcwui_C->g_cnc->ProcessKeyboard(UPWARD, gcwui_C->g_cnc->deltaTime);
    }
    gcwui_C->g_cnc->lastX = xpos;
    gcwui_C->g_cnc->lastY = ypos;

    //reshapeFunc(gcwui_C->display_w, gcwui_C->display_h);

}

GLFWmousebuttonfun mouseButtonFunc( GLFWwindow * window, int button, int action, int mods)
{

    if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        rotateView();
        //printf("MMB Pressed.\n");
    }
    if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        //printf("MMB Released.\n");
        gcwui_C->g_cnc->firstMouse = true;
    }
	return (GLFWmousebuttonfun)1;

}

GLFWcursorposfun mouseFunc(double xpos, double ypos)
{
    //rotate view
    int mmbState = glfwGetMouseButton(gcwui_C->window, GLFW_MOUSE_BUTTON_MIDDLE);
    int shiftState = glfwGetKey(gcwui_C->window, GLFW_KEY_LEFT_SHIFT);

    if( mmbState == GLFW_PRESS && shiftState != GLFW_PRESS)
    {
        //printf("mouseFunc - mmbState pressed - shiftState not pressed.\n");
        rotateView();
    }

    if((mmbState == GLFW_PRESS) && (shiftState == GLFW_PRESS))
    {
        //printf("MMB Clicked & shiftState pressed.\n");
        panView();
    }

    return (GLFWcursorposfun)1;

}

GLFWscrollfun scrollBackFunc(GLFWwindow *window, double xOffset, double yOffset)
{
    gcwui_C->g_cnc->ProcessMouseScroll(yOffset);
    //printf("Scroll back function - %f : %f\n", xOffset, yOffset);
	return (GLFWscrollfun)1;
}

GLFWkeyfun moveFunc(GLFWwindow * window, int key, int scancode, int action);

void editModeFunc( GLFWwindow * window, int key, int scancode, int action)
{
    printf("Edit mode.\n");
    if(action == GLFW_PRESS)
    {
        switch( key ){
            default:
                printf("[engine-X]: show ui: %i\n", gcwui_C->show_ui);
                break;

            case GLFW_KEY_F10:
                gcwui_C->show_ui = !gcwui_C->show_ui;
                printf("[engine-X]: show ui: %i\n", gcwui_C->show_ui);
                reshapeFunc(gcwui_C->display_w, gcwui_C->display_h);
                glfwSetKeyCallback(gcwui_C->window, (GLFWkeyfun)moveFunc);

                return;
                break;
        }
    }
}

GLFWkeyfun moveFunc(GLFWwindow * window, int key, int scancode, int action)
{

    //https://www.youtube.com/watch?v=ZrL6qUNvKwk
    if(action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch( key )
        {
            case GLFW_KEY_F9:
                if(gcwui_C->show_ui == 1)
                {
                    printf("UI mode disabled.\n");
                    gcwui_C->show_ui = 0;
                    printf("[engine-X]: show ui: %i\n", gcwui_C->show_ui);
                    reshapeFunc(gcwui_C->display_w, gcwui_C->display_h);
                    glfwSetKeyCallback(gcwui_C->window, (GLFWkeyfun)moveFunc);
                    glfwSetCursorPosCallback(gcwui_C->window, (GLFWcursorposfun)mouseButtonFunc );
                    glfwSetScrollCallback(gcwui_C->window, (GLFWscrollfun) scrollBackFunc);
                }
                break;

            case GLFW_KEY_W:
                printf("moving forward.");
                gcwui_C->g_cnc->ProcessKeyboard(FORWARD, gcwui_C->g_cnc->deltaTime);
                break;
            case GLFW_KEY_S:
                gcwui_C->g_cnc->ProcessKeyboard(BACKWARD, gcwui_C->g_cnc->deltaTime);
                break;
            case GLFW_KEY_A:
                gcwui_C->g_cnc->ProcessKeyboard(LEFT, gcwui_C->g_cnc->deltaTime);
                break;
            case GLFW_KEY_D:
                gcwui_C->g_cnc->ProcessKeyboard(RIGHT, gcwui_C->g_cnc->deltaTime);
                break;
            case GLFW_KEY_R:
                gcwui_C->g_cnc->ProcessKeyboard(UPWARD, gcwui_C->g_cnc->deltaTime);
                break;
            case GLFW_KEY_F:
                gcwui_C->g_cnc->ProcessKeyboard(DOWNWARD, gcwui_C->g_cnc->deltaTime);
                break;

            case GLFW_KEY_F10:
                if(gcwui_C->show_ui == 0)
                {
                    printf("UI Mode enabled.\n");
                    gcwui_C->show_ui = 1;
                    reshapeFunc(gcwui_C->display_w, gcwui_C->display_h);
                    glfwSetKeyCallback(gcwui_C->window, (GLFWkeyfun)editModeFunc);
                    glfwSetMouseButtonCallback(gcwui_C->window, (GLFWmousebuttonfun) mouseButtonFunc);
                    glfwSetCursorPosCallback(gcwui_C->window, (GLFWcursorposfun)mouseFunc);
                    glfwSetScrollCallback(gcwui_C->window, (GLFWscrollfun)scrollBackFunc );
                }


                break;
            default:
                printf("[engine-X]: show ui: %i\n", gcwui_C->show_ui);
                printf("Key pressed: %s \n",glfwGetKeyName(key, 0));
                return (GLFWkeyfun) 0;;
                break;

        }

    }

    // do a reshape since g_eye_y might have changed
    //doMovement(key);
    //reshapeFunc(gcwui_C->display_w,gcwui_C->display_h, gcwui_C);
    return (GLFWkeyfun) 1;

}

void init_glfw()
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        fprintf(stderr, "Error initializing glfw.\n");

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 + GLSL 150
    strcpy(gcwui_C->glsl_version,"#version 330 core");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    strcpy(gcwui_C->glsl_version ,"#version 330 core");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
    // Create window with graphics context
    gcwui_C->window = glfwCreateWindow(gcwui_C->display_w, gcwui_C->display_h, "Lesson: Hello World!", NULL, NULL);

    if (gcwui_C->window == NULL)
    {
        fprintf(stderr, "Error creating glfw window.\n");
    }
    glfwMakeContextCurrent(gcwui_C->window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif

    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
    }
    gcwui_C->clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    glfwSetFramebufferSizeCallback(gcwui_C->window, framebuffer_size_callback);

    glfwSetCursorPosCallback( gcwui_C->window, (GLFWcursorposfun) mouseFunc );
    glfwSetMouseButtonCallback(gcwui_C->window,  (GLFWmousebuttonfun) mouseButtonFunc);
    glfwSetKeyCallback(gcwui_C->window, (GLFWkeyfun) moveFunc);
    glfwSetScrollCallback(gcwui_C->window, (GLFWscrollfun) scrollBackFunc);

    glfwSetInputMode(gcwui_C->window, GLFW_STICKY_MOUSE_BUTTONS, 1);
    glfwSetInputMode(gcwui_C->window, GLFW_STICKY_KEYS, 1);

}

#endif
