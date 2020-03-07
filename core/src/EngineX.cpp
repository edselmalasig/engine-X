#include "EngineX.h"

int EngineX::window_w;
int EngineX::window_h;
GLFWwindow* EngineX::window;
bool EngineX::show_ui;
Camera * EngineX::camera;

EngineX::EngineX(Camera * cam)
{
     camera = cam;
     show_demo_window = false;
     show_another_window;
     show_ui = true;
     clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};

static void glfw_error_callback(int error, const char* description)
{
     fprintf(stderr, "GlFW Error %d: %s\n", error, description);
}

void EngineX::init_ImGui( )
{
     // Setup Dear ImGui context
     IMGUI_CHECKVERSION();
     ImGui::CreateContext();
     ImGuiIO& io = ImGui::GetIO();
     (void)io;
     //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
     //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

     ImGuiStyle& style = ImGui::GetStyle();
     style.Alpha                   = 1.0f;             // Global alpha applies to everything in ImGui
    style.WindowPadding           = ImVec2(8,8);      // Padding within a window
    style.WindowMinSize           = ImVec2(32,32);    // Minimum window size
    style.WindowRounding          = 9.0f;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
    style.WindowTitleAlign        = ImVec2(0.0f,0.5f);// Alignment for title bar text
    style.ChildRounding           = 3.0f;             // Radius of child window corners rounding. Set to 0.0f to have rectangular child windows
    style.FramePadding            = ImVec2(4,3);      // Padding within a framed rectangle (used by most widgets)
    style.FrameRounding           = 6.0f;             // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
    style.ItemSpacing             = ImVec2(8,4);      // Horizontal and vertical spacing between widgets/lines
    style.ItemInnerSpacing        = ImVec2(4,4);      // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
    style.TouchExtraPadding       = ImVec2(0,0);      // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
    style.IndentSpacing           = 12.0f;            // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
    style.ColumnsMinSpacing       = 6.0f;             // Minimum horizontal spacing between two columns
    style.ScrollbarSize           = 16.0f;            // Width of the vertical scrollbar, Height of the horizontal scrollbar
    style.ScrollbarRounding       = 9.0f;             // Radius of grab corners rounding for scrollbar
    style.GrabMinSize             = 10.0f;            // Minimum width/height of a grab box for slider/scrollbar
    style.GrabRounding            = 0.0f;             // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
    style.ButtonTextAlign         = ImVec2(0.5f,0.5f);// Alignment of button text when button is larger than text.
    style.DisplayWindowPadding    = ImVec2(22,22);    // Window positions are clamped to be visible within the display area by at least this amount. Only covers regular windows.
    style.DisplaySafeAreaPadding  = ImVec2(4,4);      // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
    style.AntiAliasedLines        = true;             // Enable anti-aliasing on lines/borders. Disable if you are really short on CPU/GPU.
    style.CurveTessellationTol    = 1.25f;            // Tessellation tolerance. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.

     // Setup Dear ImGui style
     ImGui::StyleColorsDark();
     //ImGui::StyleColorsClassic();

     // Setup Platform/Renderer bindings
     ImGui_ImplGlfw_InitForOpenGL(window, true);
     ImGui_ImplOpenGL3_Init(glsl_version);

     // Load Fonts
     // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
     // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
     // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
     // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
     // - Read 'misc/fonts/README.txt' for more instructions and details.
     // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !

     //io.Fonts->AddFontDefault();
     io.Fonts->AddFontFromFileTTF("resources/Monofur for Powerline.ttf", 14.0f);

     //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
     //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
     //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
     //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
     //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
     //IM_ASSERT(font != NULL);
     /*
     io.Fonts->AddFontFromFileTTF("../../misc/fonts/Exo2-ExtraLightExpanded.otf", 14.0f);
     io.Fonts->AddFontFromFileTTF("../../misc/fonts/ColabLig.otf", 14.0f);
     io.Fonts->AddFontFromFileTTF("../../misc/fonts/System San Francisco Display Regular.ttf", 14.0f);
     io.Fonts->AddFontFromFileTTF("../../misc/fonts/GOODDP__.ttf", 14.0f);
     io.Fonts->AddFontFromFileTTF("../../misc/fonts/SFMono-Regular.otf", 14.0f);
     */
     ImVec4* colors = ImGui::GetStyle().Colors;
     colors[ImGuiCol_Text]                   = ImVec4(0.85f, 0.83f, 0.71f, 1.00f);
     colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
     colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
     colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
     colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
     colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
     colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
     colors[ImGuiCol_FrameBg]                = ImVec4(0.44f, 0.44f, 0.44f, 0.54f);
     colors[ImGuiCol_FrameBgHovered]         = ImVec4(1.00f, 1.00f, 1.00f, 0.40f);
     colors[ImGuiCol_FrameBgActive]          = ImVec4(0.91f, 0.95f, 1.00f, 0.67f);
     colors[ImGuiCol_TitleBg]                = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
     colors[ImGuiCol_TitleBgActive]          = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
     colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
     colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
     colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
     colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
     colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
     colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
     colors[ImGuiCol_CheckMark]              = ImVec4(0.86f, 0.98f, 0.26f, 1.00f);
     colors[ImGuiCol_SliderGrab]             = ImVec4(0.67f, 0.76f, 0.87f, 1.00f);
     colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.87f, 0.92f, 0.99f, 1.00f);
     colors[ImGuiCol_Button]                 = ImVec4(0.12f, 0.12f, 0.12f, 0.40f);
     colors[ImGuiCol_ButtonHovered]          = ImVec4(0.43f, 0.43f, 0.43f, 1.00f);
     colors[ImGuiCol_ButtonActive]           = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
     colors[ImGuiCol_Header]                 = ImVec4(0.25f, 0.27f, 0.29f, 0.31f);
     colors[ImGuiCol_HeaderHovered]          = ImVec4(0.32f, 0.34f, 0.36f, 0.80f);
     colors[ImGuiCol_HeaderActive]           = ImVec4(0.59f, 0.61f, 0.64f, 1.00f);
     colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
     colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.28f, 0.30f, 0.33f, 0.78f);
     colors[ImGuiCol_SeparatorActive]        = ImVec4(0.20f, 0.21f, 0.23f, 1.00f);
     colors[ImGuiCol_ResizeGrip]             = ImVec4(0.43f, 0.98f, 0.26f, 0.25f);
     colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.41f, 0.98f, 0.26f, 0.67f);
     colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.98f, 0.92f, 0.26f, 0.95f);
     colors[ImGuiCol_Tab]                    = ImVec4(0.55f, 0.55f, 0.55f, 0.86f);
     colors[ImGuiCol_TabHovered]             = ImVec4(0.85f, 0.85f, 0.85f, 0.80f);
     colors[ImGuiCol_TabActive]              = ImVec4(0.67f, 0.67f, 0.67f, 1.00f);
     colors[ImGuiCol_TabUnfocused]           = ImVec4(0.16f, 0.16f, 0.16f, 0.97f);
     colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
     colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
     colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
     colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
     colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
     colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.32f, 0.98f, 0.26f, 0.35f);
     colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
     colors[ImGuiCol_NavHighlight]           = ImVec4(0.41f, 0.98f, 0.26f, 1.00f);
     colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
     colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
     colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

     show_demo_window = false;
     show_another_window = false;
     clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

