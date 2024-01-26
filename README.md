# Custom malloc function
This school project aims to implement our own malloc, free, realloc and calloc functions in C, using the [sbrk(2)](https://linux.die.net/man/2/sbrk) and [brk(2)](https://linux.die.net/man/2/brk) system calls. It is a simplified version of the basic stdlib functions used in a program to manage and allocate dynamic memory on the heap. 

## Requirements
To run this code, you will need a C compiler, we will use [GCC](). It is usually pre-installed on most Linux distributions, but can be installed with :
```bash
sudo apt-get install gcc 
```

## Quick start
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
<!-- Add test files to run and instructions to use the function wherever we need -->

## Functions wiki

`void *malloc(size_t size)`<br>Allocates memory on the heap of the given size in bytes<br>
`void free(void *ptr)`<br>
`void *calloc(size_t nmemb, size_t size)`<br>
`void *realloc(void *ptr, size_t size)`<br>