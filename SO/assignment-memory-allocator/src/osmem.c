// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stddef.h>

#include "osmem.h"
#include "block_meta.h"

#define MMAP_THRESHOLD 131072
#define PAGE_SIZE 4096
#define ALIGNMENT 8
#define MALLOC 1
#define CALLOC 0

typedef struct block_meta mem_block;

static mem_block *mem_head;

const unsigned int FLAGS = MAP_ANONYMOUS | MAP_PRIVATE;
const unsigned int PROT = PROT_READ | PROT_WRITE;
const int MEM_BLOCK_SIZE = sizeof(mem_block);

size_t get_align_size(size_t size)
{
	if (size % ALIGNMENT)
		return ((size / ALIGNMENT) + 1) * ALIGNMENT;
	return size;
}

mem_block *coalesce_mem_chunks(void)
{
	mem_block *curr, *prev;
	int isChecked = 0; // checks if there are no two free adjacents blocks

	while (!isChecked) {
		isChecked = 1; // assuming that everything is ok now

		curr = mem_head;
		prev = NULL;

		while (curr) {
			if (curr->status == STATUS_FREE && curr->next && curr->next->status == STATUS_FREE) {
				curr->size += curr->next->size;
				curr->next = curr->next->next;
				isChecked = 0; // I have to check again for free adjacents blocks
			}

			prev = curr;
			curr = curr->next;
		}
	}

	return prev; // I need the last node
}

mem_block *request_space(size_t size, const short scope)
{
	mem_block *req;

	if (scope == 1) { // malloc
		if (size < MMAP_THRESHOLD) { // sbrk
			req = (mem_block *) sbrk(0);
			req = (mem_block *) sbrk(size);

			if (req == (void *)-1) {
				errno = ENOMEM;
				return NULL;
			}

			req->status = STATUS_ALLOC;

		} else { // mmap
			req = mmap(NULL, size, PROT, FLAGS, -1, 0);

			if (req == MAP_FAILED) {
				errno = ENOMEM;
				return MAP_FAILED;
			}

			req->status = STATUS_MAPPED;
		}

		// last req data to add
		req->size = size;
		req->next = NULL;

		return req;
	}

	if (scope) { // checks if the function is used for either malloc or calloc
		errno = ENOMEM; // if scope isn't 1 or 0, something is wrong
		return NULL;
	}

	// calloc
	if (size < PAGE_SIZE) {
		req = (mem_block *) sbrk(0);
		req = (mem_block *) sbrk(size);

		if (req == (void *)-1) {
			errno = ENOMEM;
			return NULL;
		}

		req->status = STATUS_ALLOC;
	} else {
		req = mmap(NULL, size, PROT, FLAGS, -1, 0);

		if (req == MAP_FAILED) {
			errno = ENOMEM;
			return NULL;
		}

		req->status = STATUS_MAPPED;
	}

	// last req data to add
	req->size = size;
	req->next = NULL;

	return req;
}

void split_mem_chunk(mem_block *mem_chunk, size_t size)
{
	if (size > mem_chunk->size) // nothing to do if I can't split
		return;

	mem_block *new = (mem_block *)((char *)mem_chunk + size);

	new->size = mem_chunk->size - size;
	mem_chunk->size = size;

	new->status = STATUS_FREE;

	new->next = mem_chunk->next;
	mem_chunk->next = new;
}

mem_block *find_free_mem_chunk(size_t size)
{
	mem_block *p = mem_head, *q = NULL;

	while (p) {
		if (p->status == STATUS_FREE && p->size >= size) { // found free chunk
			if (!q)
				q = p; // if it is first, remember it
			else if (q->size > p->size)
				q = p; // better choice
		}
		p = p->next;
	}

	return q;
}

mem_block *get_mem_end_chunk(void) // get last node of memory list
{
	mem_block *p = mem_head;

	while (p->next)
		p = p->next;

	return p;
}

void heap_preallocate(void)
{
	mem_head = (mem_block *) sbrk(0);
	mem_head = (mem_block *) sbrk(MMAP_THRESHOLD);

	if (mem_head == (void *)-1) {
		errno = ENOMEM;
		return;
	}

	mem_head->next = NULL;
	mem_head->prev = NULL;

	mem_head->status = STATUS_FREE;
	mem_head->size = MMAP_THRESHOLD;
}