void EngineX::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
     // make sure the viewport matches the new window dimensions; note that width and
     // height will be significantly larger than specified on retina displays.
     glViewport(0, 0, width, height);
}

void EngineX::ImGui_Loop()
{

     if(show_ui)
     {
          // Start the Dear ImGui frame
          ImGui_ImplOpenGL3_NewFrame();
          ImGui_ImplGlfw_NewFrame();
          ImGui::NewFrame();

          // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemowindow()! You can browse its code to learn more about Dear ImGui!).
          if (show_demo_window)
          ImGui::ShowDemoWindow(&show_demo_window);

          // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
          {
               static float f = 0.0f;
               static int counter = 0;

               ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

               ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
               ImGui::Checkbox("Control window", &show_demo_window);      // Edit bools storing our window open/close state

               ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
               ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

               if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
               counter++;
               ImGui::SameLine();
               ImGui::Text("counter = %d", counter);


               ImGui::Text("\n");
               ImGui::Text("Please modify the current style in:");
               ImGui::Text("ImGui Test->window Options->Style Editor");
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
          if (show_another_window)
          {
               ImGui::Begin("Another window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
               ImGui::Text("Hello from another window!");
               if (ImGui::Button("Close Me"))
               show_another_window = false;
               ImGui::End();
          }

          // Rendering
          ImGui::Render();
     }
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void EngineX::processInput(GLFWwindow * window)
{
     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
     glfwSetWindowShouldClose(window, true);
}

void EngineX::reshapeFunc( int w, int h)
{
     // save the new window size
     printf("Window width and height: %i %i\n", window_w, window_h);

     window_w = w; window_h = h;
     // map the view port to the client area
     glViewport( 0, 0, w, h );

}

void EngineX::rotateView()
{
     //printf("MMB pressed rotating view. ");
     double xpos, ypos;
     glfwGetCursorPos(window, &xpos, &ypos);
     //printf("Mouse pos: %f %f\n", xpos, ypos);
     if(camera->firstMouseClick)
     {
          camera->lastMouseXPosition = xpos;
          camera->lastMouseYPosition = ypos;
          camera->firstMouseClick = false;
     }

     GLfloat xoffset = xpos - camera->lastMouseXPosition;
     GLfloat yoffset = camera->lastMouseYPosition - ypos;  // Reversed since y-coordinates go from bottom to left

     camera->lastMouseXPosition = xpos;
     camera->lastMouseYPosition = ypos;

     camera->ProcessMouseMovement(xoffset, yoffset, true);
}

void EngineX::panView()
{
     double xpos, ypos;
     glfwGetCursorPos(window, &xpos, &ypos);
     //printf("Mouse pos: %f %f\n", xpos, ypos);
     if(camera->firstMouseClick)
     {
          camera->lastMouseXPosition = xpos;
          camera->lastMouseYPosition = ypos;
          camera->firstMouseClick = false;
     }

     //GLfloat xoffset = xpos - camera->lastMouseXPosition;
     //GLfloat yoffset = camera->lastMouseYPosition - ypos;

     if(xpos > camera->lastMouseXPosition)
     {
          camera->ProcessKeyboard(LEFT, camera->deltaTime);
     }
     else if(xpos < camera->lastMouseXPosition)
     {
          camera->ProcessKeyboard(RIGHT, camera->deltaTime);
     }

     if(ypos > camera->lastMouseYPosition)
     {
          camera->ProcessKeyboard(DOWNWARD, camera->deltaTime);
     }
     else if(ypos < camera->lastMouseYPosition)
     {
          camera->ProcessKeyboard(UPWARD, camera->deltaTime);
     }
     camera->lastMouseXPosition = xpos;
     camera->lastMouseYPosition = ypos;
}


GLFWmousebuttonfun EngineX::mouseButtonFunc( GLFWwindow * window, int button, int action, int mods)
{

     if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
     {
          EngineX::rotateView();
          //printf("MMB Pressed.\n");
     }
     if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
     {
          //printf("MMB Released.\n");
          camera->firstMouseClick = true;
     }
     return (GLFWmousebuttonfun)1;

}

GLFWcursorposfun EngineX::mouseFunc(double xpos, double ypos)
{
     //rotate view
     int mmbState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
     int shiftState = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);

     if( mmbState == GLFW_PRESS && shiftState != GLFW_PRESS)
     {
          //printf("mouseFunc - mmbState pressed - shiftState not pressed.\n");
          EngineX::rotateView();
     }

     if((mmbState == GLFW_PRESS) && (shiftState == GLFW_PRESS))
     {
          //printf("MMB Clicked & shiftState pressed.\n");
          EngineX::panView();
     }

     return (GLFWcursorposfun)1;
}

void EngineX::editModeFunc( GLFWwindow * window, int key, int scancode, int action)
{
     printf("Edit mode.\n");
     if(action == GLFW_PRESS)
     {
          switch( key ){
               default:
               printf("[engine-X]: show ui: %i\n", show_ui);
               break;

               case GLFW_KEY_F10:
               show_ui = !show_ui;
               printf("[engine-X]: show ui: %i\n", show_ui);
               EngineX::reshapeFunc(window_w, window_h);
               glfwSetKeyCallback(window, (GLFWkeyfun) EngineX::moveFunc);

               return;
               break;
          }
     }
}

GLFWkeyfun EngineX::moveFunc(GLFWwindow * window, int key, int scancode, int action)
{

     //https://www.youtube.com/watch?v=ZrL6qUNvKwk
     if(action == GLFW_PRESS || action == GLFW_REPEAT)
     {
          switch( key )
          {
               case GLFW_KEY_F9:
               if(show_ui == 1)
               {
                    printf("UI mode disabled.\n");
                    show_ui = 0;
                    printf("[engine-X]: show ui: %i\n", show_ui);
                    glfwSetKeyCallback(window, (GLFWkeyfun) EngineX::moveFunc);
                    glfwSetCursorPosCallback(window, (GLFWcursorposfun) EngineX::mouseButtonFunc );
                    glfwSetScrollCallback(window, (GLFWscrollfun) EngineX::scrollBackFunc);
               }
               break;

               case GLFW_KEY_W:
               camera->ProcessKeyboard(FORWARD, camera->deltaTime);
               break;
               case GLFW_KEY_S:
               camera->ProcessKeyboard(BACKWARD, camera->deltaTime);
               break;
               case GLFW_KEY_A:
               camera->ProcessKeyboard(LEFT, camera->deltaTime);
               break;
               case GLFW_KEY_D:
               camera->ProcessKeyboard(RIGHT, camera->deltaTime);
               break;
               case GLFW_KEY_R:
               camera->ProcessKeyboard(UPWARD, camera->deltaTime);
               break;
               case GLFW_KEY_F:
               camera->ProcessKeyboard(DOWNWARD, camera->deltaTime);
               break;

               case GLFW_KEY_F10:
               if(show_ui == 0)
               {
                    printf("UI Mode enabled.\n");
                    show_ui = 1;
                    glfwSetKeyCallback(window, (GLFWkeyfun) EngineX::editModeFunc);
                    glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun) EngineX::mouseButtonFunc);
                    glfwSetCursorPosCallback(window, (GLFWcursorposfun) EngineX::mouseFunc);
                    glfwSetScrollCallback(window, (GLFWscrollfun) EngineX::scrollBackFunc );
               }


               break;
               default:
               printf("[engine-X]: show ui: %i\n", show_ui);
               printf("Key pressed: %s \n",glfwGetKeyName(key, 0));
               return (GLFWkeyfun) 0;;
               break;

          }

     }

     // do a reshape since g_eye_y might have changed
     reshapeFunc(window_w, window_h);
     return (GLFWkeyfun) 1;

}

