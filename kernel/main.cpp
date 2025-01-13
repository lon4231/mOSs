#include "kinc.h"

extern "C" __attribute__((noreturn,section(".kernel"))) void kmain(kernel_handle_t handle)
{

for(UINTN i=0;i<handle.kdata.driver_count;++i)
{

}




no_interrupt_halt();
}
