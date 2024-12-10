#include "mstdi.h"



extern "C" __attribute__((section(".kernel"))) void kmain(kernel_args_t args)
{



halt_machine();
}
