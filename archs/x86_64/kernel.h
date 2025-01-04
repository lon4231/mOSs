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
init_acpi();
init_apic();
init_idt();

init_pci();



asm volatile("sti");

}