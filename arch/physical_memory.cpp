#include "physical_memory.h"

void *get_indexed_usable_page(mmap_t *mmap, UINTN index)
{
    UINTN current_index = 0;
    for (UINTN i = 0; i < mmap->size / mmap->desc_size; ++i)
    {
        mmap_mem_desc_t *desc = (mmap_mem_desc_t *)((UINT8 *)mmap->map + (i * mmap->desc_size));
        if (desc->Type != 7)
        {
            continue;
        }
        for (UINTN n = 0; n < desc->NumberOfPages; ++n)
        {
            if (current_index == index)
            {
                return (void *)(desc->PhysicalStart + (n * PAGE_SIZE));
            }
            current_index++;
        }
    }
    return nullptr;
}

void freelist_add_page(pmm_handle_t *pmm, freelist_node_t *new_node)
{
    new_node->next = pmm->head;
    pmm->head = new_node;
}

void init_pmm(pmm_handle_t *pmm, mmap_t *mmap)
{
    pmm->mmap = mmap;
    pmm->total_pages = 0;
    pmm->head = nullptr;

    for (UINTN i = 0; i < (mmap->size / mmap->desc_size); ++i)
    {
        mmap_mem_desc_t *desc = (mmap_mem_desc_t *)(((UINT8 *)mmap->map) + (i * mmap->desc_size));
        if (desc->Type == 7)
        {
            pmm->total_pages += desc->NumberOfPages;

            for (UINTN n = 0; n < desc->NumberOfPages; ++n)
            {
                freelist_add_page(pmm, (freelist_node_t *)(desc->PhysicalStart + (n * PAGE_SIZE)));
            }
        }
    }
}

void *pmm_request_page(pmm_handle_t *pmm)
{
    void *page = (void *)pmm->head;

    pmm->head = pmm->head->next;

    return page;
}

void pmm_free_page(pmm_handle_t*pmm,void*page)
{
freelist_node_t*new_node=(freelist_node_t*)page;

new_node->next=pmm->head;

pmm->head=new_node;


}
