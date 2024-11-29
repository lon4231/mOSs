#include "mstdi.h"

extern "C" __attribute__((section(".kernel"))) void kmain(kernel_args_t args)
{
memset(args.sgi.buffer,255,args.sgi.w*args.sgi.h*4);





halt_machine();
}
