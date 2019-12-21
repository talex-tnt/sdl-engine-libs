Dependencies:
- [CMake](https://cmake.org/download/)
- [SDL2-2.0.9](https://www.libsdl.org/download-2.0.php)

Please install **CMake** first and download **SDL2-2.0.9**.

The *scripts* folder contains the following scripts:  
- [**proj-vsc/gen_proj-vsc.bat**](scripts/proj-vsc/gen_proj-vsc.bat) generates Visual Studio project files in `scripts/proj-vsc/build-vsc`  
- [**proj-vsc/start_proj-vsc.bat**](scripts/proj-vsc/start_proj-vsc.bat) eventually generates Visual Studio project and then starts it.
- [**proj-vsc/clear_proj.bat**](scripts/proj-vsc/clear_proj.bat) cleans up the `scripts/proj-vsc/build-vsc` folder containing the project files.

- [**proj-llvm/gen_proj-llvm.bat**](scripts/proj-llvm/gen_proj-llvm.bat) generates Visual Studio project files in `scripts/proj-llvm/build-llvm`   
- [**proj-llvm/start_proj-llvm.bat**](scripts/proj-llvm/start_proj-llvm.bat) eventually generates Visual Studio project and then starts it.
- [**proj-llvm/clear_proj.bat**](scripts/proj-llvm/clear_proj.bat) cleans up the `scripts/proj-llvm/build-llvm` folder containing the project files.

- [**clear_projects.bat**](scripts/clear_projects.bat) cleans up `scripts/proj-*/build-*` folders containing the project files.  
- [**gen_proj-SDL.bat**](scripts/gen_proj-SDL.bat) generates Visual Studio project files for **SDL2-2.0.9**.  
  Fix this script for supporting a different version.  
  At the moment it expects a folder `libs/SDL2-2.0.9`   
  containing all the **SDL** files.   
  

**SDL2**   
Download the sources and extract them into the `libs` folder,   
run [scripts/**gen_proj-SDL.bat**](scripts/gen_proj-SDL.bat)   
open *Visual Studio* and **build** the project.

Then create the sibiling folder `/app`   
(it is set as working directory by cmake)   
and copy the `SDL2.dll` file in it, after the `SDL2-2.0.9` is built.

**Generate and start the project**  
You can then run [scripts/proj-vsc/**gen_proj-vsc.bat**](scripts/proj-vsc/gen_proj-vsc.bat) 
to generate the *Visual Studio* project inside `scripts/proj-vsc/build-vsc`,   
and open the solution in it.
Or you can just run `start_proj-vsc.bat` to build and open the solution once built automatically.


If you want to build with *LLVM/Clang*  
please download and install [**llvm** pre-built binaries](http://releases.llvm.org/download.html)  
and the [**LLVM Toolchain Extension** for *Visual Studio 2017*](https://marketplace.visualstudio.com/items?itemName=LLVMExtensions.llvm-toolchain)  
Then run [scripts/proj-llvm/**gen_proj-llvm.bat**](scripts/proj-llvm/gen_proj-llvm.bat) 
that will generates *Visual Studio* project files   
under `scripts/proj-llvm/build-llvm` with **llvm** as **target**.   
To build and open the solution once created just run `start_proj-llvm.bat`
