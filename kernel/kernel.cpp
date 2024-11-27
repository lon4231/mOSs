#include "mstdi.h"
#include "globals.h"
#include "alloc.h"
#include "kprintf.h"
#include "tty/tty.h"
#include "acpi/acpi.h"
#include "interrupts/interrupts.h"
#include "keyboard/kb.h"
#include "pci/pcie.h"

extern "C" __attribute__((section(".kernel"))) void kmain(kernel_args_t args)
{
kargs=args;
sgi=args.sgi;
mmap=args.mmap;
alloc_context=args.alloc_context;
xsdp=args.xsdp;

init_tty();

init_idt();

init_keyboard();

printf(u"[     MOSS_TTY     ]\r\n");
printf(u"[ current: %03dx%03d ]\r\n",tty_w,tty_h);

init_acpi();

init_pcie();

print_pcie();

enable_sse();

while(true)
{


}


halt_machine();
}
