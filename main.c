#include <dlfcn.h>
#include <stdio.h>
#include <umf/memory_pool.h>

void* (*alloc)(void);

int main() {
    // Work fine if RTLD_GLOBAL is used
    void *handle = dlopen("libipc.so", RTLD_LAZY | RTLD_LOCAL);
    if (!handle) { 
	    printf("dlopen failed\n");
	    return 1;
    }
    *(void**)&alloc = dlsym(handle, "alloc");
    if (!alloc) {
	    printf("dlsym failed\n");
	    return 1;
    }
    void *ptr = alloc();
    fprintf(stderr, "ptr: %p\n", ptr);

    umf_memory_pool_handle_t umfPool = umfPoolByPtr(ptr);
}
