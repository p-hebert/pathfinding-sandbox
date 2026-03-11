cmake_minimum_required(VERSION 3.25) # Matches project tooling/preset baseline.

project(pathfinding_sandbox VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Enforces C++20. Downgrades exit build with error.
set(CMAKE_CXX_EXTENSIONS OFF)        # Disable extensions, enforce ISO C++20 for portability.

# DEPENDENCIES -------------------------------------------------------------------------------------

include(CTest)
include(FetchContent)

# DEPENDENCIES.MAIN

# DEPENDENCIES.DEV

# DEPENDENCIES.TEST
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

# BUILD --------------------------------------------------------------------------------------------
# BUILD.MAIN
add_library(pathfinding_core
    src/app.cpp
)

target_include_directories(pathfinding_core PUBLIC src)

add_executable(pathfinding_sandbox
    src/main.cpp
)

target_link_libraries(pathfinding_sandbox
    PRIVATE pathfinding_core
)


# BUILD.TEST
if(BUILD_TESTING)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    file(GLOB_RECURSE UNIT_TEST_SOURCES CONFIGURE_DEPENDS
        tests/unit/*.cpp
    )

    add_executable(unit_tests ${UNIT_TEST_SOURCES})
    target_link_libraries(unit_tests
        PRIVATE
        pathfinding_core
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(unit_tests)
endif()


# CONFIG -------------------------------------------------------------------------------------------
# Guard flags to match compiler per env, for portability.
function(enable_project_warnings target_name)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang"
      OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${target_name} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
  elseif(MSVC)
    target_compile_options(${target_name} PRIVATE /W4)
  endif()
endfunction()

enable_project_warnings(pathfinding_core)
enable_project_warnings(pathfinding_sandbox)

if(BUILD_TESTING)
  enable_project_warnings(unit_tests)
endif()