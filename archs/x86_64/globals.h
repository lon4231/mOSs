#pragma once

#include "mstdi.h"
#include "arch.h"
#include "cpu.h"

static __attribute__((aligned(0x10))) idt_desc_t idt[256];
static idtr_t idtr;

static xsdt_t*xsdt;
static madt_t*madt;
static fadt_t*fadt;
static srat_t*srat;

static kernel_args_t*kargs;

static tty_context_t tty_context;

static lapic_context_t apic_context;