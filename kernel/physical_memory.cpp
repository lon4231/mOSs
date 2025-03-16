#include "physical_memory.h"

void*get_indexed_usable_page(mmap_t*mmap,UINTN index)
{
UINTN current_index=0;
for(UINTN i=0;i<mmap->size/mmap->desc_size;++i)
{
mmap_mem_desc_t*desc=(mmap_mem_desc_t*)((UINT8*)mmap->map+(i*mmap->desc_size));
if(desc->Type!=7){continue;}
for(UINTN n=0;n<desc->NumberOfPages;++n)
{
if(current_index==index)
{return(void*)(desc->PhysicalStart+(n*PAGE_SIZE));}
current_index++;
}
}
return NULL;
}

void init_phys_mem(phys_mem_handle_t*phys_mem,mmap_t*mmap)
{
phys_mem->mmap=mmap;
phys_mem->usable_pages=0;
phys_mem->reserved_pages=0;

for(UINTN i=0;i<mmap->size/mmap->desc_size;++i)
{
mmap_mem_desc_t*desc=(mmap_mem_desc_t*)((UINT8*)mmap->map+(i*mmap->desc_size));
if(desc->Type==7)
{phys_mem->usable_pages+=desc->NumberOfPages;}
}

}

void*phys_mem_reserve_page(phys_mem_handle_t*phys_mem)
{
if(phys_mem->reserved_pages>=phys_mem->usable_pages)
{return nullptr;}
return get_indexed_usable_page(phys_mem->mmap,phys_mem->reserved_pages++);
}