void EngineX::init_glfw()
{
     // Setup window
     glfwSetErrorCallback(glfw_error_callback);
     if (!glfwInit())
     fprintf(stderr, "Error initializing glfw.\n");

     // Decide GL+GLSL versions
     #if __APPLE__
     // GL 3.2 + GLSL 150
     strcpy(glsl_version,"#version 330 core");
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
     #else
     // GL 3.0 + GLSL 130
     strcpy(glsl_version ,"#version 330 core");
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
     //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
     //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
     #endif
     // Create window with graphics context
     printf("window width and height: %i %i\n", camera->window_w, camera->window_h);
     window = glfwCreateWindow(camera->window_w, camera->window_h, "[engine-X] Hello World!", NULL, NULL);

     if (window == NULL)
     {
          fprintf(stderr, "Error creating glfw window.\n");
     }
     glfwMakeContextCurrent(window);
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
     clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

     glfwSetFramebufferSizeCallback(window, EngineX::framebuffer_size_callback);

     glfwSetCursorPosCallback( window, (GLFWcursorposfun) EngineX::mouseFunc );
     glfwSetMouseButtonCallback(window,  (GLFWmousebuttonfun) EngineX::mouseButtonFunc);
     glfwSetKeyCallback(window, (GLFWkeyfun) EngineX::moveFunc);
     glfwSetScrollCallback(window, (GLFWscrollfun) EngineX::scrollBackFunc);

     glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
     glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

}

