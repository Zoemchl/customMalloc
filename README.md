# Custom malloc function
This school project aims to implement our own malloc, free, realloc and calloc functions in C, using the [sbrk(2)](https://linux.die.net/man/2/sbrk) and [brk(2)](https://linux.die.net/man/2/brk) system calls. It is a simplified version of the basic stdlib functions used in a program to manage and allocate dynamic memory on the heap. 

## Requirements
To run this code, you will need a C compiler, we will use [GCC](). It is usually pre-installed on most Linux distributions, but can be installed with :
```bash
sudo apt-get install gcc 
```


## Quick start

### Clone the repository

```bash
git clone git@github.com:Zoemchl/customMalloc_Auriane-Zo-.git
```

### Compile the code on Linux
In the root folder, run the following command:
```bash
gcc -o main main.c
```

### Run the compiled code
Then simply run:
```bash
./main
```

## Functions wiki

`void *malloc(size_t size)`<br>Allocates memory on the heap of the given size in bytes<br>
`void free(void *ptr)`<br>Frees memory previously allocated by malloc, calloc or realloc, by using the ptr argument returned by one of the memory allocation functions.<br>
`void *calloc(size_t nmemb, size_t size)`<br>Resizes a previously allocated block of memory, by using the ptr argument returned by one of the memory allocation functions and the desired new memory size.<br>
`void *realloc(void *ptr, size_t size)`<br>Allocates a block of memory for an array of num elements, each occupying size bytes.<br>

## Tests

By default, you'll find four functions running within main to test custom_malloc, custom_free, custom_realloc and custom_calloc.

```bash
int main() {
    // Run the multiple tests
    test_custom_malloc();
    test_custom_free();
    test_custom_realloc();
    test_custom_calloc();
    return 0;
}
```

## Authors
This repository was created by [Zoé Michel](https://github.com/Zoemchl) and [Auriane Le Perdriel](https://github.com/aleperdriel)
