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
#   pacman -S --noconfirm --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-glfw
#

#CXX = g++
CXX = clang++

FREEIMAGE = /Users/edselmalasig/Experiments_in_Computer_Science/lib/Computer_Graphics/FreeImage
FREEIMAGE_LIB = /Users/edselmalasig/Experiments_in_Computer_Science/lib/FreeImage
FREEIMAGE_EXT = extensions/FreeImage
IMGUI = extensions/imgui
IMGUI_IMPL = $(IMGUI)/imgui_impl
IMGUIADDONS = $(IMGUI)/addons
SOURCES = main.cpp core/src/camera.cpp core/src/Geometry.cpp core/src/initialize.cpp
SOURCES += $(IMGUI_IMPL)/imgui_impl_glfw.cpp $(IMGUI_IMPL)/imgui_impl_opengl3.cpp
SOURCES += $(IMGUIADDONS)/imguistyleserializer/imguistyleserializer.cpp
SOURCES += $(IMGUI)/imgui.cpp $(IMGUI)/imgui_demo.cpp $(IMGUI)/imgui_draw.cpp $(IMGUI)/imgui_widgets.cpp
SOURCES += $(FREEIMAGE_EXT)/fip_ImageOperations.cpp

OBJS =  $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)

##---------------------------------------------------------------------
## OPENGL LOADER
##---------------------------------------------------------------------

## Using OpenGL loader: gl3w [default]
#SOURCES += ../libs/gl3w/GL/gl3w.c ../../../../Computer_Graphics/FreeImage/src/fip_ImageOperations.cpp
#CXXFLAGS = -I../libs/gl3w

## Using OpenGL loader: glew
## (This assumes a system-wide installation)
 CXXFLAGS = -lGLEW -DIMGUI_IMPL_OPENGL_LOADER_GLEW

## Using OpenGL loader: glad
## (You'll also need to change the rule at line ~77 of this Makefile to compile/link glad.c/.o)
# SOURCES += ../libs/glad/src/glad.c
# CXXFLAGS = -I../libs/glad/include -DIMGUI_IMPL_OPENGL_LOADER_GLAD

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux compilation"
	FREEIMAGE = /home/notadeveloper/Desktop/Experiments_in_Computer_Science/lib/FreeImage
	FREEIMAGE_LIB =  /home/notadeveloper/Desktop/Experiments_in_Computer_Science/lib/FreeImage/Dist
	EXE = engine-X.out
	LIBS = -lGL -lglfw
	LIBS += -L$(FREEIMAGE_LIB) -lfreeimage -lfreeimageplus `pkg-config --libs glfw3`

	CXXFLAGS += `pkg-config --cflags glfw3`
	CXXFLAGS += -I/usr/local/include
	CXXFLAGS += -I./ -I$(IMGUI)/ -I$(IMGUI_IMPL)/ -I$(IMGUIADDONS)/ -I$(IMGUIADDONS)/imguistyleserializer/
	CXXFLAGS += -I $(FREEIMAGE)/include
	CXXFLAGS += -I $(FREEIMAGE_LIB)/Source -I$(FREEIMAGE_LIB)/Wrapper/FreeImagePlus/
	CXXFLAGS += -Wall -Wformat -DGLM_ENABLE_EXPERIMENTAL -DFREEIMAGE_LIB -g
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	EXE = engine-X.macos
	LIBS = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
	#LIBS += -L/usr/local/lib -lglfw
	LIBS += -L$(FREEIMAGE_LIB) -lfreeimage -lfreeimageplus
	LIBS += -lglfw

	CXXFLAGS += -DFREEIMAGE_LIB
	CXXFLAGS += -I/usr/local/include
	CXXFLAGS += -I core/ -I core/include/ -I core/src/
	CXXFLAGS += -I./ -I$(IMGUI)/ -I$(IMGUI_IMPL)/ -I$(IMGUIADDONS)/ -I$(IMGUIADDONS)/imguistyleserializer/
	CXXFLAGS += -I /Users/edselmalasig/lib/glm -I/Users/edselmalasig/lib/glfw/include
	CXXFLAGS += -I $(FREEIMAGE)/include -I $(FREEIMAGE_LIB)/Source -I$(FREEIMAGE_LIB)/Wrapper/FreeImagePlus/
	CXXFLAGS += -I $(FREEIMAGE_EXT)/
	CXXFLAGS += -Wall -Wformat
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
   ECHO_MESSAGE = "Windows"
	 EXE = example_glfw_opengl
   LIBS = -lglfw3 -lgdi32 -lopengl32 -limm32

   CXXFLAGS += -I../ -I../../ `pkg-config --cflags glfw3`
   CXXFLAGS += -Wall -Wformat
   CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------
%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:core/src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(FREEIMAGE)/src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(FREEIMAGE_EXT)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI)/imgui_impl/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

#%.o:../libs/gl3w/GL/%.c
# %.o:../libs/glad/src/%.c
#	$(CC) $(CFLAGS) -c -o $@ $<

%.o:$(IMGUI)/addons/imguistyleserializer/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
	@echo =======================================================================
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS)
