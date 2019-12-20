@echo off
cd ..

SET dir=%cd%
rem ECHO %dir%

SET build_dir=%dir%\libs\SDL2-2.0.9\build
rem ECHO %build_dir%

mkdir %build_dir%
cd %build_dir%

rem ECHO %cd%

cmake -G "Visual Studio 15 2017 Win64" ..

pause