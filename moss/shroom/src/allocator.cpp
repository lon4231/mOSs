#include <efi_globals.h>
#include <allocator.h>
#include <cstr.h>
#include <arch.h>

void init_allocator(alloc_handle_t *handle)
{

    for (size_t i = 0; i < handle->mmap.entry_count; ++i)
    {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)(((uint8_t *)handle->mmap.map) + (i * handle->mmap.desc_size));

        if ((desc->Type == EfiConventionalMemory) || (desc->Type == EfiRuntimeServicesCode) || (desc->Type == EfiRuntimeServicesData))
        {
            for (size_t n = 0; n < desc->NumberOfPages; ++n)
            {
                alloc_node_t *node = (alloc_node_t *)(desc->PhysicalStart + (n * PAGE_SIZE));

                memset(node,0,PAGE_SIZE);

                node->next = handle->head;
                handle->head = node;
            }
        }
    }
}

void *alloc_page(alloc_handle_t *handle)
{
    void *page = handle->head;
    handle->head = handle->head->next;
    return page;
}

void free_page(alloc_handle_t *handle, void *page)
{
    ((alloc_node_t *)page)->next = handle->head;
    handle->head = ((alloc_node_t *)page);
}
