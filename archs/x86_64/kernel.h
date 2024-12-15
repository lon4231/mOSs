#pragma once

#include "mstdi.h"
#include "arch.h"
#include "cpu.h"
#include "vmem.h"
#include "idt.h"
#include "acpi.h"
#include "apic.h"
#include "tty.h"


void karch_init_and_setup(kernel_args_t*args)
{
kargs=args;
xsdt=args->xdst;
vmem_context=&args->vmem_context;
init_tty();
init_acpi();
init_apic();
init_idt();






}