ifeq ($(OS),Windows_NT)
	PYTHON = python
else
	PYTHON = python3
endif

all:
	$(MAKE) -C demo/cimgui
	$(MAKE) -C demo/dcimgui

.PHONEY: clean

clean:
	@-$(MAKE) -C demo/cimgui   clean
	@-$(MAKE) -C demo/dcimgui   clean

CIMGUI_ORG_DIR = ../cimgui
gen:
	-rm -fr libs/cimgui
	-mkdir -p libs/cimgui/imgui/backends
	-cp  $(CIMGUI_ORG_DIR)/{cimgui*.*,LICENSE,*.md,Makefile}            libs/cimgui/
	-cp  $(CIMGUI_ORG_DIR)/imgui/*.*                                    libs/cimgui/imgui/
	-cp  $(CIMGUI_ORG_DIR)/imgui/backends/imgui_impl_{glfw.*,opengl3*}  libs/cimgui/imgui/backends/


server:
	$(PYTHON) -m http.server 8000
