@echo off
rem rmdir /s /q build
mkdir build
cd build
cmake -G "Visual Studio 15 2017 Win64" ../..
pause