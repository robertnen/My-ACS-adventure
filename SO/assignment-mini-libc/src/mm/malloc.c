// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

const int ALLOC_SIZE = sizeof(size_t); // the first 4 bytes of the allocated adress represents the size

void *malloc(size_t size) {
	void *mem = mmap(NULL, size + ALLOC_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (mem == MAP_FAILED) return NULL; // couldn't find a memory region

    *((size_t *)mem) = size; // add to the first 4 bytes the size of the allocated memory

    return (char *)mem + ALLOC_SIZE; // returning the allocated memory, not the size
}

void *calloc(size_t nmemb, size_t size) {
	void *mem = mmap(NULL, nmemb * size + ALLOC_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (mem == MAP_FAILED) return NULL; // couldn't find a memory region

    *((size_t *)mem) = size; // add to the first 4 bytes the size of the allocated memory

    memset((char *)mem + ALLOC_SIZE, 0, nmemb * size); // set everything to 0

    return (char *)mem + ALLOC_SIZE; // return the allocated memory, not the size
}

void free(void *ptr) {
    if (!ptr) return;

    size_t size = *(size_t *)((char *)ptr - ALLOC_SIZE); // first 4 bytes

    munmap((char *)ptr - ALLOC_SIZE, size + ALLOC_SIZE); // release memory for the entire region
}

void *realloc(void *ptr, size_t size) {
    void *new = malloc(size); // new memory region

    if (new == NULL) return NULL; // it didn't work

    int oldSize = munmap(ptr, 0); // unmap

    if (oldSize >= (int)size) return ptr; // I can't copy sth bigger into sth smaller

    *((size_t *)new) = size; // add to the first 4 bytes the size of the allocated memory

    memcpy((char *)new + ALLOC_SIZE, (char *)ptr + ALLOC_SIZE, size); // copy old data

    free(ptr);
    return (char *)new + ALLOC_SIZE;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size) {
    void *new = malloc(nmemb * size); // new memory region

    if (new == NULL) return NULL; // it didn't work

    int oldSize = munmap(ptr, 0); // unmap

    if ((int)oldSize >= (int)(nmemb * size)) return ptr; // I can't copy sth bigger into sth smaller

    *((size_t *)new) = size; // add to the first 4 bytes the size of the allocated memory

    memcpy((char *)new + ALLOC_SIZE, (char *)ptr + ALLOC_SIZE, nmemb * size); // copy old data

    free(ptr);

    return (char *)new + ALLOC_SIZE; // return the allocated memory, not the size
}
