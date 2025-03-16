#include "virtual_memory.h"
#include "std_string.h"

#define PHYS_ADDR_MASK 0x000FFFFFFFFFF000

void init_vmm(vmm_handle_t*vmm,void*pml4_page)
{
vmm->pml4=(page_table_t*)pml4_page;
memset(vmm->pml4,0,sizeof(page_table_t));

}

void vmm_map_page(vmm_handle_t*vmem,void*phys_addr,void*virt_addr,UINT32 flags)
{

UINT64 pml4_index=(((UINT64)virt_addr)>>39)&0x1FF;
UINT64 pdpt_index=(((UINT64)virt_addr)>>30)&0x1FF;
UINT64 pdt_index =(((UINT64)virt_addr)>>21)&0x1FF;
UINT64 pt_index  =(((UINT64)virt_addr)>>12)&0x1FF;

if(!(vmem->pml4->entries[pml4_index].value&PAGE_TABLE_FLAGS_PRESENT))
{
void*pdpt_page=nullptr;

if(vmem->request_page!=nullptr)
{
pdpt_page=vmem->request_page();
memset(pdpt_page,0,sizeof(page_table_t));
vmem->pml4->entries[pml4_index].value=(UINT64)pdpt_page | flags;
}

}

page_table_t*pdpt=(page_table_t*)(vmem->pml4->entries[pml4_index].value&PHYS_ADDR_MASK);
if(!(pdpt->entries[pdpt_index].value&PAGE_TABLE_FLAGS_PRESENT))
{
void*pdt_page=nullptr;
if(vmem->request_page!=nullptr)
{
pdt_page=vmem->request_page();
memset(pdt_page,0,sizeof(page_table_t));
pdpt->entries[pdpt_index].value=(UINT64)pdt_page|flags;
}
}

page_table_t*pdt=(page_table_t*)(pdpt->entries[pdpt_index].value&PHYS_ADDR_MASK);
if(!(pdt->entries[pdt_index].value&PAGE_TABLE_FLAGS_PRESENT))
{
void*pt_page=nullptr;
if(vmem->request_page!=nullptr)
{
pt_page=vmem->request_page();
memset(pt_page,0,sizeof(page_table_t));
pdt->entries[pdt_index].value=(UINT64)pt_page|flags;
}
}

page_table_t*pt=(page_table_t*)(pdt->entries[pdt_index].value&PHYS_ADDR_MASK);
pt->entries[pt_index].value=((UINT64)phys_addr&PHYS_ADDR_MASK)|flags;

}


void vmm_map_pages(vmm_handle_t*vmem,void*phys_addr,void*virt_addr,UINT32 flags,UINTN pages)
{
for(UINTN i=0;i<pages;++i)
{
vmm_map_page(vmem,((UINT8*)phys_addr)+(i*PAGE_SIZE),((UINT8*)virt_addr)+(i*PAGE_SIZE),flags);
}
}