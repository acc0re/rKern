cmake_minimum_required(VERSION 3.24)
project(raylib-project)

# C++ Standard and other settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
include_directories(include)

# All source and header files
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB ENGINE_SRC_FILES ${PROJECT_SOURCE_DIR}/src/engine/gui/manager/*.cpp)
add_executable(raylib-project ${SRC_FILES} ${ENGINE_SRC_FILES})

# Include directories for the main target
target_include_directories(raylib-project PRIVATE ${PROJECT_SOURCE_DIR}/include)

# ==== IMGUI ====
find_package(imgui QUIET)
if (NOT imgui_FOUND)
  FetchContent_Declare(
          ImGui
          GIT_REPOSITORY https://github.com/ocornut/imgui.git
          GIT_TAG v1.91.3
  )
  FetchContent_MakeAvailable(ImGui)
  add_library(
          imgui STATIC
          ${imgui_SOURCE_DIR}/imgui.cpp
          ${imgui_SOURCE_DIR}/imgui_draw.cpp
          ${imgui_SOURCE_DIR}/imgui_demo.cpp
          ${imgui_SOURCE_DIR}/imgui_widgets.cpp
          ${imgui_SOURCE_DIR}/imgui_tables.cpp
  )
  target_include_directories(imgui INTERFACE ${imgui_SOURCE_DIR})
endif()

# ==== RAYLIB ====
find_package(raylib QUIET)
if (NOT raylib_FOUND)
  FetchContent_Declare(
          raylib
          GIT_REPOSITORY https://github.com/raysan5/raylib.git
          GIT_TAG 5.0
  )
  FetchContent_MakeAvailable(raylib)
endif()

# ==== RAYLIB_CPP ====
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
  FetchContent_Declare(
          raylib_cpp
          GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
          GIT_TAG v5.0.2
  )
  FetchContent_MakeAvailable(raylib_cpp)
  target_include_directories(raylib-project PRIVATE ${raylib_cpp_SOURCE_DIR}/include)
endif()

# ==== RLIMGUI ====
find_package(rlimgui QUIET)
if (NOT rlimgui_FOUND)
  FetchContent_Declare(
          rlImGui
          GIT_REPOSITORY https://github.com/raylib-extras/rlImGui
          GIT_TAG c7303258e045b4698c3e0b930b71956b5bbe7dff
  )
  FetchContent_MakeAvailable(rlImGui)
  add_library(rlimgui STATIC ${rlimgui_SOURCE_DIR}/rlImGui.cpp)
  target_include_directories(rlimgui INTERFACE ${rlimgui_SOURCE_DIR})
  target_link_libraries(rlimgui PRIVATE imgui raylib)
endif()

# Link all libraries
target_link_libraries(raylib-project PRIVATE imgui rlimgui raylib raylib_cpp)

# Include directories and libraries for all relevant targets
target_include_directories(raylib-project PRIVATE ${imgui_SOURCE_DIR} ${raylib_SOURCE_DIR} ${rlimgui_SOURCE_DIR})
target_link_libraries(raylib-project PRIVATE imgui raylib rlimgui raylib_cpp)