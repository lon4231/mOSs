#include "std_types.h"
#include "std_string.h"
#include "mmap.h"
#include "printf.h"
#include "kernel_args.h"
#include "physical_memory.h"
#include "virtual_memory.h"
#include "sgi.h"

static kernel_args_t*kargs;
static sgi_t*sgi;

extern "C" void _putchar(CHAR16 chr) {}

extern "C" void __attribute__((noreturn, section(".kernel"))) kmain(kernel_args_t *kargs_ptr)
{
    asm volatile("sti");

    kargs=kargs_ptr;

    sgi=(sgi_t*)kargs->dm.head->dev_data;

    memset(sgi->buffer,128,sgi->width*sgi->height*sizeof(sgi_pixel_t));


    asm volatile("cli;hlt");
}