GLFWscrollfun EngineX::scrollBackFunc(GLFWwindow *window, double xOffset, double yOffset)
{
     camera->ProcessMouseScroll(yOffset);
     //printf("Scroll back function - %f : %f\n", xOffset, yOffset);
     return (GLFWscrollfun)1;
}

// Object picking section

void EngineX::Get3DRayUnderMouse(glm::vec3* v1, glm::vec3* v2)
{
/*
	POINT mp; GetCursorPos(&mp);
	ScreenToClient(appMain.hWnd, &mp);
	RECT rect; GetClientRect(appMain.hWnd, &rect);
	mp.y = rect.bottom-mp.y;
*/
     double mousePosX, mousePosY;

     glfwGetCursorPos(window, &mousePosX, &mousePosY);
     mousePosY = camera->window_h - mousePosY;
	glm::vec4 viewport = glm::vec4(0.0f, 0.0f, camera->window_w, camera->window_h);

	*v1 = glm::unProject(glm::vec3(float(mousePosX), float(mousePosY), 0.0f), camera->getViewMatrix(), camera->getProjectionMatrix(), viewport);
	*v2 = glm::unProject(glm::vec3(float(mousePosX), float(mousePosY), 1.0f), camera->getViewMatrix(), camera->getProjectionMatrix(), viewport);
}

