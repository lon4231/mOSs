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

vmm_map_pages(&vmm,(void*)kargs->kernel_bin,(void*)kargs->kernel_bin,0b111,kargs->kernel_bin_pages);
vmm_map_pages(&vmm,(void*)kargs->kernel_stack,(void*)kargs->kernel_stack,0b111,kargs->kernel_bin_pages);
vmm_map_pages(&vmm,(void*)kargs,(void*)kargs,0b111,SIZE_TO_PAGES(sizeof(kernel_args_t)));

asm volatile("movq %0, %%CR3;"::"r"(vmm.pml4));


asm volatile("cli;hlt");
}
