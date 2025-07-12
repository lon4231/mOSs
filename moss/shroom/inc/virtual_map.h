#ifndef _SHROOM_VIRTUAL_MEMORY_MAP_
#define _SHROOM_VIRTUAL_MEMORY_MAP_

#include <allocator.h>
#include <cstr.h>
#include <arch.h>

struct vmem_table_t
{
page_table_t*pml4;
alloc_handle_t*allocator;


};

void init_vmem_table(vmem_table_t*vmm,alloc_handle_t*allocator);

void*map_page(vmem_table_t*vmm,void*phys_addr,void*virt_addr,uint16_t flags);

#endif