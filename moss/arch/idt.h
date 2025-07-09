#ifndef _ARCH_IDT_DEFINED_
#define _ARCH_IDT_DEFINED_

#include <arch_types.h>

struct idt_entry_t
{
    uint16_t isr_low;
    uint16_t kernel_cs;
    uint8_t ist;
    uint8_t attributes;
    uint16_t isr_mid;
    uint32_t isr_high;
    uint32_t reserved;
} __attribute__((packed));

#endif