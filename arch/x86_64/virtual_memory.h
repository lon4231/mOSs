#pragma once

#include "std_dtypes.h"
#include "std_string.h"
#include "arch.h"
#include "allocator.h"

#define PAGE_ADDRESS_MASK 0x000FFFFFFFFFF000

enum PAGE_FLAGS
{
    PAGE_FLAGS_PRESENT = 1,
    PAGE_FLAGS_READWRITE = 2,
    PAGE_FLAGS_USER = 4,
    PAGE_FLAGS_ALL = 7,
};

struct page_table_t
{
    UINTN entries[512];
};

struct vmem_context_t
{
    alloc_context_t *allocator_context;
    page_table_t *pml4;
};

void vmem_init_vmem(vmem_context_t *context, alloc_context_t *alloc)
{
    context->allocator_context = alloc;
    context->pml4 = (page_table_t *)mmap_allocate_pages(context->allocator_context, 1);
    memset(context->pml4, 0, sizeof(page_table_t));
}

void vmem_map_page(vmem_context_t *context, void *physical_addr, void *virtual_addr, UINT8 flags)
{
    UINTN v_addr = (UINTN)virtual_addr;
    UINTN p_addr = (UINTN)physical_addr;

    UINTN pml4_index = ((v_addr) >> 39) & 0x1FF;
    UINTN pdpt_index = ((v_addr) >> 30) & 0x1FF;
    UINTN pdt_index = ((v_addr) >> 21) & 0x1FF;
    UINTN pt_index = ((v_addr) >> 12) & 0x1FF;

    if (!(context->pml4->entries[pml4_index] & PAGE_FLAGS_PRESENT))
    {
        void *pdpt_addr = mmap_allocate_pages(context->allocator_context, 1);
        memset(pdpt_addr, 0, sizeof(page_table_t));
        context->pml4->entries[pml4_index] = (UINTN)pdpt_addr | flags;
    }

    page_table_t *pdpt = (page_table_t *)context->pml4->entries[pml4_index];
    if (!(pdpt->entries[pml4_index] & PAGE_FLAGS_PRESENT))
    {
        void *pdt_addr = mmap_allocate_pages(context->allocator_context, 1);
        memset(pdt_addr, 0, sizeof(page_table_t));
        pdpt->entries[pdpt_index] = (UINTN)pdt_addr | flags;
    }

    page_table_t *pdt = (page_table_t *)pdpt->entries[pdpt_index];
    if (!(pdt->entries[pdt_index] & PAGE_FLAGS_PRESENT))
    {
        void *pt_addr = mmap_allocate_pages(context->allocator_context, 1);
        memset(pt_addr, 0, sizeof(page_table_t));
        pdt->entries[pdpt_index] = (UINTN)pt_addr | flags;
    }

    page_table_t *pt = (page_table_t *)pdt->entries[pdt_index];
    if (!(pt->entries[pt_index] & PAGE_FLAGS_PRESENT))
    {
        pt->entries[pt_index] = (p_addr & PAGE_ADDRESS_MASK) | flags;
    }
}

void arch_unmap_page(vmem_context_t *context, void *virtual_address)
{
    uint64_t pml4_index = (((UINTN)virtual_address) >> 39) & 0x1FF;
    uint64_t pdpt_index = (((UINTN)virtual_address) >> 30) & 0x1FF;
    uint64_t pdt_index = (((UINTN)virtual_address) >> 21) & 0x1FF;
    uint64_t pt_index = (((UINTN)virtual_address) >> 12) & 0x1FF;

    page_table_t *pdpt = (page_table_t *)(context->pml4->entries[pml4_index] & PAGE_ADDRESS_MASK);
    page_table_t *pdt = (page_table_t *)(pdpt->entries[pdpt_index] & PAGE_ADDRESS_MASK);
    page_table_t *pt = (page_table_t *)(pdt->entries[pdt_index] & PAGE_ADDRESS_MASK);

    pt->entries[pt_index] = 0;
    __asm__("invlpg (%0)\n" : : "r"(virtual_address));
}