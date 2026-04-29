#include "appImGui.h"
#include "loadImage.h"

#include "cimgui_zoomable_image.h"


#if defined(DCIMGUI)
#  define C_INTERFACE_LIB     "[ Dear Bindings ]"
#  define igBegin                 ImGui_Begin
#  define igEnd                   ImGui_End
#  define igGetIO                 ImGui_GetIO
#  define igShowDemoWindow        ImGui_ShowDemoWindow
#  define igGetMainViewport       ImGui_GetMainViewport
#  define igSetNextWindowPos      ImGui_SetNextWindowPosEx
#  define igSetNextWindowSize     ImGui_SetNextWindowSize
#  define igGetContentRegionAvail ImGui_GetContentRegionAvail
#  define igCheckbox              ImGui_Checkbox
#  define igButton                ImGui_ButtonEx
#  define igSeparator             ImGui_Separator
#  define igText                  ImGui_Text
# else
#  define C_INTERFACE_LIB     "[ CImGui ]"
#endif

//------
// main
//------
void gui_main(Window *window) {
  ImGuiIO* pio = igGetIO();
  //#define DEFAULT_VECTOR_FONT
  #if defined(DEFAULT_VECTOR_FONT)
    ImFontAtlas_AddFontDefaultVector(pio->Fonts, NULL);
    igGetStyle()->FontScaleMain = 1.2;
    #undef  ICON_FA_DOG
    #define ICON_FA_DOG
  #else
    setupFonts();
  #endif

  bool showDemoWindow = true;

  // Image texture
  ImTextureRef textureRef;

  //---------------------------
  // Init imgui_zoomable_image
  //---------------------------
  //   preserved across frames to maintain zoom and pan state.
  static ImGuiImageState zoomState;
  ImGuiImage_State_Init(&zoomState);

  //------------
  // Load image
  //------------
  const char* ImageName = "./resources/dinosaurs_paradise.jpg";
  unsigned int textureId;
  int32_t  textureWidth  = 0;
  int32_t  textureHeight = 0;
  LoadTextureFromFile(ImageName, &textureId, &textureWidth, &textureHeight);
  textureRef._TexID = textureId;

  //-----------------
  // main event loop
  //-----------------
  while (!glfwWindowShouldClose(window->handle)) {
    glfwPollEvents();
    newFrame();

    if (showDemoWindow)
      igShowDemoWindow(&showDemoWindow);

    ImVec2 frameSize =   igGetMainViewport()->Size;
    ImVec2 imageWindowPos    = (ImVec2){frameSize.x * 0.1f, frameSize.y * 0.1f};
    ImVec2 imageWindowSize   = (ImVec2){frameSize.x * 0.5f, frameSize.y * 0.5f};
    ImVec2 controlsWindowPos = (ImVec2){frameSize.x * 0.7f, frameSize.y * 0.1f};

    //---------------------------------
    // imgui_zoomable_image demo in C
    //---------------------------------
    igSetNextWindowPos(imageWindowPos, ImGuiCond_FirstUseEver, (ImVec2){0, 0});

    igSetNextWindowSize(imageWindowSize, ImGuiCond_FirstUseEver);
    zoomState.textureSize = (ImVec2){textureWidth, textureHeight};
    igBegin("ImGui Zoomable Image demo in C with " C_INTERFACE_LIB " "  ICON_FA_DOG, NULL, 0);
      const ImVec2 displaySize = igGetContentRegionAvail();
      ImGuiImage_Zoomable(textureRef, &displaySize, &zoomState);
    igEnd();

    //-------------------------------------------------------------
    // Create a window displaying information about the test image
    //-------------------------------------------------------------
    igSetNextWindowPos(controlsWindowPos, ImGuiCond_FirstUseEver, (ImVec2){0, 0});
    {
      igBegin("Controls Window", NULL, 0);
      igCheckbox("Enable Zoom/Pan", &zoomState.zoomPanEnabled);
      igCheckbox("Maintain Aspect Ratio", &zoomState.maintainAspectRatio);
      if (igButton("Reset Zoom/Pan", (ImVec2){0, 0}))
      {
        zoomState.zoomLevel = 1.0f;
        zoomState.panOffset = (ImVec2){0.0f, 0.0f};
      }
      igSeparator();
      igText("Texture Size: %u x %u", textureWidth, textureHeight);
      igText("Display Size: %.0f x %.0f", displaySize.x, displaySize.y);
      igText("Zoom Level: %.2f%%", zoomState.zoomLevel * 100.0f);
      igText("Pan Offset: (%.2f, %.2f)", zoomState.panOffset.x * textureWidth,
                                              zoomState.panOffset.y * textureHeight);
      igText("Mouse Pos: (%.2f, %.2f)", zoomState.mousePosition.x,
                                             zoomState.mousePosition.y);
      igSeparator();
      igText("Application average %.3f ms/frame (%.1f FPS)",
        1000.0f / pio->Framerate, pio->Framerate);
      igEnd();
    }

    //--------
    // render
    //--------
    render(window);
  }

  glDeleteTextures(1, &textureId);
}

//------
// main
//------
int main(int argc, char *argv[]) {
  Window *window = createImGui(1200, 830, "CImGuiImage (2026/04)");

#if defined(DCIMGUI)
  setTheme(0); // Dark
#else
  setTheme(1); // Classic
#endif

  gui_main(window);

  destroyImGui(window);
}
