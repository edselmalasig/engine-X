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


#include <stdio.h>
#include <string.h>
#include <memory>

struct coordinates
{
    glm::vec3 coords;
    glm::vec3 * view_coords;
    GLfloat *radians;
    float near, far, angle;
};

int main(int, char**)
{
    printf("Initializing.\n");
    std::shared_ptr<gcw_UI_Controls>  s_gcw_UIC(gcw_UIC);
    init_glfw();
    init_ImGui();

    printf("Initializing shaders and objects.\n");
    //Geometry * lo_rectangle= new Geometry();

    Geometry * g_rectangle = new Geometry();
    /* Obsolete function but still implemented.
     init_shader(vertexShaderSource, fragmentShaderSource, lo_rectangle);
     */

    //lo_rectangle->lo_shader = new Shader("rectangle.vs", "rectangle.fs");
    g_rectangle->lo_shader = new Shader("resources/shader/rectangle.vs", "resources/shader/rectangle.fs");
    //init_object(vertices, indices, lo_rectangle);
    //init_object(lo_rectangle);
    g_rectangle->initobject(g_rectangle);
    g_rectangle->inittexture(g_rectangle, 0, "resources/textures/container.jpg");
    g_rectangle->inittexture(g_rectangle, 1, "resources/textures/awesomeface.png");
    g_rectangle->initshader("resources/shader/rectangle.vs", "resources/shader/rectangle.fs", g_rectangle);

    g_rectangle->enableshader(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    // glUniform1i(glGetUniformLocation(g_rectangle->lo_shader->ID, "texture1"), 0);
    // the above is the same as below.
    // the above is the same as g_rectangle->lo_shader->setInt("texture1", 0)
    // or set it via the texture class
    g_rectangle->lo_shader->setInt("texture1", 0); //// Should I include this in the Geo Class?
    g_rectangle->lo_shader->setInt("texture2", 1);

    printf("Starting main loop.\n");
    //---------------------------------------
    // Main loop
    bool show_demo_window = false;
    coordinates c_model, c_view, c_projection, c_view_pos, c_view_la, c_view_hu;

    c_model.coords.x = 1.0f; c_model.coords.y = 1.0f; c_model.coords.z = 0.0f;
    c_model.radians = new GLfloat(0.0f);

    c_view_pos.coords.x = 0.0f; c_view_pos.coords.y = 0.0f; c_view_pos.coords.z = 2.0f;
    c_view_la.coords.x = 0.0f; c_view_la.coords.y = 0.0f; c_view_la.coords.z = 0.0f;
    c_view_hu.coords.x = 0.0f; c_view_hu.coords.y = 1.0f; c_view_hu.coords.z = 0.0f;

    c_projection.radians = gcw_UIC->g_cnc->Zoom;
    c_projection.near = 0.1f; c_projection.far = 100.0f;

    float clearColor[4];

    clearColor[0]=0.0f; clearColor[1]=0.0f; clearColor[2]=0.0f; clearColor[3]=0.0f;

    Shader lightingshader("resources/shader/lightingshader.vs", "resources/shader/lightingshader.fs");
    Shader lampshader("resources/shader/lampshader.vs", "resources/shader/lampshader.fs");
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    unsigned int lightVAO;
    glGenVertexArrays(1,&lightVAO);
    glBindVertexArray(lightVAO);

    while (!glfwWindowShouldClose(s_gcw_UIC->window))
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
        s_gcw_UIC->g_cnc->deltaTime = currentFrame - s_gcw_UIC->g_cnc->lastFrame;
        s_gcw_UIC->g_cnc->lastFrame = currentFrame;

        glfwPollEvents();

        {
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            {
                static float f = 0.0f;
                static int counter = 0;
                ImGui::Begin("Coordinate Controls");
                ImGui::Checkbox("Show Control Window", &show_demo_window);      // Edit bools storing our window open/close state

                ImGui::ColorEdit3("Background color", clearColor); // Edit 3 floats representing a color

                ImGui::DragFloat("Model X", &c_model.coords.x, 0.5f);
                ImGui::DragFloat("Model Y", &c_model.coords.y, 0.5f);
                ImGui::DragFloat("Model Z", &c_model.coords.z, 0.5f);

                ImGui::InputFloat("Model radians", c_model.radians);

                ImGui::DragFloat("View Pos X", &c_view_pos.coords.x, 0.5);
                ImGui::DragFloat("View Pos Y", &c_view_pos.coords.y, 0.5);
                ImGui::DragFloat("View Pos Z", &c_view_pos.coords.z, 0.5);

                ImGui::DragFloat("View LookAt X", &c_view_la.coords.x, 0.5);
                ImGui::DragFloat("View LookAt Y", &c_view_la.coords.y, 0.5);
                ImGui::DragFloat("View LookAt Z", &c_view_la.coords.z, 0.5);

                ImGui::DragFloat("Projection radians", c_projection.radians, 0.5f);
                ImGui::DragFloat("Projection zNear", &c_projection.near, 0.01f);
                ImGui::DragFloat("Projection zFar", &c_projection.far, 2.5f);

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

        glfwMakeContextCurrent(s_gcw_UIC->window);
        glfwGetFramebufferSize(s_gcw_UIC->window, &s_gcw_UIC->display_w, &s_gcw_UIC->display_h);
        glViewport(0, 0, s_gcw_UIC->display_w, s_gcw_UIC->display_h);
        //glClearColor(s_gcw_UIC->clear_color.x, s_gcw_UIC->clear_color.y, s_gcw_UIC->clear_color.z, s_gcw_UIC->clear_color.w);
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        // create transformations
        // create transformations
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);

        //model = glm::rotate(model, glm::radians(*c_model.radians), glm::vec3(c_model.coords.x, c_model.coords.y, c_model.coords.z));

        view  = gcw_UIC->g_cnc->getViewMatrix();

        projection = glm::perspective(glm::radians(*c_projection.radians), (float)s_gcw_UIC->display_w / (float)s_gcw_UIC->display_h, c_projection.near, c_projection.far);


        s_gcw_UIC->g_cnc->computeMatricesFromInputs();

        //view = s_gcw_UIC->g_cnc->camera->getViewMatrix();
        //projection = glm::perspective(glm::radians(c_projection.angle), (float)s_gcw_UIC->display_w / (float)s_gcw_UIC->display_h, c_projection.near, c_projection.far);
        //projection = glm::ortho(0.0f, (float) s_gcw_UIC->display_w, 0.0f, (float) s_gcw_UIC->display_h, 0.1f, 100.0f);
        //projection = s_gcw_UIC->g_cnc->camera->getProjectionMatrix();
        // get matrix's uniform location and set matrix

        lightingshader.use();
        lightingshader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingshader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

        lightingshader.setMat4("projection", projection);
        lightingshader.setMat4("view", view);
        lightingshader.setMat4("model", model);

        lampshader.use();
        lampshader.setMat4("projection", projection);
        lampshader.setMat4("view", view);

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(2.0f));
        lampshader.setMat4("model", model);

        glBindVertexArray(lightVAO);

        model = glm::mat4(1.0f);
        g_rectangle->lo_shader->use();
        unsigned int modelLoc = glGetUniformLocation(g_rectangle->lo_shader->ID, "model");
        unsigned int viewLoc  = glGetUniformLocation(g_rectangle->lo_shader->ID, "view");
        unsigned int projectionLoc  = glGetUniformLocation(g_rectangle->lo_shader->ID, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        g_rectangle->renderTexLayer(0);
        g_rectangle->draw_object(g_rectangle);

        //draw_object(lo_rectangle);
        if(s_gcw_UIC->show_ui == true)
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(s_gcw_UIC->window);
        glfwSwapBuffers(s_gcw_UIC->window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    //delete_object(lo_rectangle);
    g_rectangle->delete_object(g_rectangle);

    glfwDestroyWindow(s_gcw_UIC->window);
    glfwTerminate();

    return 0;
}
