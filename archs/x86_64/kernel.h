#pragma once

#include "mstdi.h"
#include "arch.h"
#include "cpu.h"
#include "vmem.h"
#include "idt.h"
#include "acpi.h"
#include "pic.h"



void karch_init_and_setup(kernel_args_t*args)
{
vmem_alloc_context=&args->alloc_context;
vmem_pml4         =args->pml4;
vmem_ers          =&args->krs;

enable_sse();

init_acpi(args->xdst);

init_pic();
init_idt();




}