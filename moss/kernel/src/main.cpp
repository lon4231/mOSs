#include <arch.h>
#include <kernel_boot_interface.h>
#include <printf/printf.h>

const char str[]="mystrfuckfuckfuck";

inline void outb(uint16_t port, uint8_t data)
{
asm volatile("outb %b0, %w1" : : "a"(data), "Nd"(port) : "memory");
}

extern "C" void _putchar(char chr)
{
outb(0x3F8,chr);
}

extern "C" __attribute__((ms_abi)) void kmain(kernel_arguments_t *kargs)
{
    printf("printf: %s\r\n",str);

    asm volatile("cli;hlt");

    return;
}