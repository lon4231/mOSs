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

for (UINTN e=0;e<mcfg_entry_count;++e){for(UINTN i=0;i<256;++i){for(UINTN n=0;n<32;++n){for(UINTN j=0;j<8;++j){
pci_entry_t entry=get_pci_entry(mcfg_entries[e].base_address,i,n,j);
if(entry.vendor_id==0xFFFF){continue;}
printf(u"0x%x 0x%x 0x%x 0x%x 0x%x\r\n",entry.vendor_id,entry.device_id,entry.class_code,entry.subclass,entry.revision_id);
}}}}

enable_sse();

while(true)
{


}


halt_machine();
}
