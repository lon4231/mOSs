#pragma once

#include "mstdi.h"
#include "arch.h"
#include "cpu.h"
#include "vmem.h"
#include "idt.h"
#include "acpi.h"
#include "apic.h"
#include "tty.h"
#include "pci.h"

void karch_init_and_setup(kernel_args_t*args)
{
asm volatile("cli");
kargs=args;
xsdt=args->xdst;
vmem_context=&args->vmem_context;

init_tty();
kprintf(u"[tty      initialized]\r\n");
init_acpi();
kprintf(u"[acpi     initialized]\r\n");
init_idt();
kprintf(u"[idt      initialized]\r\n");
init_apic();
kprintf(u"[apic     initialized]\r\n");
init_ioapic();
kprintf(u"[ioapic   initialized]\r\n");
init_pci();
kprintf(u"[pci      initialized]\r\n");

inb(0x60);
kprintf(u"[keyboard initialized]\r\n");

set_irq(1,IOREDTBL1,0x21,0,0,false);
set_irq(2,IOREDTBL2,0x22,0,0,true);
kprintf(u"[irqs     initialized]\r\n\n");

asm volatile("sti");

uint32_t apic_ticks=calibrate_apic();
start_apic_timer(apic_ticks,APIC_TIMER_SET_PERIODIC,apic_context.timer_divisor);



}