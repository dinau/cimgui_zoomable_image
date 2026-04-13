#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "appImGui.h"
#include "loadImage.h"

#include "cimgui_zoomable_image.h"

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
  ImTextureRef_c textureRef;

  //---------------------------
  // Init imgui_zoomable_image
  //---------------------------
  //   preserved across frames to maintain zoom and pan state.
  static ImGuiImageState zoomState;
  ImGuiImage_State_Init(&zoomState);

  //------------
  // Load image
  //------------
  const char* ImageName = "./resources/dinosaurs_paradise.png";
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

    ImVec2_c frameSize =   igGetMainViewport()->Size;
    ImVec2_c imageWindowPos    = (ImVec2_c){frameSize.x * 0.1f, frameSize.y * 0.1f};
    ImVec2_c imageWindowSize   = (ImVec2_c){frameSize.x * 0.5f, frameSize.y * 0.5f};
    ImVec2_c controlsWindowPos = (ImVec2_c){frameSize.x * 0.7f, frameSize.y * 0.1f};

    //---------------------------------
    // imgui_zoomable_image demo in C
    //---------------------------------
    igSetNextWindowPos(imageWindowPos, ImGuiCond_Once, (ImVec2_c){0, 0});
    igSetNextWindowSize(imageWindowSize, ImGuiCond_Once);
    zoomState.textureSize = (ImVec2_c){textureWidth, textureHeight};
    igBegin("ImGui Zoomable Image demo in C " ICON_FA_DOG, NULL, 0);
      const ImVec2_c displaySize = igGetContentRegionAvail();
      ImGuiImage_Zoomable(textureRef, &displaySize, &zoomState);
    igEnd();

    //-------------------------------------------------------------
    // Create a window displaying information about the test image
    //-------------------------------------------------------------
    igSetNextWindowPos(controlsWindowPos, ImGuiCond_Once, (ImVec2_c){0, 0});
    {
      igBegin("Controls Window", NULL, 0);
      igCheckbox("Enable Zoom/Pan", &zoomState.zoomPanEnabled);
      igCheckbox("Maintain Aspect Ratio", &zoomState.maintainAspectRatio);
      if (igButton("Reset Zoom/Pan", (ImVec2_c){0, 0}))
      {
        zoomState.zoomLevel = 1.0f;
        zoomState.panOffset = (ImVec2_c){0.0f, 0.0f};
      }
      igSeparator();
      igText("Texture Size: %zu x %zu", textureWidth, textureHeight);
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

  gui_main(window);

  destroyImGui(window);
}
