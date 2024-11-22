project(test_l0)

#include_directories(/home/igchor/unified-memory-framework/include)
#include_directories(/home/igchor/unified-memory-framework/examples/common)
#link_directories(/home/igchor/unified-memory-framework/build/lib)

add_library(ipc SHARED lib.c)
target_link_libraries(ipc PRIVATE ze_loader umf libdisjoint_pool.a)

add_executable(test main.c)
target_link_libraries(test PRIVATE  umf)
