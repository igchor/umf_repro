project(test_l0)

set(UMF_DIR /user/svinogra/unified-memory-framework)
#set(UMF_DIR /home/igchor/unified-memory-framework)


include_directories(${UMF_DIR}/include)
include_directories(${UMF_DIR}/examples/common)
link_directories(${UMF_DIR}/build/lib)

add_library(ipc SHARED lib.c ${UMF_DIR}/examples/common/examples_level_zero_helpers.c)
target_link_libraries(ipc PRIVATE ze_loader umf libdisjoint_pool.a)

add_executable(test main.c)
target_link_libraries(test PRIVATE umf)
