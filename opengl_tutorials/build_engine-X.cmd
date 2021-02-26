@echo off
@REM Build for Visual Studio compiler. Run your copy of vcvars32.bat or vcvarsall.bat to setup command-line compiler.

title Building FreeImage project...

set LIB_DIR=E:\dev\lib
set FREEIMAGE_LIB_DIR=%LIB_DIR%\FreeImage\Dist\x64
set FREEIMAGEPLUS_LIB_DIR="%LIB_DIR%\FreeImage\Wrapper\FreeImagePlus\x64\Release"
set FREEIMAGE_PROJ=%LIBDIR%\FreeImage
set FREEIMAGE_PROJ=%FREEIMAGE_PROJ%;%FREEIMAGE_PROJ%\src
set FREEIMAGE_PROJ=%FREEIMAGE_PROJ%;%FREEIMAGE_PROJ%\include
set EX=E:\dev\engine-X
set external=%EX%\external
set GLEW=%LIB_DIR%\glew-2.1.0
set GLFW=%LIB_DIR%\glfw-3.3.2.bin.WIN64\
set ASSIMP=%LIB_DIR%\assimp\build-win
::set PATH=%PATH%;%LIBDIR%\FreeImage\dist\x64
::set PATH=%PATH%;%LIBDIR%\FreeImage\Wrapper\FreeImagePlus\x64\Release

::set OUT_DIR=.
::set OUT_EXE=%2

set INCLUDES=/I .. /I %EX%\core\include /I %EX%\core\src /I %external%\imgui /I %external%\imgui\imgui_impl /I %GLEW%\include
set INCLUDES=%INCLUDES% /I %external%\imgui\addons  /I %external%\imgui\addons\imguistyleserializer /I %external%\FreeImage
set INCLUDES=%INCLUDES% /I %LIB_DIR%\glm\ /I %EX%\plugins\ImageEditor\ /I %GLFW%\include /I %external%\stb /I %LIB_DIR%\assimp\include
set INCLUDES=%INCLUDES% /I %LIB_DIR%\assimp\build-win\include /I %external%\ImGuizmo
set INCLUDES=%INCLUDES%
set INCLUDES=%INCLUDES% /I %LIB_DIR%\FreeImage\Dist\x64

set LIBS=%FREEIMAGE_LIB_DIR%\FreeImage.lib OpenGL32.lib  glew32s.lib  glfw3dll.lib assimp-vc142-mt.lib


set LIBPATHS=/libpath:%FREEIMAGE_LIB_DIR% FreeImage.lib /libpath:%GLFW%\lib-vc2019\ glfw3dll.lib /libpath:%GLEW%\lib\Release\x64\ glew32.lib
set LIBPATHS=%LIBPATHS% /libpath:%ASSIMP%\lib\Release\ assimp-vc142-mt.lib

set BUILDTYPE=Release
set DFLAGS=/D WIN32 /D WINDOWS /D RELEASE /D _CONSOLE /D _WIN32 /D IMGUI_IMPL_OPENGL_LOADER_GLEW
set SOURCES=%EX%\opengl_tutorials\ColorPicking.cpp %external%\imgui\imgui.cpp %external%\imgui\imgui_demo.cpp
set SOURCES=%SOURCES% %external%\imgui\imgui_draw.cpp  %external%\imgui\imgui_widgets.cpp  %external%\imgui\imgui_impl\imgui_impl_opengl3.cpp %external%\imgui\imgui_impl\imgui_impl_glfw.cpp
set SOURCES=%SOURCES% %EX%\core\src\camera.cpp %external%\imgui\addons\imguistyleserializer\imguistyleserializer.cpp %EX%\core\src\camera.cpp
set SOURCES=%SOURCES% %EX%\core\src\Geometry.cpp %EX%\core\src\Primitive.cpp %EX%\core\src\EngineX.cpp
set SOURCES=%SOURCES% %external%\ImGuizmo\ImGuizmo.cpp %external%\ImGuizmo\ImSequencer.cpp %external%\ImGuizmo\ImCurveEdit.cpp %external%\ImGuizmo\ImGradient.cpp
set SOURCES=%SOURCES% %EX%\opengl_tutorials\texture.cpp %EX%\opengl_tutorials\objloader.cpp
set SOURCES=%SOURCES% %EX%\opengl_tutorials\shader.cpp  %EX%\opengl_tutorials\vboindexer.cpp
set SOURCES=%SOURCES% %EX%\opengl_tutorials\controls.cpp
cl  %DFLAGS% /nologo /MD /EHsc %DFLAGS% %SOURCES% %INCLUDES% /Feengine-X.exe /link /MACHINE:x64 /DYNAMICBASE:NO  /subsystem:console /TLBID:1 %LIBS% %LIBPATHS%
