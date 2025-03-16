#include "std_types.h"
#include "std_string.h"
#include "mmap.h"
#include "printf.h"
#include "kernel_args.h"
#include "physical_memory.h"
#include "virtual_memory.h"

static pmm_handle_t pmm;
static vmm_handle_t vmm;

void*vmm_bootstrap_page_request()
{
return pmm_reserve_page(&pmm);
}

extern "C" void _putchar(CHAR16 chr){}

extern "C" void __attribute__((noreturn,section(".kernel"))) kmain(kernel_args_t*kargs)
{
init_pmm(&pmm,&kargs->mmap);

init_vmm(&vmm,pmm_reserve_page(&pmm));

vmm.request_page=vmm_bootstrap_page_request;

for(UINTN i=0;i<(kargs->mmap.size/kargs->mmap.desc_size);++i)
{
mmap_mem_desc_t*desc=(mmap_mem_desc_t*)((UINT8*)kargs->mmap.map+(i*kargs->mmap.desc_size));

vmm_map_pages(&vmm,(void*)desc->PhysicalStart,(void*)desc->VirtualStart,0b111,desc->NumberOfPages);
}

asm volatile("movq %0, %%CR3;"::"r"(vmm.pml4));






asm volatile("cli;hlt");
}