/*-----------------------------------------------

Name:    RaySphereCollision

Params:  vSphereCenter - guess what it is
	     fSphereRadius - guess what it is
		 vA, vB - two points of ray

Result:  Checks if a ray given by two points
		 collides with sphere.

/*---------------------------------------------*/

bool EngineX::RaySphereCollision(glm::vec3 vSphereCenter, float fSphereRadius, glm::vec3 vA, glm::vec3 vB)
{
	// Create the vector from end point vA to center of sphere
	glm::vec3 vDirToSphere = vSphereCenter - vA;

	// Create a normalized direction vector from end point vA to end point vB
	glm::vec3 vLineDir = glm::normalize(vB-vA);

	// Find length of line segment
	float fLineLength = glm::distance(vA, vB);

	// Using the dot product, we project the vDirToSphere onto the vector vLineDir
	float t = glm::dot(vDirToSphere, vLineDir);

	glm::vec3 vClosestPoint;
	// If our projected distance from vA is less than or equal to 0, the closest point is vA
	if (t <= 0.0f)
		vClosestPoint = vA;
	// If our projected distance from vA is greater thatn line length, closest point is vB
	else if (t >= fLineLength)
		vClosestPoint = vB;
	// Otherwise calculate the point on the line using t and return it
	else
		vClosestPoint = vA+vLineDir*t;

	// Now just check if closest point is within radius of sphere
	return glm::distance(vSphereCenter, vClosestPoint) <= fSphereRadius;
}

void EngineX::ScreenPosToWorldRay(
	int mousePosX, int mousePosY,             // Mouse position, in pixels, from bottom-left corner of the window
	int screenWidth, int screenHeight,  // window size, in pixels
	glm::mat4 ViewMatrix,               // Camera position and orientation
	glm::mat4 ProjectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
	glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
	glm::vec3& out_direction            // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
){

     mousePosY = screenHeight - mousePosY;
     // The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
     glm::vec4 lRayStart_NDC(
          ((float)mousePosX/(float)screenWidth  - 0.5f) * 2.0f, // [0,width] -> [-1,1]
          ((float)mousePosY/(float)screenHeight - 0.5f) * 2.0f, // [0, height] -> [-1,1]
          -1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
          1.0f
     );
     glm::vec4 lRayEnd_NDC(
          ((float)mousePosX/(float)screenWidth  - 0.5f) * 2.0f,
          ((float)mousePosY/(float)screenHeight - 0.5f) * 2.0f,
          0.0, // The far plane
          1.0f
     );

//     glm::vec4 lRayStart_NDC(mouseX, mouseY, -1.0f, 1.0f);
//     glm::vec4 lRayEnd_NDC(mouseX, mouseY,  0.0f, 1.0f);

     // The Projection matrix goes from Camera Space to NDC.
     // So inverse(ProjectionMatrix) goes from NDC to Camera Space.
     glm::mat4 InverseProjectionMatrix = glm::inverse(ProjectionMatrix);

     // The View Matrix goes from World Space to Camera Space.
     // So inverse(ViewMatrix) goes from Camera Space to World Space.
     glm::mat4 InverseViewMatrix = glm::inverse(ViewMatrix);

     glm::vec4 lRayStart_camera = InverseProjectionMatrix * lRayStart_NDC;    lRayStart_camera/=lRayStart_camera.w;
     glm::vec4 lRayStart_world  = InverseViewMatrix       * lRayStart_camera; lRayStart_world /=lRayStart_world .w;
     glm::vec4 lRayEnd_camera   = InverseProjectionMatrix * lRayEnd_NDC;      lRayEnd_camera  /=lRayEnd_camera  .w;
     glm::vec4 lRayEnd_world    = InverseViewMatrix       * lRayEnd_camera;   lRayEnd_world   /=lRayEnd_world   .w;


     // Faster way (just one inverse)
     //glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
     //glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
     //glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;


     glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
     lRayDir_world = glm::normalize(lRayDir_world);


     out_origin = glm::vec3(lRayStart_world);
     out_direction = glm::normalize(lRayDir_world);
}

