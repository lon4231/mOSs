#include "std_types.h"
#include "std_string.h"
#include "mmap.h"

extern "C" void _putchar(char16_t chr)
{

}

extern "C" void __attribute__((noreturn,section(".kernel"))) kmain()
{


asm volatile("cli;hlt");
}