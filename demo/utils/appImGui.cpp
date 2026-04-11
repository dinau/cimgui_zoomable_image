#include "appImGui.h"

//------------------
// --- setTheme
//------------------
void setTheme(int32_t num){
  switch (num){
  case 0:
    ImGui::StyleColorsDark(NULL);
    break;
  case 1:
    ImGui::StyleColorsClassic(NULL);
    break;
  case 2:
    ImGui::StyleColorsLight(NULL);
    break;
  default:
    break;
  }
}

//---------------
// --- initImGui
//---------------
Window* createImGui(int32_t width, int32_t height, const char* title){
  if (!glfwInit())
    return NULL;

  // Decide GL+GLSL versions
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // Hide window at startup.

  const char *glsl_version = "#version 330";
  // just an extra window hint for resize
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  GLFWwindow* glfwwindow = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!glfwwindow)
  {
    printf("Failed to create window! Terminating!\n");
    glfwTerminate();
    return NULL;
  }

  glfwMakeContextCurrent(glfwwindow);

  // enable vsync
  glfwSwapInterval(1);

  // check opengl version sdl uses
  printf("opengl version: %s\n", (char *)glGetString(GL_VERSION));

  // setup imgui
  ImGui::CreateContext(NULL);

  ImGui_ImplGlfw_InitForOpenGL(glfwwindow, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  Window* window = (Window*)malloc(sizeof(Window));
  window->handle = glfwwindow;
  window->clearColor.x = 0.45f;
  window->clearColor.y = 0.55f;
  window->clearColor.z = 0.60f;
  window->clearColor.w = 1.00f;
  window->showDelayWindow = 1;

  return window;
}

//------------------
// --- destroyImGui
//------------------
void destroyImGui(Window* window){
  // clean up
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext(NULL);

  glfwDestroyWindow(window->handle);
  glfwTerminate();
  free(window);
}

//------------
// --- render
//------------
void render(Window* window){
    auto ioptr = ImGui::GetIO();
    // render
    ImGui::Render();
    glfwMakeContextCurrent(window->handle);
    glViewport(0, 0, (int)ioptr.DisplaySize.x, (int)ioptr.DisplaySize.y);
    glClearColor(window->clearColor.x, window->clearColor.y, window->clearColor.z, window->clearColor.w);

    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window->handle);

    if (window->showDelayWindow >= 0) window->showDelayWindow--;
    if (window->showDelayWindow == 0)  glfwShowWindow(window->handle); // Avoid flickering screen at startup.
}

//-------------
//--- newFrame
//-------------
void newFrame(void){
    // start imgui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
