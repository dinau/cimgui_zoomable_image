// cimgui_zoomable_image.h
// C language wrapper for imgui_zoomable_image.h
//
// Original library: ImGui Zoomable Image
// Original author: Daniel Moreno
// Original license: MIT
//
// This C wrapper follows the same MIT license terms.
//------------------------------------------------------------------------------

#ifndef CIMGUI_ZOOMABLE_IMAGE_H
#define CIMGUI_ZOOMABLE_IMAGE_H


#ifdef __cplusplus
  extern "C" {
//  typedef ImU64 ImTextureID;
//  typedef struct ImTextureData ImTextureData;
//  typedef struct T_IM_TEXTURE_REF T_IM_TEXTURE_REF;
//  struct T_IM_TEXTURE_REF {
//      ImTextureData* _TexData;
//      ImTextureID _TexID;
//  };
//  typedef struct T_IM_VEC2 T_IM_VEC2;
//  struct T_IM_VEC2
//  {
//      float x, y;
//  };
//  typedef struct ImVec4_c ImVec4_c;
//  struct ImVec4_c
//  {
//      float x, y, z, w;
//  };
#endif

// ----------------------------------- Types ----------------------------------

// C equivalent of ImGuiImage::State
typedef struct ImGuiImageState
{
    // User Inputs
    bool           zoomPanEnabled;       // Enable/disable zoom and pan (default: true)
    bool           maintainAspectRatio;  // Maintain aspect ratio (default: false)
    float          maxZoomLevel;         // Max zoom level; 0.0 = auto (default: 0.0)
    T_IM_VEC2         textureSize;          // Original texture size in pixels (default: {0,0})

    // Outputs (set by the widget each frame)
    float          zoomLevel;            // Current zoom level (1.0 = 100%)
    T_IM_VEC2         panOffset;            // Current pan offset in normalized coords
    T_IM_VEC2         mousePosition;        // Mouse pos within image, or NaN if outside
} ImGuiImageState;

// ----------------------------------- Functions ------------------------------

// Initialize an ImGuiImageState with default values.
// Call this before the first use of the state.
void ImGuiImage_State_Init(ImGuiImageState* state);

// Display a zoomable/pannable image.
// Drop-in replacement for ImGui::Image() with zoom/pan support.
//
// Parameters:
//   texRef      - ImGui texture reference
//   displaySize - Size to display the image in the window
//   state       - Pointer to state struct (may be NULL for no zoom/pan)
void ImGuiImage_Zoomable(
    T_IM_TEXTURE_REF          texRef,
    const T_IM_VEC2*         displaySize,
    ImGuiImageState*        state);

// Same as ImGuiImage_Zoomable() but with explicit UV coordinates.
//
// Parameters:
//   uv0 - UV coordinates of the top-left corner
//   uv1 - UV coordinates of the bottom-right corner
void ImGuiImage_ZoomableUV(
    T_IM_TEXTURE_REF          texRef,
    const T_IM_VEC2*         displaySize,
    const T_IM_VEC2*         uv0,
    const T_IM_VEC2*         uv1,
    ImGuiImageState*        state);

// Full version with all parameters explicitly specified.
//
// Parameters:
//   bgColor   - Background color behind the image
//   tintColor - Tint color applied to the image
void ImGuiImage_ZoomableFull(
    T_IM_TEXTURE_REF          texRef,
    const T_IM_VEC2*         displaySize,
    const T_IM_VEC2*         uv0,
    const T_IM_VEC2*         uv1,
    const T_IM_VEC4*         bgColor,
    const T_IM_VEC4*         tintColor,
    ImGuiImageState*        state);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // CIMGUI_ZOOMABLE_IMAGE_H
