#pragma once

#include "std_types.h"
#include "std_string.h"
#include "mmap.h"

struct bump_handle_t
{
mmap_t*mmap;
void*  next_page;
UINTN  current_desc;
UINTN  remaining;
};

struct bitmap_chunk_t
{
UINT8 bitmap_section[PAGE_SIZE-sizeof(bitmap_chunk_t*)];
bitmap_chunk_t*next;
};

struct bitmap_handle_t
{
bitmap_chunk_t first_chunk;
};

struct pmm_t
{
bump_handle_t bump_handle;
bitmap_handle_t bitmap_handle;
};

void init_bump_alloc(bump_handle_t*handle,mmap_t*mmap)
{
handle->mmap=mmap;
for(UINTN i=0;i<(mmap->size/mmap->desc_size);++i)
{
mmap_mem_desc_t*desc=(mmap_mem_desc_t*)(((UINT8*)mmap->map)+i*mmap->desc_size);
if(desc->Type==7)
{
handle->current_desc=i;
handle->next_page=(void*)desc->PhysicalStart;
handle->remaining=desc->NumberOfPages;
break;
}
}
}

void*bump_allocate_pages(pmm_t*pmm,UINTN pages)
{
if(pages<pmm->bump_handle.remaining)
{
void*returned_pages=pmm->bump_handle.next_page;
pmm->bump_handle.remaining-=pages;
pmm->bump_handle.next_page+=pages*PAGE_SIZE;
return returned_pages;
}
if(pages==pmm->bump_handle.remaining)
{
void*returned_pages=pmm->bump_handle.next_page;
for(UINTN i=pmm->bump_handle.current_desc+1;i<(pmm->bump_handle.mmap->size/pmm->bump_handle.mmap->desc_size);++i)
{
mmap_mem_desc_t*desc=(mmap_mem_desc_t*)(((UINT8*)pmm->bump_handle.mmap->map)+i*pmm->bump_handle.mmap->desc_size);
if(desc->Type==7)
{
pmm->bump_handle.current_desc=i;
pmm->bump_handle.next_page=(void*)desc->PhysicalStart;
pmm->bump_handle.remaining=desc->NumberOfPages;
break;
}
}
return returned_pages;
}
for(UINTN i=pmm->bump_handle.current_desc+1;i<(pmm->bump_handle.mmap->size/pmm->bump_handle.mmap->desc_size);++i)
{
mmap_mem_desc_t*desc=(mmap_mem_desc_t*)(((UINT8*)pmm->bump_handle.mmap->map)+i*pmm->bump_handle.mmap->desc_size);
if(desc->Type==7)
{
pmm->bump_handle.current_desc=i;
pmm->bump_handle.next_page=(void*)desc->PhysicalStart;
pmm->bump_handle.remaining=desc->NumberOfPages;
break;
}
}
return NULL;
}

void init_bitmap_allocator(bitmap_handle_t*bitmap,bump_handle_t*handle)
{
mmap_t*mmap=handle->mmap;
UINTN total_pages=0;

for(UINTN i=0;i<(mmap->size/mmap->desc_size);++i)
{
mmap_mem_desc_t*desc=(mmap_mem_desc_t*)(((UINT8*)mmap->map)+(i*mmap->desc_size));
if(desc->Type==7)
{total_pages+=desc->NumberOfPages;}
}




}


void init_pmm(pmm_t*pmm,mmap_t*mmap)
{
init_bump_alloc(&pmm->bump_handle,mmap);
}