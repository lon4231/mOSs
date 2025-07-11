#ifndef _ARCH_ASM_BLOCKS_DEFINED_
#define _ARCH_ASM_BLOCKS_DEFINED_

#include <arch_types.h>
#include <acpi.h>
#include <gdt.h>
#include <idt.h>
#include <page_tables.h>

#define SET_GDT(gdtr) asm volatile("lgdt %0;" ::"m"(gdtr))
#define SET_IDT(idtr) asm volatile("lidt %0;" ::"m"(gdtr))

#define SET_TSS(tss_seg) asm volatile("ltr %0;" ::"r"((uint16_t)0x28))
#define SET_STACK(new_stack) asm volatile("movq %0, %%RSP" ::"gm"(new_stack))
#define SET_CR3(new_cr3) asm volatile("mov %0, %%cr3" ::"r"(new_cr3) : "memory")


#define SWITCH_GDT_SEG(CODE_SEGMENT, DATA_SEG)              \
    asm volatile(                                           \
        "movw %[seg], %%ax\n\t"                             \
        "pushq %%rax\n\t"                                   \
        "leaq 1f(%%rip), %%rax\n\t"                         \
        "pushq %%rax\n\t"                                   \
        "lretq\n\t"                                         \
        "1:\n\t"                                            \
        "movq %[data_seg], %%rax\n\t"                       \
        "movq %%rax, %%ds\n\t"                              \
        "movq %%rax, %%es\n\t"                              \
        "movq %%rax, %%fs\n\t"                              \
        "movq %%rax, %%gs\n\t"                              \
        "movq %%rax, %%ss\n\t"                              \
        :                                                   \
        : [seg] "i"(CODE_SEGMENT), [data_seg] "i"(DATA_SEG) \
        : "rax", "memory")

#define OUTB(port, data) asm volatile("outb %b0, %w1" : : "a"(data), "Nd"(port) : "memory")

#endif