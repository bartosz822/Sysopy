//
// Created by bartek on 13.03.17.
//

#include <dlfcn.h>
#include <stdlib.h>

void (*tree_benchmark)();
void (*list_benchmark)();


int main (){
    void * lib = dlopen("libshared_lib.so", RTLD_NOW);
    *(void**)(&tree_benchmark) = dlsym(lib, "tree_benchmark");
    *(void**)(&list_benchmark) = dlsym(lib, "list_benchmark");

    tree_benchmark();
    list_benchmark();

    dlclose(lib);

    return 0;
}