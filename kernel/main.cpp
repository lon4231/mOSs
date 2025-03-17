#include "std_types.h"
#include "std_string.h"
#include "mmap.h"
#include "printf.h"
#include "kernel_args.h"
#include "physical_memory.h"
#include "virtual_memory.h"

static kernel_args_t*kargs;

static UINT64 higher_half_address = 0xFFFFFFFF80000000;


void *reserve_pages(UINTN pages)
{

    void *reserved_chunk = (void *)higher_half_address;

    for (UINTN i = 0; i < pages; ++i)
    {
        void *reserved = (void *)higher_half_address;
        vmm_map_page(&kargs->vmm, pmm_reserve_page(&kargs->pmm), reserved, 0b111);
        higher_half_address += PAGE_SIZE;
    }

    return reserved_chunk;
}

extern "C" void _putchar(CHAR16 chr) {}

extern "C" void __attribute__((noreturn, section(".kernel"))) kmain(kernel_args_t *kargs_ptr)
{
    kargs=kargs_ptr;


    asm volatile("cli;hlt");
}
