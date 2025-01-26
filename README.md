# rKern

This project is inspired by the **Laser Blast** game for the Atari 2600 and is developed in **C++** using [Raylib](https://github.com/raysan5/raylib). The build system is managed using **CMake**.

## Prerequisites
Ensure you have the following installed:
- **C++** compiler (e.g., GCC, Clang, or MSVC)
- **CMake** (version 3.15 or higher)
- Raylib

## How to Build
1. Open the `CMakeLists.txt` file and update the project name and executable name at the following lines:
   ```cpp
   2   project(PROJECT_NAME)
   9   add_executable(PROJECT_NAME src/main.cpp) // Or list all .cpp files in your src/
   54  target_link_libraries(PROJECT_NAME PRIVATE imgui rlimgui raylib raylib_cpp)
