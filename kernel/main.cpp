#include "std_types.h"
#include "std_string.h"
#include "mmap.h"
#include "printf.h"
#include "kernel_args.h"
#include "physical_memory.h"
#include "virtual_memory.h"

static kernel_args_t*kargs;

extern "C" void _putchar(CHAR16 chr) {}

extern "C" void __attribute__((noreturn, section(".kernel"))) kmain(kernel_args_t *kargs_ptr)
{
    kargs=kargs_ptr;



    asm volatile("cli;hlt");
}
