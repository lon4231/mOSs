#include "kinc.h"

extern "C" __attribute__((noreturn,section(".kernel"))) void kmain(kernel_handle_t handle)
{





no_interrupt_halt();
}
