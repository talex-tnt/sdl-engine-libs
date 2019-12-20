@echo off

set list="%cd%\proj-vsc\build-vsc" "%cd%\proj-llvm\build-llvm"

(for %%a in (%list%) do (
	IF EXIST %%a (
 		echo Deleting: %%a
   		rmdir /s /q %%a
   	) else (
   		 echo Not Found: %%a
   	)
)) 
