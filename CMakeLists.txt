cmake_minimum_required(VERSION 3.25) # Require CMake 3.25 for stable Presets support.

project(pathfinding_sandbox VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Enforces C++20. Downgrades exit build with error.
set(CMAKE_CXX_EXTENSIONS OFF)        # Disable extensions, enforce ISO C++20 for portability.

add_executable(pathfinding_sandbox
    src/main.cpp
)

# Guard flags to match compiler per env, for portability.
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"
    OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

    target_compile_options(pathfinding_sandbox PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

elseif (MSVC)

    target_compile_options(pathfinding_sandbox PRIVATE
        /W4
    )

endif()