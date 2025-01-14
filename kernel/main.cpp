#include "kinc.h"
#include "std_driver.h"

extern "C" __attribute__((noreturn,section(".kernel"))) void kmain(kernel_handle_t handle)
{

for(UINTN i=0;i<handle.kdata.driver_count;++i)
{
driver_entry_t entry=(driver_entry_t)handle.kdata.driver_buffers[i];

if(entry!=nullptr)
{entry(&handle);}

}




no_interrupt_halt();
}
