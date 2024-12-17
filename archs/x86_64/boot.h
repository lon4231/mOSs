#pragma once

#include "interface.h"
#include "arch.h"
#include "cpu.h"
#include "helper.h"
#include "vmem.h"
#include "alloc.h"


void arch_setup_and_jump_to_kernel(MEMORY_MAP_INFO*mmap,void*kernel_buffer,UINTN kernel_pages)
{

kernel_args_t args;
kernel_args_t*args_ptr=&args;
args.mmap=*mmap;
alloc_context=&args.alloc_context;
args.sgi.buffer=(UINT32*)gop->Mode->FrameBufferBase;
args.sgi.w=gop->Mode->Info->PixelsPerScanLine;
args.sgi.h=gop->Mode->Info->VerticalResolution;
args.krs=*((KERN_RUNTIME_SERVICES*)ers);

mmap_allocate_init(alloc_context,&args.mmap);

pml4=(page_table_t*)mmap_allocate_pages(alloc_context,1);
memset(pml4,0,sizeof(page_table_t));


args.vmem_context.vmem_alloc_context=&args.alloc_context;
args.vmem_context.vmem_pml4=pml4;
args.vmem_context.vmem_map_context={KERNEL_START_ADDRESS,0};
args.vmem_context.vmem_ers=(KERN_RUNTIME_SERVICES*)ers;


identity_map_efi_mmap(&args.vmem_context,&args.mmap);
set_runtime_address_map(&args.vmem_context,&args.mmap);

vmem_map_page(&args.vmem_context,kernel_buffer,kernel_pages*2);



for(UINTN i=0;i<(gop->Mode->FrameBufferSize+(PAGE_SIZE-1))/PAGE_SIZE;i++) 
{identity_map_page(&args.vmem_context,gop->Mode->FrameBufferBase+(i*PAGE_SIZE),&args.mmap);}

const UINTN STACK_PAGES=32;  
void*kernel_stack=mmap_allocate_pages(alloc_context,STACK_PAGES);
memset(kernel_stack,0,STACK_PAGES*PAGE_SIZE);

for (UINTN i=0;i<STACK_PAGES;++i) 
{identity_map_page(&args.vmem_context,(UINTN)kernel_stack+(i*PAGE_SIZE),&args.mmap);}

tss_t tss={.io_map_base=sizeof(tss_t)};
UINTN tss_address=(UINTN)&tss;

gdt_t gdt;
gdt.null={0};
gdt.kernel_code.limit_15_0=0xFFFF;
gdt.kernel_code.base_15_0=0;
gdt.kernel_code.base_23_16=0;
gdt.kernel_code.type=0xA;
gdt.kernel_code.s=1;
gdt.kernel_code.dpl=0;
gdt.kernel_code.p=1;
gdt.kernel_code.limit_19_16=0xF;
gdt.kernel_code.avl=0;
gdt.kernel_code.l=1;
gdt.kernel_code.d_b=0;
gdt.kernel_code.g=1;
gdt.kernel_code.base_31_24 =0;

gdt.kernel_data.limit_15_0=0xFFFF;
gdt.kernel_data.base_15_0=0;
gdt.kernel_data.base_23_16=0;
gdt.kernel_data.type=0x2;
gdt.kernel_data.s=1;
gdt.kernel_data.dpl=0;
gdt.kernel_data.p=1;
gdt.kernel_data.limit_19_16=0xF;
gdt.kernel_data.avl=0;
gdt.kernel_data.l=0;
gdt.kernel_data.d_b=1;
gdt.kernel_data.g=1;
gdt.kernel_data.base_31_24=0;


gdt.tss.descriptor.limit_15_0=sizeof(tss_t)-1;
gdt.tss.descriptor.base_15_0=tss_address & 0xFFFF;
gdt.tss.descriptor.base_23_16=(tss_address >> 16) & 0xFF;
gdt.tss.descriptor.type=9;
gdt.tss.descriptor.p=1;
gdt.tss.descriptor.base_31_24=(tss_address >> 24) & 0xFF;
gdt.tss.base_63_32=(tss_address >> 32) & 0xFFFFFFFF;


desc_reg_t gdtr={.limit=sizeof(gdt)-1,.base=(UINT64)&gdt};

asm volatile
(
"cli\n"
"movq %[pml4],%%CR3\n"
"lgdt %[gdt]\n"
"ltr %[tss]\n"
"pushq $0x8\n"
"leaq 1f(%%RIP),%%RAX\n"
"pushq %%RAX\n"
"lretq\n"
"1:\n"
"movq $0x10,%%RAX\n"
"movq %%RAX,%%DS\n"
"movq %%RAX,%%ES\n"
"movq %%RAX,%%FS\n"
"movq %%RAX,%%GS\n"
"movq %%RAX,%%SS\n"
"movq %[stack],%%RSP\n"
"callq *%[entry]\n"
::  
[pml4]"r"(pml4),
[gdt]"m"(gdtr),
[tss]"r"((UINT16)0x18),
[stack]"gm"((UINTN)kernel_stack+(STACK_PAGES*PAGE_SIZE)),
[entry]"r"(KERNEL_START_ADDRESS),"c"(args_ptr)
:"rax","memory"
);
}