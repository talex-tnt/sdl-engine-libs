@echo off
call ../cmd/GenerateVSSolution.bat "Visual Studio 15 2017 Win64" ../.. "build-llvm" -T llvm
rem pause