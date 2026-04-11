#pragma once

#ifdef __cplusplus
#  include "imgui.h"
#  include "imgui_impl_glfw.h"
#  include "imgui_impl_opengl3.h"
extern "C" {
#else
   #define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#  include "cimgui.h"
#endif

#include <GLFW/glfw3.h>
#include <stdio.h>
#ifdef _MSC_VER
#include <windows.h>
#endif
#include <GL/gl.h>

#ifdef IMGUI_HAS_IMSTR
#define igBegin igBegin_Str
#define igCheckbox igCheckbox_Str
#define igButton igButton_Str
#endif

#define igGetIO igGetIO_Nil


#include "setupFonts.h"
#include <stdlib.h>

typedef struct stWindow {
  GLFWwindow* handle;
  ImVec4 clearColor;
  int showDelayWindow;
} Window;

Window* createImGui(int32_t width, int32_t height, const char* title);
void destroyImGui(Window* window);
void render(Window* window);
void newFrame(void);
void setTheme(int32_t num);

#ifdef __cplusplus
}
#endif
