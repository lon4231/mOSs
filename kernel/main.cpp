#include "std_types.h"
#include "std_string.h"
#include "mmap.h"
#include "printf.h"
#include "kernel_args.h"
#include "physical_memory.h"
#include "virtual_memory.h"

static phys_mem_handle_t pmm;
static vmem_handle_t     vmm;

void*vmm_bootstrap_page_request()
{
return phys_mem_reserve_page(&pmm);
}


extern "C" void __attribute__((noreturn,section(".kernel"))) kmain(kernel_args_t*kargs)
{
init_phys_mem(&pmm,&kargs->mmap);

init_vmm(&vmm,phys_mem_reserve_page(&pmm));

vmm.request_page=vmm_bootstrap_page_request;




asm volatile("movq %0, %%CR3;"::"r"(vmm.pml4));





asm volatile("cli;hlt");
}
