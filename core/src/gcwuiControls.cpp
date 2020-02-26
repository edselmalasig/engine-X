#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "gcwuiControls.h"

#include <stdio.h>
#include <string.h>

gcwuiControls::gcwuiControls()
{
     this->camera = new Camera();
     this->display_w = this->g_cnc->display_w;
     this->display_h = this->g_cnc->display_h;
}

gcwuiControls::gcwuiControls(Camera &cam)
{
     this->camera = cam;
     this->display_w = this->g_cnc->display_w;
     this->display_h = this->g_cnc->display_h;
}
