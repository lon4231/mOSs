#include "mstdi.h"
#include "x86_64/kernel.h"

extern "C" __attribute__((noreturn,section(".kernel"))) void kmain(kernel_args_t args)
{
karch_init_and_setup(&args);




halt_machine();
}
