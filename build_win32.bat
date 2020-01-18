@REM Build for Visual Studio compiler. Run your copy of vcvars32.bat or vcvarsall.bat to setup command-line compiler.
@echo off
::"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
mkdir Debug
mkdir Release
del .\Debug\*.exe
del .\Debug\*.obj
echo.
set /A bt_flag=0
set /A BUILD_TYPE=Debug
set bt_flag=0
if %bt_flag%==0 set BUILD_TYPE=Debug
if %bt_flag%==1 set BUILD_TYPE=Release
set GLFW_DIR=..\libs\glfw
set GL3W_DIR=..\libs\gl3w
set GLM_DIR=..\..\..\..\lib-windows\glm
set IMGUI_DIR=..\..\
::echo %BUILD_TYPE%  %GLFW_DIR%  %GL3W_DIR%   %IMGUI_DIR%
cl /Zi /std:c++17 /Zp /MD /c /I .. /I ..\.. /I include /I ..\..\..\..\lib-windows\FreeImage_win32\Dist\x64\ /I ..\..\..\..\lib-windows\FreeImage_win32\Wrapper\FreeImagePlus /I %GLFW_DIR%\include /I %GL3W_DIR%\ /I %GLM_DIR%\ *.cpp ..\imgui_impl_glfw.cpp ..\imgui_impl_opengl3.cpp %IMGUI_DIR%\imgui*.cpp %GL3W_DIR%\GL\gl3w.c /Fe%BUILD_TYPE%/%BUILD_TYPE%.exe /Fo%BUILD_TYPE%/
echo "Linking objects and libraries."
link /FORCE:MULTIPLE /out:%BUILD_TYPE%\Debug.exe Debug\*.obj ..\libs\glfw\lib-vc2010-64\glfw3.lib ..\..\..\..\lib-windows\FreeImage_win32\Dist\x64\FreeImage.lib ..\..\..\..\lib-windows\FreeImage_win32\Wrapper\FreeImagePlus\x64\Release\FreeImagePlus.lib opengl32.lib gdi32.lib shell32.lib
