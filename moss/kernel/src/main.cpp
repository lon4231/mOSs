#include <arch.h>
#include <kernel_boot_interface.h>
#include <printf/printf.h>
#include <kernel_init.h>

extern "C" void _putchar(char chr)
{
    OUTB(0x3F8, chr);
}

extern "C" __attribute__((ms_abi)) void kmain(kernel_arguments_t *kargs)
{
    kernel_init();




    asm volatile("cli;hlt");

    return;
}