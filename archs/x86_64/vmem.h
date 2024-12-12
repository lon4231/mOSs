#pragma once

#include "mstdi.h"
#include "arch.h"

alloc_context_t*      vmem_alloc_context;
page_table_t*         vmem_pml4;
KERN_RUNTIME_SERVICES*vmem_ers;

void map_page(UINTN physical_address,UINTN virtual_address,MEMORY_MAP_INFO*mmap,int flags)
{

UINTN pml4_index=((virtual_address)>>39)&0x1FF;
UINTN pdpt_index=((virtual_address)>>30)&0x1FF;
UINTN pdt_index =((virtual_address)>>21)&0x1FF;
UINTN pt_index  =((virtual_address)>>12)&0x1FF;

if (!(vmem_pml4->entries[pml4_index]&PAGE_PRESENT))
{
void*pdpt_address=mmap_allocate_pages(vmem_alloc_context,1);
memset(pdpt_address,0,sizeof(page_table_t));
vmem_pml4->entries[pml4_index]=(UINTN)pdpt_address|flags;
}

page_table_t*pdpt=(page_table_t*)(vmem_pml4->entries[pml4_index]&PHYS_PAGE_ADDR_MASK);
if (!(pdpt->entries[pdpt_index]&PAGE_PRESENT))
{
void*pdt_address=mmap_allocate_pages(vmem_alloc_context,1);
memset(pdt_address,0,sizeof(page_table_t));
pdpt->entries[pdpt_index]=(UINTN)pdt_address|flags;
}

page_table_t*pdt=(page_table_t*)(pdpt->entries[pdpt_index]&PHYS_PAGE_ADDR_MASK);

if (!(pdt->entries[pdt_index]&PAGE_PRESENT))
{
void*pt_address=mmap_allocate_pages(vmem_alloc_context,1);
memset(pt_address,0,sizeof(page_table_t));
pdt->entries[pdt_index]=(UINTN)pt_address|flags;
}

page_table_t*pt=(page_table_t*)(pdt->entries[pdt_index]&PHYS_PAGE_ADDR_MASK);
if (!(pt->entries[pt_index]&PAGE_PRESENT))
pt->entries[pt_index]=(physical_address&PHYS_PAGE_ADDR_MASK)|flags;
}

void identity_map_page(UINTN address,MEMORY_MAP_INFO*mmap)
{
map_page(address,address,mmap,PAGE_PRESENT|PAGE_READWRITE|PAGE_USER);
}

void identity_map_efi_mmap(MEMORY_MAP_INFO*mmap)
{
for (UINTN i=0;i<mmap->size/mmap->desc_size;i++)
{
MEMORY_DESCRIPTOR_T*desc=(MEMORY_DESCRIPTOR_T*)((UINT8*)mmap->map+(i*mmap->desc_size));
for (UINTN j=0;j<desc->NumberOfPages;j++)
{identity_map_page(desc->PhysicalStart+(j*PAGE_SIZE),mmap);}
}
}

void set_runtime_address_map(MEMORY_MAP_INFO*mmap)
{
UINTN runtime_descriptors=0;
for (UINTN i=0; i < mmap->size / mmap->desc_size; i++)
{
MEMORY_DESCRIPTOR_T*desc=(MEMORY_DESCRIPTOR_T*)((UINT8*)mmap->map+(i*mmap->desc_size));
if (desc->Attribute & KERN_MEMORY_RUNTIME)
runtime_descriptors++;
}

UINTN runtime_mmap_pages=(runtime_descriptors*mmap->desc_size)+((PAGE_SIZE-1)/ PAGE_SIZE);
MEMORY_DESCRIPTOR_T*runtime_mmap =(MEMORY_DESCRIPTOR_T*)mmap_allocate_pages(vmem_alloc_context,runtime_mmap_pages);
if (!runtime_mmap)
{
return;
}

UINTN runtime_mmap_size=runtime_mmap_pages*PAGE_SIZE; 
memset(runtime_mmap,0,runtime_mmap_size);

UINTN curr_runtime_desc=0;
for (UINTN i=0; i < mmap->size / mmap->desc_size; i++)
{
MEMORY_DESCRIPTOR_T*desc=(MEMORY_DESCRIPTOR_T*)((UINT8*)mmap->map+(i*mmap->desc_size));
if (desc->Attribute & KERN_MEMORY_RUNTIME)
{
MEMORY_DESCRIPTOR_T*runtime_desc=(MEMORY_DESCRIPTOR_T*)((UINT8*)runtime_mmap+(curr_runtime_desc*mmap->desc_size));

memcpy(runtime_desc,desc,mmap->desc_size);
runtime_desc->VirtualStart=runtime_desc->PhysicalStart;
curr_runtime_desc++;
}
}

vmem_ers->SetVirtualAddressMap(runtime_mmap_size,mmap->desc_size,mmap->desc_version,runtime_mmap);
}