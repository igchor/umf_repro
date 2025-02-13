cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(test_l0)

#set(UMF_DIR /user/svinogra/unified-memory-framework)
set(UMF_DIR /home/gta/unified-memory-framework)


set(UR_LEVEL_ZERO_LOADER_TAG 399cd159d00f08685f1a1281fec4ea732d8021cb)
set(UR_LEVEL_ZERO_LOADER_REPO "https://github.com/nrspruit/level-zero.git")

set(BUILD_STATIC ON)

include(FetchContent)
    FetchContent_Declare(level-zero-loader
        GIT_REPOSITORY    ${UR_LEVEL_ZERO_LOADER_REPO}
        GIT_TAG           ${UR_LEVEL_ZERO_LOADER_TAG}
    )

FetchContent_MakeAvailable(level-zero-loader)
FetchContent_GetProperties(level-zero-loader)

include_directories(${UMF_DIR}/include)
include_directories(${UMF_DIR}/examples/common)
link_directories(${UMF_DIR}/build/lib)

add_executable(test main.cpp examples_level_zero_helpers.cpp)
target_link_libraries(test PRIVATE ze_loader umf)