bool EngineX::RayAABBIntersection(
	glm::vec3 ray_origin,        // Ray origin, in world space
	glm::vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
	glm::vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
	glm::vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
	glm::mat4 ModelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
	float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB
){

	// Intersection method from Real-Time Rendering and Essential Mathematics for Games

	float tMin = 0.0f;
	float tMax = 100000.0f;

	glm::vec3 OBBposition_worldspace(ModelMatrix[3].x, ModelMatrix[3].y, ModelMatrix[3].z);

	glm::vec3 delta = OBBposition_worldspace - ray_origin;

	// Test intersection with the 2 planes perpendicular to the OBB's X axis
	{
		glm::vec3 xaxis(ModelMatrix[0].x, ModelMatrix[0].y, ModelMatrix[0].z);
		float e = glm::dot(xaxis, delta);
		float f = glm::dot(ray_direction, xaxis);

		if ( fabs(f) > 0.001f ){ // Standard case

			float t1 = (e+aabb_min.x)/f; // Intersection with the "left" plane
			float t2 = (e+aabb_max.x)/f; // Intersection with the "right" plane
			// t1 and t2 now contain distances betwen ray origin and ray-plane intersections

			// We want t1 to represent the nearest intersection,
			// so if it's not the case, invert t1 and t2
			if (t1>t2){
				float w=t1;t1=t2;t2=w; // swap t1 and t2
			}

			// tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
			if ( t2 < tMax )
				tMax = t2;
			// tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
			if ( t1 > tMin )
				tMin = t1;

			// And here's the trick :
			// If "far" is closer than "near", then there is NO intersection.
			// See the images in the tutorials for the visual explanation.
			if (tMax < tMin )
				return false;

		}else{ // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
			if(-e+aabb_min.x > 0.0f || -e+aabb_max.x < 0.0f)
				return false;
		}
	}


	// Test intersection with the 2 planes perpendicular to the OBB's Y axis
	// Exactly the same thing than above.
	{
		glm::vec3 yaxis(ModelMatrix[1].x, ModelMatrix[1].y, ModelMatrix[1].z);
		float e = glm::dot(yaxis, delta);
		float f = glm::dot(ray_direction, yaxis);

		if ( fabs(f) > 0.001f ){

			float t1 = (e+aabb_min.y)/f;
			float t2 = (e+aabb_max.y)/f;

			if (t1>t2){float w=t1;t1=t2;t2=w;}

			if ( t2 < tMax )
				tMax = t2;
			if ( t1 > tMin )
				tMin = t1;
			if (tMin > tMax)
				return false;

		}else{
			if(-e+aabb_min.y > 0.0f || -e+aabb_max.y < 0.0f)
				return false;
		}
	}


	// Test intersection with the 2 planes perpendicular to the OBB's Z axis
	// Exactly the same thing than above.
	{
		glm::vec3 zaxis(ModelMatrix[2].x, ModelMatrix[2].y, ModelMatrix[2].z);
		float e = glm::dot(zaxis, delta);
		float f = glm::dot(ray_direction, zaxis);

		if ( fabs(f) > 0.001f ){

			float t1 = (e+aabb_min.z)/f;
			float t2 = (e+aabb_max.z)/f;

			if (t1>t2){float w=t1;t1=t2;t2=w;}

			if ( t2 < tMax )
				tMax = t2;
			if ( t1 > tMin )
				tMin = t1;
			if (tMin > tMax)
				return false;

		}else{
			if(-e+aabb_min.z > 0.0f || -e+aabb_max.z < 0.0f)
				return false;
		}
	}

	intersection_distance = tMin;
	return true;
}
