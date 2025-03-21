#include "physical_memory.h"
#include "std_string.h"
#include "printf.h"

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
                freelist_node_t *new_node = (freelist_node_t *)(((UINT8 *)desc->PhysicalStart) + (n * PAGE_SIZE));
                freelist_add_page(pmm, new_node);
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

void pmm_free_page(pmm_handle_t *pmm, void *page)
{
    freelist_node_t *new_node = (freelist_node_t *)page;

    new_node->next = pmm->head;

    pmm->head = new_node;
}