void *alloc_chunk(size_t size, const short scope)
{
	mem_block *mem_chunk, *mem_end;

	if (scope == MALLOC && !mem_head && size < MMAP_THRESHOLD)
		heap_preallocate();

	if (scope == CALLOC && !mem_head && size < PAGE_SIZE)
		heap_preallocate();

	mem_end = coalesce_mem_chunks();
	mem_chunk = find_free_mem_chunk(size);

	if (!mem_chunk) { // no free block big enough to use
		if (mem_end && mem_end->status == STATUS_FREE) { // the last block can be extended
			mem_chunk = request_space(size - mem_end->size, scope);

			// no memory allocated
			if (!mem_chunk) {
				errno = ENOMEM;
				return NULL;
			}

			mem_end->size += mem_chunk->size; // size changed for last node
			mem_chunk = mem_end;

			if (mem_chunk->size >= get_align_size(1 + MEM_BLOCK_SIZE) + size)
				split_mem_chunk(mem_chunk, size); // block is too big to not split

			mem_chunk->status = STATUS_ALLOC;

			if (scope == CALLOC) // set everything to 0
				memset((void *)(mem_chunk + 1), 0, size - MEM_BLOCK_SIZE);

			return (void *)(mem_chunk + 1);
		}

		// we can't expand the last block
		mem_chunk = request_space(size, scope);

		if (!mem_chunk) {
			errno = ENOMEM;
			return NULL;
		}

		// mapped blocks shouldn't be used in the linked list
		if (mem_chunk->status == STATUS_MAPPED) {
			if (scope == CALLOC) // set everything to 0
				memset((void *)(mem_chunk + 1), 0, size - MEM_BLOCK_SIZE);

			return (void *)(mem_chunk + 1);
		}

		mem_end->next = mem_chunk;

		if (mem_end->status == STATUS_FREE) { // coalescing last two blocks if one is free
			mem_end->size += mem_chunk->size;
			mem_end->next = mem_chunk->next;
		}

		if (scope == CALLOC) // set everything to 0
			memset((void *)(mem_chunk + 1), 0, size - MEM_BLOCK_SIZE);

		return (void *)(mem_chunk + 1);
	}

	if (mem_chunk->size >= get_align_size(1 + MEM_BLOCK_SIZE) + size)
		split_mem_chunk(mem_chunk, size);

	mem_chunk->status = STATUS_ALLOC;
	if (scope == CALLOC) // set everything to 0
		memset((void *)(mem_chunk + 1), 0, size - MEM_BLOCK_SIZE);

	return (void *)(mem_chunk + 1);
}

mem_block *realloc_expand(mem_block *mem_chunk, size_t size)
{
	mem_block *p = mem_chunk->next;

	while (p && p->status == STATUS_FREE) {
		mem_chunk->size += p->size;
		mem_chunk->next = p->next;
		p = mem_chunk->next;
	}

	return (mem_chunk->size >= size ? mem_chunk : NULL);
}

void *os_malloc(size_t size)
{
	if (size <= 0) { // check if argument is valid
		errno = ENOMEM;
		return NULL;
	}

	size = get_align_size(size + MEM_BLOCK_SIZE);

	return alloc_chunk(size, MALLOC);
}

void os_free(void *ptr)
{
	if (!ptr)
		return;

	mem_block *p = (mem_block *)(ptr - MEM_BLOCK_SIZE);

	if (p->status == STATUS_MAPPED) {
		munmap(p, p->size);
		return;
	}

	// the memory should be reused
	p->status = STATUS_FREE;
}

void *os_calloc(size_t nmemb, size_t size)
{
	if (nmemb * size == 0) { // invalid arg/s
		errno = ENOMEM;
		return NULL;
	}

	size = get_align_size(MEM_BLOCK_SIZE + size * nmemb);

	return alloc_chunk(size, CALLOC);
}

void *os_realloc(void *ptr, size_t size)
{
	size_t align_size = get_align_size(size + MEM_BLOCK_SIZE);

	if (!ptr)
		return os_malloc(size);

	if (!size) {
		os_free(ptr);
		return NULL;
	}

	mem_block *p = (mem_block *)((char *)ptr - MEM_BLOCK_SIZE);

	if (p->status == STATUS_FREE) // nothing to do it is already free
		return NULL;

	if (p->size == get_align_size(size)) // nothing to do if the size is the same
		return ptr;

	if (p->status == STATUS_MAPPED) {
		mem_block *new = (mem_block *)((char *)os_malloc(size) - MEM_BLOCK_SIZE);

		if (!new) {
			errno = ENOMEM;
			return NULL;
		}

		memcpy((void *)(new + 1), ptr, new->size - MEM_BLOCK_SIZE);
		os_free(ptr);

		return (void *)(new + 1);
	}

	if (p->size >= get_align_size(1 + MEM_BLOCK_SIZE) + align_size) {
		split_mem_chunk(p, align_size);
		return ptr;
	}

	if (size >= MMAP_THRESHOLD) {
		mem_block *new = (mem_block *)((char *)os_malloc(size) - MEM_BLOCK_SIZE);

		if (!new) {
			errno = ENOMEM;
			return NULL;
		}

		memcpy((void *)(new + 1), ptr, p->size);
		os_free(ptr);

		return (void *)(new + 1);
	}

	coalesce_mem_chunks();

	p = realloc_expand(p, align_size);

	if (!p) { // can't expand so request more space
		void *q = os_malloc(size);
		mem_block *new = (mem_block *) ((char *)q - MEM_BLOCK_SIZE);

		if (!q) {
			errno = ENOMEM;
			return NULL;
		}

		memcpy(q, ptr, new->size - MEM_BLOCK_SIZE);
		os_free(ptr);

		return q;
	}

	// the chunk could be expanded
	if (p->size >= get_align_size(1 + MEM_BLOCK_SIZE) + align_size)
		split_mem_chunk(p, align_size);

	return ptr;
}
