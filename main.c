#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>

typedef struct mem_block_t {
    size_t size;
    struct mem_block_t* next;
    struct mem_block_t* previous; // TODO To keep ?
    int is_free;
} mem_block_t;

mem_block_t* first_block = NULL;

// Find an existing block that is free in the linked list
mem_block_t* find_free_block(size_t size) {
    mem_block_t* current = first_block;

    while (current && !(current->is_free && current->size >= size)) {
        current = current->next;
    }
    if(current) {
        printf("A block has been found at the address : %p\n", current);
        // current->previous = // TODO to keep ?
    }
    return current;
}

// Modify the available memory space on the heap
mem_block_t* allocate_block(mem_block_t* last_block, size_t size) {

    // Give the current top of the heap
    mem_block_t* head = sbrk(0);
    mem_block_t* new_block = sbrk(size);

    // When allocation fails
    if (new_block == (void*)-1) {  
        perror("sbrk");
        return NULL;
    }

    new_block->size = size;
    new_block->previous = head; // TODO to keep ?
    new_block->next = NULL;
    new_block->is_free = 0;

    if (last_block) {
        last_block->next = new_block;
    }

    return new_block;
}

// Manage the allocation of the memory on the heap of the program
void* custom_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }

    // If there is no element yet in the list of memory blocks
    if (!first_block) {
        first_block = allocate_block(NULL, size);
        return first_block ? (void*)(first_block) + sizeof(mem_block_t) : NULL;
    }

    mem_block_t* free_block = find_free_block(size);

    if (!free_block) {
        mem_block_t* last_block = first_block;
        while (last_block->next) {
            last_block = last_block->next;
        }

        free_block = allocate_block(last_block, size) + sizeof(mem_block_t);
        printf("%p\n", free_block);
    } else {
        free_block->is_free = 0;
        free_block->size = size;
    }
    return free_block;
}


void custom_free(void* ptr) {
    if (!ptr) {
        printf("Nothing to free !\n");
        return;
    }
    printf("%p\n", (mem_block_t*)ptr);
    // Moves backward the pointer by the size of a mem_block
    mem_block_t* block = (mem_block_t*)ptr - 1;

    printf("Freed space! of %zu bytes\n", block->size);
    printf("Mem_block at the address %p\n", block);

    block->is_free = 1;
    // TODO : handle when next block is free too (unite the two blocks into one new bigger one)
}


// Modify an already allocated memory block
void* custom_realloc(void* ptr, size_t size) {
    if (!ptr) {
        return custom_malloc(size);
    }

    mem_block_t* block = (mem_block_t*)ptr - 1;

    if (size == 0) {
        custom_free(ptr);
        return NULL;
    }

    if (block->size >= size) {
        return ptr;
    }

    void* new_ptr = custom_malloc(size);

    if (new_ptr) {
        memcpy(new_ptr, ptr, block->size);
        custom_free(ptr);
    }

    return new_ptr;

}


// Print all of the existing memory_blocks (for debug mainly)
void print_memory_blocks() {

    printf("====== MEMORY BLOCKS =========\n");   
    mem_block_t* current = first_block;

    while (current) {
        printf("Block at %p:\n", (void*)current);
        printf("-- Size: %zu bytes\n", current->size);
        printf("-- %s\n", current->is_free ? "FREE" : "ALLOCATED");

        if (current->next) {
            printf("-- Next Block: %p\n", (void*)current->next);
        } else {
            printf("-- Next Block: NULL\n");
        }

        current = current->next;
        printf("\n");
    }
}

// Several functions for testing the functions that we created
void test_custom_malloc() {
    // Test 1: Allocate memory for an integer
    int *ptr1 = custom_malloc(sizeof(int));
    assert(ptr1 != NULL);

    // Test 2: Allocate memory for an array of integers
    int *ptr2 = custom_malloc(sizeof(int) * 5);
    assert(ptr2 != NULL);

    // Free the allocated memory
    custom_free(ptr1);
    custom_free(ptr2);

    printf("All custom_malloc tests passed!\n");
}

void test_custom_free() {
    // Test 1: Free a NULL pointer (should not cause issues)
    custom_free(NULL);

    // Test 2: Allocate and free memory for a single integer
    int *ptr1 = custom_malloc(sizeof(int));
    assert(ptr1 != NULL);
    custom_free(ptr1);

    // Test 3: Allocate and free memory for an array of doubles
    double *ptr2 = custom_malloc(sizeof(double) * 5);
    assert(ptr2 != NULL);
    custom_free(ptr2);

    printf("All custom_free tests passed!\n");
}

void test_custom_realloc() {
    // Test 1: Reallocate a NULL pointer
    int *ptr1 = custom_realloc(NULL, sizeof(int));
    assert(ptr1 != NULL);
    custom_free(ptr1);

    // Test 2: Reallocate memory for an integer to a larger size
    int *ptr2 = custom_malloc(sizeof(int));
    assert(ptr2 != NULL);
    int *ptr2_realloc = custom_realloc(ptr2, sizeof(int)*5);
    assert(ptr2_realloc != NULL);
    custom_free(ptr2_realloc);

    printf("All custom_realloc tests passed!\n");
}

void test_custom_calloc() {
    // Test 1: Allocate and initialize memory for an array of integers
    int *ptr1 = custom_calloc(5, sizeof(int));
    assert(ptr1 != NULL);
    for (int i = 0; i < 5; ++i) {
        assert(ptr1[i] == 0);
    }
    custom_free(ptr1);

    // Test 2: Allocate and initialize memory for an array of doubles
    double *ptr2 = custom_calloc(3, sizeof(double));
    assert(ptr2 != NULL);
    for (int i = 0; i < 3; ++i) {
        assert(ptr2[i] == 0.0);
    }
    custom_free(ptr2);

    printf("All custom_calloc tests passed!\n");
}

int main() {

    // // Taille initiale de la chaîne
    // size_t initialSize = 10;


    // char *dynamicString = (char*)custom_malloc(initialSize * sizeof(char));

    // if (dynamicString == NULL) {
    //     printf("Allocation failed\n");
    //     return 1;
    // }

    // printf("Type characters and end it with a dot:\n");

    // char userInput;
    // size_t inputLength = 0;

    // while (1) {
    //     scanf(" %c", &userInput);

    //     if (userInput == '.') {
    //         break;
    //     }

    //     if (inputLength == initialSize - 1) {
    //         initialSize = 2;
    //         dynamicString = (char*)custom_realloc(dynamicString, initialSize * sizeof(char));

    //         if (dynamicString == NULL) {
    //             printf("Allocation failed.\n");
    //             return 1;
    //         } else {
    //             printf("Allocation done ! \n");
    //         }
    //     }

    //     dynamicString[inputLength] = userInput;
    //     inputLength++;
    // }

    // dynamicString[inputLength] = '\0';

    // int* other_ptr = custom_malloc(1024);
    // int* other_ptzr = custom_malloc(36);

    // print_memory_blocks();
    // custom_free(dynamicString);
    // custom_free(other_ptr);
    // custom_free(other_ptzr);
    // // int* new_size = custom_malloc(4);

    // // other_ptzr = custom_realloc(other_ptr, (size_t) 100);

    // print_memory_blocks();



    // // custom_free(dynamicString);

    // Run the multiple tests
    test_custom_malloc();
    test_custom_free();
    test_custom_realloc();
    test_custom_calloc();
    
    return 0;

}