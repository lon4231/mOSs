#pragma once

#include "mstdi.h"
#include "arch.h"
#include "cpu.h"

UINTN get_mmap_usable_pages(MEMORY_MAP_INFO*mmap) 
{
UINTN pages=0;
for(UINTN i=0;i<mmap->size/mmap->desc_size;++i)
{
MEMORY_DESCRIPTOR_T*desc=(MEMORY_DESCRIPTOR_T*)((UINT8*)mmap->map+(i*mmap->desc_size));
if(desc->Type==MTConventionalMemory)
{pages+=desc->NumberOfPages;}
}
return pages;
}

void*get_mmap_usable_page(MEMORY_MAP_INFO*mmap,UINTN page_index)
{
UINTN current_index=0;
for(UINTN i=0;i<mmap->size/mmap->desc_size;++i)
{
MEMORY_DESCRIPTOR_T*desc=(MEMORY_DESCRIPTOR_T*)((UINT8*)mmap->map+(i*mmap->desc_size));
if(desc->Type!=MTConventionalMemory){continue;}
for(UINTN n=0;n<desc->NumberOfPages;++n)
{
if(current_index==page_index)
{return(void*)(desc->PhysicalStart+(n*PAGE_SIZE));}
current_index++;
}
}
return NULL;
}

UINTN get_page_index_from_address(MEMORY_MAP_INFO*mmap,void*address)
{
UINTN current_index=0;
for (UINTN i=0;i<mmap->size/mmap->desc_size;++i)
{
MEMORY_DESCRIPTOR_T*desc=(MEMORY_DESCRIPTOR_T*)((UINT8*)mmap->map+(i*mmap->desc_size));
if(desc->Type!=MTConventionalMemory)
{ continue;}
for (UINTN n=0;n<desc->NumberOfPages;++n)
{
void*page_start=(void*)(desc->PhysicalStart+(n*PAGE_SIZE));
void*page_end=(void*)((UINT8*)page_start+PAGE_SIZE);
if (address>=page_start&&address<page_end)
{return current_index+n;}
}
current_index+=desc->NumberOfPages;
}
return (UINTN)-1;
}


inline bool mmap_bitmap_get_page(alloc_context_t*alloc_context,UINTN index)
{
return (alloc_context->bitmap[index/8]>>(index%8))&1;
}

inline void mmap_bitmap_set_page(alloc_context_t*alloc_context,UINTN index,bool set)
{
if(set) 
{alloc_context->bitmap[index/8]|=(1<<(index%8));} 
else 
{alloc_context->bitmap[index/8]&=~(1<<(index%8));}
}

void mmap_allocate_init(alloc_context_t*alloc_context,MEMORY_MAP_INFO*mmap)
{
alloc_context->mmap=mmap;
alloc_context->total_pages=get_mmap_usable_pages(mmap);

alloc_context->bitmap=(UINT8*)get_mmap_usable_page(mmap,0);

memset(alloc_context->bitmap,0,(alloc_context->total_pages+7)/8);

for(UINTN i=0;i<SIZE_TO_PAGES(alloc_context->total_pages/8);++i)
{
mmap_bitmap_set_page(alloc_context,i,true);
}

}

void*mmap_allocate_pages(alloc_context_t*alloc_context,UINTN pages)
{
UINTN allocated_pages=0;
UINTN start_page_index=0;
for(UINTN i=0;i<alloc_context->total_pages;++i)
{
if(!mmap_bitmap_get_page(alloc_context,i))
{
if(allocated_pages==0)
{start_page_index=i;}
mmap_bitmap_set_page(alloc_context,i,true);
++allocated_pages;
if (allocated_pages==pages)
{void*address=get_mmap_usable_page(alloc_context->mmap,start_page_index);return address;}
}
}
return nullptr;
}

void mmap_free_pages(alloc_context_t*alloc_context,void*address,UINTN pages)
{
UINTN start_page_index=get_page_index_from_address(alloc_context->mmap,address);
for(UINTN i=0;i<pages;++i)
{
UINTN page_index=start_page_index+i;
mmap_bitmap_set_page(alloc_context,page_index,false);
}
}
