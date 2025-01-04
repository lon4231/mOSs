#pragma once

#include "mstdi.h"
#include "arch.h"
#include "cpu.h"

static idt_desc_t idt[256];
static idtr_t idtr;

static xsdt_t*xsdt;
static madt_t*madt;
static fadt_t*fadt;
static srat_t*srat;
static mcfg_t*mcfg;


static kernel_args_t*kargs;
static vmem_context_t*vmem_context;

static tty_context_t tty_context;

static lapic_context_t apic_context;
static ioapic_context_t ioapic_context;

static void*pci_base;