#pragma once

#include "mstdi.h"
#include "arch.h"
#include "cpu.h"
#include "globals.h"
#include "acpi.h"
#include "alloc.h"
#include "tty.h"

#define IA32_APIC_BASE   0x1b
#define APIC_BASE_ADDRESS_MASK   0xFFFFF000
#define APIC_SPURIOUS_VECTOR_REGISTER_OFFSET 0xF0
#define APIC_SPURIOUS_INTERRUPT_IDT_ENTRY0xFF
#define APIC_SOFTWARE_ENABLE (1<<8)
#define APIC_SPURIOUS_INTERRUPT  255
#define APIC_EOI_REGISTER_OFFSET 0xB0
#define APIC_TIMER_LVT_OFFSET 0x00000320
#define APIC_TIMER_CONFIGURATION_OFFSET 0x3E0
#define APIC_TIMER_INITIAL_COUNT_REGISTER_OFFSET 0x380
#define APIC_TIMER_CURRENT_COUNT_REGISTER_OFFSET 0x390
#define APIC_TIMER_IDT_ENTRY 0x20
#define PIT_CHANNEL_0_DATA_PORT 0x40
#define PIT_MODE_COMMAND_REGISTER   0x43

#define IO_APIC_IRQ_TIMER_INDEX 0x14

#define PIT_COUNTER_VALUE 0x4A9

#define PIT_CONFIGURATION_BYTE 0b00110100

#define CALIBRATION_MS_TO_WAIT  30

#define APIC_TIMER_SET_PERIODIC 0x20000
#define APIC_TIMER_SET_MASKED   0x10000

#define APIC_TIMER_DIVIDER_1 0xB
#define APIC_TIMER_DIVIDER_2 0x0
#define APIC_TIMER_DIVIDER_4 0x1
#define APIC_TIMER_DIVIDER_8 0x2
#define APIC_TIMER_DIVIDER_16 0x3
#define APIC_TIMER_DIVIDER_32 0x8
#define APIC_TIMER_DIVIDER_64 0x9
#define APIC_TIMER_DIVIDER_128 0xA

#define IOREDTBL0   0x10
#define IOREDTBL1   0x12
#define IOREDTBL2   0x14
#define IOREDTBL3   0x16
#define IOREDTBL4   0x18
#define IOREDTBL5   0x1A
#define IOREDTBL6   0x1C
#define IOREDTBL7   0x1E
#define IOREDTBL8   0x20
#define IOREDTBL9   0x22
#define IOREDTBL10  0x24
#define IOREDTBL11  0x26
#define IOREDTBL12  0x28
#define IOREDTBL13  0x2A
#define IOREDTBL14  0x2C
#define IOREDTBL15  0x2E
#define IOREDTBL16  0x30
#define IOREDTBL17  0x32
#define IOREDTBL18  0x34
#define IOREDTBL19  0x36
#define IOREDTBL20  0x38
#define IOREDTBL21  0x3A
#define IOREDTBL22  0x3C
#define IOREDTBL23  0x3E

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

void write_apic_register(uint32_t register_offset,uint32_t value) 
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

uint32_t spurious_interrupt_register=read_apic_register(APIC_SPURIOUS_VECTOR_REGISTER_OFFSET);
write_apic_register(APIC_SPURIOUS_VECTOR_REGISTER_OFFSET,APIC_SOFTWARE_ENABLE | APIC_SPURIOUS_INTERRUPT);


}