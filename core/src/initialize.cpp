#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "initialize.h"
#include <stdio.h>
#include <string.h>

gcw_UI_Controls::gcw_UI_Controls()
{
    g_cnc = new Camera();
    this->display_w = g_cnc->display_w;
    this->display_h = g_cnc->display_h;
}

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
    ImGui_ImplGlfw_InitForOpenGL(gcw_UIC->window, true);
    ImGui_ImplOpenGL3_Init(gcw_UIC->glsl_version);

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

    gcw_UIC->show_demo_window = false;
    gcw_UIC->show_another_window = false;
    gcw_UIC->clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
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
    strcpy(gcw_UIC->glsl_version,"#version 330 core");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    strcpy(gcw_UIC->glsl_version ,"#version 330 core");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
    // Create window with graphics context
    gcw_UIC->window = glfwCreateWindow(gcw_UIC->display_w, gcw_UIC->display_h, "Lesson: Hello World!", NULL, NULL);

    if (gcw_UIC->window == NULL)
    {
        fprintf(stderr, "Error creating glfw window.\n");
    }
    glfwMakeContextCurrent(gcw_UIC->window);
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
    gcw_UIC->clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    glfwSetFramebufferSizeCallback(gcw_UIC->window, framebuffer_size_callback);

    glfwSetCursorPosCallback( gcw_UIC->window, (GLFWcursorposfun) mouseFunc );
    glfwSetMouseButtonCallback(gcw_UIC->window,  (GLFWmousebuttonfun) mouseButtonFunc);
    glfwSetKeyCallback(gcw_UIC->window, (GLFWkeyfun) moveFunc);
    glfwSetScrollCallback(gcw_UIC->window, (GLFWscrollfun) scrollBackFunc);

    glfwSetInputMode(gcw_UIC->window, GLFW_STICKY_MOUSE_BUTTONS, 1);
    glfwSetInputMode(gcw_UIC->window, GLFW_STICKY_KEYS, 1);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void ImGui_Loop()
{

    if(gcw_UIC->show_ui)
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (gcw_UIC->show_demo_window)
            ImGui::ShowDemoWindow(&gcw_UIC->show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Control Window", &gcw_UIC->show_demo_window);      // Edit bools storing our window open/close state

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&gcw_UIC->clear_color); // Edit 3 floats representing a color

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
        if (gcw_UIC->show_another_window)
        {
            ImGui::Begin("Another Window", &gcw_UIC->show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                gcw_UIC->show_another_window = false;
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

GLFWkeyfun moveFunc(GLFWwindow * window, int key, int scancode, int action)
{

    //https://www.youtube.com/watch?v=ZrL6qUNvKwk
    if(action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch( key )
        {
            case GLFW_KEY_F9:
                if(gcw_UIC->show_ui == 1)
                {
                    printf("UI mode disabled.\n");
                    gcw_UIC->show_ui = 0;
                    printf("[Virtuoso Reality]: show ui: %i\n", gcw_UIC->show_ui);
                    reshapeFunc(gcw_UIC->display_w, gcw_UIC->display_h);
                    glfwSetKeyCallback(gcw_UIC->window, (GLFWkeyfun)moveFunc);
                    glfwSetCursorPosCallback(gcw_UIC->window, (GLFWcursorposfun)mouseButtonFunc );
                    glfwSetScrollCallback(gcw_UIC->window, (GLFWscrollfun) scrollBackFunc);
                }
                break;

            case GLFW_KEY_W:
                printf("moving forward.");
                gcw_UIC->g_cnc->ProcessKeyboard(FORWARD, gcw_UIC->g_cnc->deltaTime);
                break;
            case GLFW_KEY_S:
                gcw_UIC->g_cnc->ProcessKeyboard(BACKWARD, gcw_UIC->g_cnc->deltaTime);
                break;
            case GLFW_KEY_A:
                gcw_UIC->g_cnc->ProcessKeyboard(LEFT, gcw_UIC->g_cnc->deltaTime);
                break;
            case GLFW_KEY_D:
                gcw_UIC->g_cnc->ProcessKeyboard(RIGHT, gcw_UIC->g_cnc->deltaTime);
                break;
            case GLFW_KEY_R:
                gcw_UIC->g_cnc->ProcessKeyboard(UPWARD, gcw_UIC->g_cnc->deltaTime);
                break;
            case GLFW_KEY_F:
                gcw_UIC->g_cnc->ProcessKeyboard(DOWNWARD, gcw_UIC->g_cnc->deltaTime);
                break;

            case GLFW_KEY_F10:
                if(gcw_UIC->show_ui == 0)
                {
                    printf("UI Mode enabled.\n");
                    gcw_UIC->show_ui = 1;
                    reshapeFunc(gcw_UIC->display_w, gcw_UIC->display_h);
                    glfwSetKeyCallback(gcw_UIC->window, (GLFWkeyfun)editModeFunc);
                    glfwSetMouseButtonCallback(gcw_UIC->window, (GLFWmousebuttonfun) mouseButtonFunc);
                    glfwSetCursorPosCallback(gcw_UIC->window, (GLFWcursorposfun)mouseFunc);
                    glfwSetScrollCallback(gcw_UIC->window, (GLFWscrollfun)scrollBackFunc );
                }


                break;
            default:
                printf("[Virtuoso Reality]: show ui: %i\n", gcw_UIC->show_ui);
                printf("Key pressed: %s \n",glfwGetKeyName(key, 0));
                return (GLFWkeyfun) 0;;
                break;

        }

    }

    // do a reshape since g_eye_y might have changed
    //doMovement(key);
    //reshapeFunc(gcw_UIC->display_w,gcw_UIC->display_h, gcw_UIC);
    return (GLFWkeyfun) 1;

}

GLFWmousebuttonfun mouseButtonFunc( GLFWwindow * window, int button, int action, int mods)
{

    if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        rotateView();
        printf("MMB Pressed.\n");
    }
    if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        printf("MMB Released.\n");
        gcw_UIC->g_cnc->firstMouse = true;
    }
	return (GLFWmousebuttonfun)1;

}

void rotateView()
{
    printf("MMB pressed rotating view. ");
    double xpos, ypos;
    glfwGetCursorPos(gcw_UIC->window, &xpos, &ypos);
    printf("Mouse pos: %f %f\n", xpos, ypos);
    if(gcw_UIC->g_cnc->firstMouse)
    {
        gcw_UIC->g_cnc->lastX = xpos;
        gcw_UIC->g_cnc->lastY = ypos;
        gcw_UIC->g_cnc->firstMouse = false;
    }

    GLfloat xoffset = xpos - gcw_UIC->g_cnc->lastX;
    GLfloat yoffset = gcw_UIC->g_cnc->lastY - ypos;  // Reversed since y-coordinates go from bottom to left

    gcw_UIC->g_cnc->lastX = xpos;
    gcw_UIC->g_cnc->lastY = ypos;

    gcw_UIC->g_cnc->ProcessMouseMovement(xoffset, yoffset, true);
}

GLFWcursorposfun mouseFunc(double xpos, double ypos)
{
    //rotate view
    int mmbState = glfwGetMouseButton(gcw_UIC->window, GLFW_MOUSE_BUTTON_MIDDLE);
    int shiftState = glfwGetKey(gcw_UIC->window, GLFW_KEY_LEFT_SHIFT);

    if( mmbState == GLFW_PRESS && shiftState != GLFW_PRESS)
    {
        printf("mouseFunc - mmbState pressed - shiftState not pressed.\n");
        rotateView();
    }

    if((mmbState == GLFW_PRESS) && (shiftState == GLFW_PRESS))
    {
        printf("MMB Clicked & shiftState pressed.\n");
        panView();
    }

    return (GLFWcursorposfun)1;

}

void panView()
{
    double xpos, ypos;
    glfwGetCursorPos(gcw_UIC->window, &xpos, &ypos);
    printf("Mouse pos: %f %f\n", xpos, ypos);
    if(gcw_UIC->g_cnc->firstMouse)
    {
        gcw_UIC->g_cnc->lastX = xpos;
        gcw_UIC->g_cnc->lastY = ypos;
        gcw_UIC->g_cnc->firstMouse = false;
    }

    //GLfloat xoffset = xpos - gcw_UIC->g_cnc->lastX;
    //GLfloat yoffset = gcw_UIC->g_cnc->lastY - ypos;

    if(xpos > gcw_UIC->g_cnc->lastX)
    {
        gcw_UIC->g_cnc->ProcessKeyboard(LEFT, gcw_UIC->g_cnc->deltaTime);
    }
    else if(xpos < gcw_UIC->g_cnc->lastX)
    {
        gcw_UIC->g_cnc->ProcessKeyboard(RIGHT, gcw_UIC->g_cnc->deltaTime);
    }

    if(ypos > gcw_UIC->g_cnc->lastY)
    {
        gcw_UIC->g_cnc->ProcessKeyboard(DOWNWARD, gcw_UIC->g_cnc->deltaTime);
    }
    else if(ypos < gcw_UIC->g_cnc->lastY)
    {
        gcw_UIC->g_cnc->ProcessKeyboard(UPWARD, gcw_UIC->g_cnc->deltaTime);
    }
    gcw_UIC->g_cnc->lastX = xpos;
    gcw_UIC->g_cnc->lastY = ypos;

    //reshapeFunc(gcw_UIC->display_w, gcw_UIC->display_h);

}

GLFWscrollfun scrollBackFunc(GLFWwindow *window, double xOffset, double yOffset)
{
    gcw_UIC->g_cnc->ProcessMouseScroll(yOffset);
    printf("Scroll back function - %f : %f\n", xOffset, yOffset);
	return (GLFWscrollfun)1;
}

void editModeFunc( GLFWwindow * window, int key, int scancode, int action)
{
    printf("Edit mode.\n");
    if(action == GLFW_PRESS)
    {
        switch( key ){
            default:
                printf("[Virtuoso Reality]: show ui: %i\n", gcw_UIC->show_ui);
                break;

            case GLFW_KEY_F10:
                gcw_UIC->show_ui = !gcw_UIC->show_ui;
                printf("[Virtuoso Reality]: show ui: %i\n", gcw_UIC->show_ui);
                reshapeFunc(gcw_UIC->display_w, gcw_UIC->display_h);
                glfwSetKeyCallback(gcw_UIC->window, (GLFWkeyfun)moveFunc);

                return;
                break;
        }
    }
}


void reshapeFunc( int w, int h)
{
    // save the new window size
    gcw_UIC->display_w = w; gcw_UIC->display_h = h;
    // map the view port to the client area
    glViewport( 0, 0, w, h );

}
