#include "mstdi.h"
#include "printf.cpp"

extern "C" void _putchar(CHAR16 chr)
{

}

extern "C" __attribute__((section(".kernel"))) void kmain(kernel_args_t args)
{
printf(u"shlit");




halt_machine();
}
