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

    //-----------------------
    // show a simple window
    //-----------------------
    igBegin("ImGui Zoomable Image Demo in C " ICON_FA_DOG, NULL, 0);
      igText("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / pio->Framerate, pio->Framerate);
    igEnd();

    //---------------------------------
    // imgui_zoomable_image demo in C
    //---------------------------------
    zoomState.textureSize = (ImVec2_c){textureWidth, textureHeight};
    igBegin("ImGui Zoomable Image", NULL, 0);
      const ImVec2_c displaySize = igGetContentRegionAvail();
      ImGuiImage_Zoomable(textureRef, &displaySize, &zoomState);
    igEnd();

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
