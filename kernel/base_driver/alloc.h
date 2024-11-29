#pragma once

#include "mstdi.h"
#include "globals.h"


void*mmap_allocate_pages(UINTN pages) 
{
if (alloc_context.remaining_pages<pages) 
{
UINTN i=alloc_context.current_descriptor+1;
for (;i<alloc_context.mmap->size/alloc_context.mmap->desc_size;++i) 
{
MEMORY_DESCRIPTOR_T*desc=(MEMORY_DESCRIPTOR_T*)((UINT8*)alloc_context.mmap->map+(i*alloc_context.mmap->desc_size));

if (desc->Type==MTConventionalMemory&&desc->NumberOfPages>=pages) 
{
alloc_context.current_descriptor=i;
alloc_context.remaining_pages=desc->NumberOfPages-pages;
alloc_context.next_page_address=(void*)(desc->PhysicalStart+(pages*PAGE_SIZE));
return (void*)desc->PhysicalStart;
}
}

if (i>=alloc_context.mmap->size/alloc_context.mmap->desc_size) 
{return nullptr;}
}

alloc_context.remaining_pages-=pages;
void*page=alloc_context.next_page_address;
alloc_context.next_page_address=(void*)((UINT8*)page+(pages*PAGE_SIZE));
return page;
}