#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct mem_block_t {
    size_t size;
    struct mem_block_t *next;
    int is_free;
} mem_block_t;

#define BLOCK_STRUCT_SIZE sizeof(mem_block_t)
mem_block_t *first_block = NULL;

mem_block_t *find_free_block(size_t size) {
    // Find free space 
    // 1. Parse known allocated memory
    mem_block_t *current = first_block;
    mem_block_t new_block;

    while(current && !(current->is_free && current->size >= size)) {
        current = current->next;
    }    
    return current;
}

mem_block_t *allocate_space(mem_block_t *last_block, size_t size) {
    mem_block_t *head = sbrk(0);
    mem_block_t *new_block = sbrk(size + BLOCK_STRUCT_SIZE);
    
}

void *custom_malloc(size_t size) {
    if(size == 0) {
        return NULL;
    }
    void *p = sbrk(0);

    if(!first_block) {
        mem_block_t *free_block = find_free_block(size);
    } else {

    }
    mem_block_t *new_block = find_free_block(size);
    void *addr;
    // Check return find_free_block
    if (new_block == NULL) {
        printf("Error in findind new free block");
        // return 1;
    }
    addr = (sbrk(size));
    if( addr != (void*)-1){
        printf("%li bytes have been allocated", size);

    } else {
        printf("Error");
        return NULL;
    }
}

void free(void *ptr) {

}

void *realloc(void *ptr, size_t size) {

}

void *realloc(void *ptr, size_t size) {

}

int main() {
    int size_block = 1024;
    int *new_variable = custom_malloc(size_block);
}

// "custom_alloc"
// 1. size != 0 ?
// a.2> Free space already available
//   3> Add to the memory list
// b.2> Need to push program break
// 3.  
// Return custom_alloc : pointer ptr to the allocated space
// value of ptr assigned like : *ptr = value