#include "virtual_memory.h"

#define phys_addr_mask 0x

void init_vmm(vmem_handle_t*vmm,void*pml4_page)
{
vmm->pml4=(page_table_t*)pml4_page;


}

void vmem_map_page(vmem_handle_t*vmem,void*phys_addr,void*virt_addr,UINT32 flags)
{




}
