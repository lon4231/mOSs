#include "printf.h"


extern "C" void _putchar(char16_t chr) {}

extern "C" void __attribute__((noreturn, section(".kernel"))) kmain()
{
    printf(u"going insane ngl");
    
    asm volatile("cli;hlt");
}
