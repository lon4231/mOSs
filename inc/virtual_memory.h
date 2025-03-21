#pragma once

#include "std_types.h"
#include "physical_memory.h"

#define HIGHER_HALF_START_ADDRESS 0xFFFFFFFF80000000

enum PAGE_TABLE_FLAGS
{
    PAGE_TABLE_FLAGS_PRESENT = 1,
    PAGE_TABLE_FLAGS_RW = 2,
    PAGE_TABLE_FLAGS_USER = 4,
};

struct page_table_entry_t
{
    UINT64 value;
} __attribute__((packed));

struct page_table_t
{
    page_table_entry_t entries[512];
} __attribute__((packed));

struct vmm_handle_t
{
    pmm_handle_t *pmm;
    page_table_t *pml4;
    UINTN higher_half_index;
};

void init_vmm(vmm_handle_t *vmm, pmm_handle_t *pmm);

void vmm_map_page(vmm_handle_t *vmm, void *phys_addr, void *virt_addr, UINT32 flags);

void vmm_map_pages(vmm_handle_t *vmm, void *phys_addr, void *virt_addr, UINT32 flags, UINTN pages);

void *vmm_map_higher_half(vmm_handle_t *vmm, void *phys_addr, UINT32 flags, UINTN pages);

void *virt_to_phys_addr(vmm_handle_t *vmm, void *phys_addr, void *virt_addr);
