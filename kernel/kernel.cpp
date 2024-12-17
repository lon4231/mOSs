#include "mstdi.h"
#include "x86_64/kernel.h"

extern "C" __attribute__((noreturn,section(".kernel"))) void kmain(kernel_args_t args)
{
karch_init_and_setup(&args);

printf(u"[mOSs TTY %dx%d]\r\n",tty_context.tty_w,tty_context.tty_h);
printf(u"[WELCOME!!]\r\n");

void*page=mmap_allocate_pages(&args.alloc_context,1);

printf(u"%x\r\n",page);

page=mmap_allocate_pages(&args.alloc_context,1);

printf(u"%x\r\n",page);

render_tty();

halt_machine();
}
