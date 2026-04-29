#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# You will need GLFW (http://www.glfw.org):
# Linux:
#   apt-get install libglfw-dev
# Mac OS X:
#   brew install glfw
# MSYS2:
#   pacman -S --noconfirm --needed mingw-w64-ucrt-x86_64-{toolchain,glfw}
#

#CXX = g++
#CXX = clang++

CXXFLAGS += -DDCIMGUI

EXE = cimgui_zoomable_image

ROOT_DIR              = ../..
LIBS_DIR              = $(ROOT_DIR)/libs
IMGUI_ZOOMABLE_IMAGE  = $(LIBS_DIR)/imgui_zoomable_image
CIMGUI_DIR            = $(LIBS_DIR)/cimgui
DCIMGUI_DIR           = $(LIBS_DIR)/dcimgui
IMGUI_DIR             = $(CIMGUI_DIR)/imgui
UTILS_DIR             = ../utils
BUILD_DIR             = .build

VPATH = .. : $(IMGUI_ZOOMABLE_IMAGE): $(ROOT_DIR) : $(DCIMGUI_DIR): $(IMGUI_DIR) : $(UTILS_DIR) : $(IMGUI_DIR)/backends \
      : $(DCIMGUI_DIR)/backends

CSOURCES = main.c utils.c loadImage.c
SOURCES += imgui_impl_glfw.cpp      \
           imgui_impl_opengl3.cpp

SOURCES += $(notdir $(wildcard $(IMGUI_DIR)/*.cpp))
SOURCES += $(notdir $(wildcard $(IMGUI_ZOOMABLE_IMAGE)/*.cpp))
SOURCES += $(notdir $(wildcard $(ROOT_DIR)/*.cpp))
SOURCES += $(notdir $(wildcard $(UTILS_DIR)/*.cpp))
SOURCES += $(notdir $(wildcard $(DCIMGUI_DIR)/backends/*.cpp))
SOURCES += $(notdir $(wildcard $(DCIMGUI_DIR)/*.cpp))

CXXFLAGS += -MMD -MP
CXXFLAGS += -O1 -Wl,-s
CXXFLAGS += -I$(IMGUI_ZOOMABLE_IMAGE) -I$(DCIMGUI_DIR) -I$(DCIMGUI_DIR)/generator/output
CXXFLAGS += -I$(UTILS_DIR) -I$(ROOT_DIR) -I$(UTILS_DIR)/fonticon -I$(UTILS_DIR)/cpp
CXXFLAGS += -I$(IMGUI_ZOOMABLE_IMAGE) -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I$(DCIMGUI_DIR)/backends

OBJS = $(addprefix $(BUILD_DIR)/,$(CSOURCES:.c=.o)) $(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))
UNAME_S := $(shell uname -s)
LINUX_GL_LIBS = -lGL


CXXFLAGS += -g -Wall -Wformat
LIBS =

CFLAGS_EX += -DT_IM_TEXTURE_REF=ImTextureRef
CFLAGS_EX += -DT_IM_VEC2=ImVec2 -DT_IM_VEC4=ImVec4
CXXFLAGS_EX += -DT_IM_TEXTURE_REF=ImTextureRef
CXXFLAGS_EX += -DT_IM_VEC2=ImVec2 -DT_IM_VEC4=ImVec4

.PHONY: $(BUILD_DIR) clean run

##---------------------------------------------------------------------
## OPENGL ES
##---------------------------------------------------------------------

## This assumes a GL ES library available in the system, e.g. libGLESv2.so
# CXXFLAGS += -DIMGUI_IMPL_OPENGL_ES2
# LINUX_GL_LIBS = -lGLESv2

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
  ECHO_MESSAGE = "Linux"
  LIBS += $(LINUX_GL_LIBS) `pkg-config --static --libs glfw3`

  CXXFLAGS += -DIMGUI_IMPL_API="extern \"C\""
  CXXFLAGS += `pkg-config --cflags glfw3`
  CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
  ECHO_MESSAGE = "Mac OS X"
  LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
  LIBS += -L/usr/local/lib -L/opt/local/lib -L/opt/homebrew/lib
  #LIBS += -lglfw3
  LIBS += -lglfw

  CXXFLAGS += -I/usr/local/include -I/opt/local/include -I/opt/homebrew/include
  CFLAGS = $(CXXFLAGS)
endif

ifeq ($(OS), Windows_NT)
  ECHO_MESSAGE = "MinGW"
  LIBS += -lglfw3 -lgdi32 -lopengl32 -limm32

  CXXFLAGS += -DIMGUI_IMPL_API="extern \"C\" __declspec(dllexport)"
  CXXFLAGS += $(shell pkg-config --cflags glfw3)
  CXXFLAGS += -static
  CFLAGS = $(CXXFLAGS)
endif

.PHONY: $(BUILD_DIR) clean run
##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

all: $(BUILD_DIR) $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(BUILD_DIR):
	@-mkdir -p $@

$(BUILD_DIR)/%.o:%.c Makefile
	@echo [$(CC) ] $(notdir $<)
	@$(CC) $(CFLAGS) $(CFLAGS_EX) -c -o $@ $<

$(BUILD_DIR)/%.o:%.cpp Makefile
	@echo [$(CXX)] $(notdir $<)
	@$(CXX) $(CXXFLAGS) $(CXXFLAGS_EX)  -c -o $@ $<

$(EXE): $(OBJS)
	@$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(EXE)

run: all
	./$(EXE)

include $(wildcard $(BUILD_DIR)/*.d)
