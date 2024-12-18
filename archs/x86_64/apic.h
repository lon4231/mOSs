#pragma once

#include "mstdi.h"
#include "arch.h"
#include "cpu.h"
#include "globals.h"
#include "acpi.h"
#include "alloc.h"
#include "tty.h"

#define IA32_APIC_BASE                       0x1b
#define APIC_BASE_ADDRESS_MASK               0xFFFFF000
#define APIC_SPURIOUS_VECTOR_REGISTER_OFFSET 0xF0
#define APIC_SPURIOUS_INTERRUPT_IDT_ENTRY    0xFF
#define APIC_SOFTWARE_ENABLE                 (1<<8)
#define APIC_SPURIOUS_INTERRUPT              255

#define PIC_COMMAND_MASTER 0x20
#define PIC_COMMAND_SLAVE  0xA0

#define PIC_DATA_MASTER 0x21
#define PIC_DATA_SLAVE  0xA1

#define ICW_1   0x11
#define ICW_2_M 0x20
#define ICW_2_S 0x28
#define ICW_3_M 0x04
#define ICW_3_S 0x02
#define ICW_4   0x01

uint32_t read_apic_register(uint32_t register_offset) 
{return (*(volatile uint32_t*)((uintptr_t)(apic_context.remmaped_address+register_offset)));}

void write_apic_register(uint32_t register_offset, uint32_t value) 
{(*(volatile uint32_t*)((uintptr_t)(apic_context.remmaped_address+register_offset)))=value;}

void disable_pic() 
{
outb(PIC_COMMAND_MASTER,ICW_1);
outb(PIC_COMMAND_SLAVE,ICW_1);
outb(PIC_DATA_MASTER,ICW_2_M);
outb(PIC_DATA_SLAVE,ICW_2_S);
outb(PIC_DATA_MASTER,ICW_3_M);
outb(PIC_DATA_SLAVE,ICW_3_S);
outb(PIC_DATA_MASTER,ICW_4);
outb(PIC_DATA_SLAVE,ICW_4);
outb(PIC_DATA_MASTER,0xFF);
outb(PIC_DATA_SLAVE,0xFF);
}


void init_apic()
{
UINT64 msr_output=rdmsr(IA32_APIC_BASE);
apic_context.base_address=msr_output&APIC_BASE_ADDRESS_MASK;
apic_context.remmaped_address=(UINTN)vmem_map_page(vmem_context,(void*)apic_context.base_address,1);

wrmsr(IA32_APIC_BASE,msr_output);

uint32_t spurious_interrupt_register = read_apic_register(APIC_SPURIOUS_VECTOR_REGISTER_OFFSET);
write_apic_register(APIC_SPURIOUS_VECTOR_REGISTER_OFFSET, APIC_SOFTWARE_ENABLE | APIC_SPURIOUS_INTERRUPT);

disable_pic();
}