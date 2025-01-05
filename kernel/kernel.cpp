#include "mstdi.h"
#include "x86_64/kernel.h"

extern "C" __attribute__((noreturn,section(".kernel"))) void kmain(kernel_args_t args)
{
karch_init_and_setup(&args);

kprintf(u"[mOSs TTY %dx%d]\r\n",tty_context.tty_w,tty_context.tty_h);
kprintf(u"[WELCOME!!]\r\n");




while(true)
{asm volatile("hlt");}

}
