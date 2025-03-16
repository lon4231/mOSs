#pragma once

#include "std_types.h"

struct idt_entry_t
{
    UINT16 isr_low;
    UINT16 kernel_cs;
    UINT8 ist;
    UINT8 attributes;
    UINT16 isr_mid;
    UINT32 isr_high;
    UINT32 reserved;
};

struct idt_t
{
    idt_entry_t entries[256];
};

struct idtr_t
{
    UINT16 limit;
    UINT64 base;
} __attribute__((packed));