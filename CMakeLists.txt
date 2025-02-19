cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(test_l0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(UR_LEVEL_ZERO_LOADER_TAG bebac0da1432b9d5bf36eb400ac1b0b30e682bb8)
set(UR_LEVEL_ZERO_LOADER_REPO "https://github.com/nrspruit/level-zero.git")

set(BUILD_STATIC ON)

include(FetchContent)
    FetchContent_Declare(level-zero-loader
        GIT_REPOSITORY    ${UR_LEVEL_ZERO_LOADER_REPO}
        GIT_TAG           ${UR_LEVEL_ZERO_LOADER_TAG}
    )

FetchContent_MakeAvailable(level-zero-loader)
FetchContent_GetProperties(level-zero-loader)

add_library(lib SHARED lib.cpp)
target_link_libraries(lib PRIVATE ze_loader)

add_executable(test main.cpp)
target_link_libraries(test PRIVATE lib)

