@echo off

set CURRENT_DIR=%cd%
echo %CURRENT_DIR%

cd %2
set ROOT=%cd%
echo %ROOT%

cd %CURRENT_DIR%
mkdir %3
cd %3
set ROOT_LIB_DIR=%ROOT%\libs

set SDL_VERSION=SDL2-2.0.9

set SDL_INCLUDE_PATH=%ROOT_LIB_DIR%\%SDL_VERSION%\include

set SDL_LIBRARY_PATH=%ROOT_LIB_DIR%\%SDL_VERSION%\build\Release

set SDL_LIBS=%SDL_LIBRARY_PATH%\SDL2.lib;%SDL_LIBRARY_PATH%\SDL2main.lib;Imm32.lib;version.lib


cmake -G %1 %ROOT% %4 %5^
 -DSDL2_INCLUDE_DIR=%SDL_INCLUDE_PATH%^
 -DSDL2_LIBRARY=%SDL_LIBS%

cd %ROOT%/scripts/cmd
Notification.bat "Visual Studio Solution is Ready" "%TOOLSET% Compiler"
rem pause