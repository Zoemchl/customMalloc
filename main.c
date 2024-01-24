#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct mem_block_t {
    size_t size;
    struct mem_block_t *next;
    int is_free;
} mem_block_t;

void *find_free_block(mem_block_t *last_block, size_t size) {
    mem_block_t new_block;
    // Find free space 
    // 1. Parse known allocated memory
    mem_block_t *current = last_block;
    

    // 2. Stop when one free
}
void *custom_malloc(size_t size) {
    if(sbrk(size) != (void*)-1) {
        find_free_block(NULL, size);

        printf("%i bytes have been allocated", size);

    } else {
        printf("Error");
        return NULL;
    }
}

int main() {
    int new_space = 1024;
    custom_malloc(new_space);
}

