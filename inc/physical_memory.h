#pragma once
#include "std_types.h"
#include "mmap.h"

struct freelist_node_t
{
freelist_node_t*next;
};

struct pmm_handle_t
{
    mmap_t *mmap;
    UINTN total_pages;
    freelist_node_t*head;
};

void init_pmm(pmm_handle_t *phys_mem, mmap_t *mmap);

void *get_indexed_usable_page(mmap_t *mmap, UINTN index);

void *pmm_request_page(pmm_handle_t*phys_mem);
void  free_page(pmm_handle_t*phys_mem);
