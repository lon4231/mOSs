#include "std_types.h"
#include "std_string.h"
#include "mmap.h"
#include "printf.h"
#include "kernel_args.h"
#include "virtual_memory.h"

extern "C" void _putchar(char16_t chr)
{



}

extern "C" void __attribute__((noreturn,section(".kernel"))) kmain(kernel_args_t*kargs)
{


asm volatile("cli;hlt");
}