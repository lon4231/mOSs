#include "std_types.h"
#include "std_string.h"
#include "mmap.h"
#include "printf.h"
#include "kernel_args.h"
#include "physical_memory.h"
#include "virtual_memory.h"

static phys_mem_handle_t pmm;
static vmem_handle_t     vmm;

extern "C" void _putchar(char16_t chr)
{



}

extern "C" void __attribute__((noreturn,section(".kernel"))) kmain(kernel_args_t*kargs)
{
init_phys_mem(&pmm,&kargs->mmap);
init_vmm(&vmm,phys_mem_reserve_page(&pmm));




asm volatile("cli;hlt");
}
