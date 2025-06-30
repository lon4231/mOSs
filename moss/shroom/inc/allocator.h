#ifndef _SHROOM_PHYS_ALLOCATOR_
#define _SHROOM_PHYS_ALLOCATOR_

#include <efi.h>

struct alloc_node_t
{
    alloc_node_t *next;
};

struct alloc_handle_t
{
    memory_map_info_t mmap;
    alloc_node_t *head;
};

void init_allocator(alloc_handle_t *handle);

void *alloc_page(alloc_handle_t *handle);
void free_page(alloc_handle_t *handle, void *page);

#endif