#pragma once

#include "std_types.h"
#include "std_string.h"
#include "mmap.h"

struct bump_handle_t
{
mmap_t*mmap;
void*  current_address;
UINTN  desc;
UINTN  used_pages;
};

void init_bump_alloc(bump_handle_t*handle,mmap_t*mmap)
{
handle->mmap=mmap;
handle->used_pages=0;

for(UINTN i=0;i<(mmap->size/mmap->desc_size);++i)
{
mmap_mem_desc_t*desc=(mmap_mem_desc_t*)((UINT8*)mmap->map)+(i*mmap->desc_size);

if(desc->Type==7)
{
handle->desc=i;
break;
}


}


}