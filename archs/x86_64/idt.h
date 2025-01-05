#pragma once

#include "mstdi.h"
#include "arch.h"
#include "cpu.h"
#include "globals.h"
#include "tty.h"
#include "apic.h"
#include "keyboard.h"

extern "C" cpu_status_t*handle_interrupt()
{
cpu_status_t*cpu_status;
asm volatile("movq %%rdi,%0":"=r"(cpu_status));

switch(cpu_status->interrupt_number)
{
case 32:
write_apic_register(APIC_EOI_REGISTER_OFFSET,0x00l);
break;
    
case 33:
keyboard_handler();
write_apic_register(APIC_EOI_REGISTER_OFFSET,0x00l);
break;

case 34:
apic_context.pit_ticks++;
write_apic_register(APIC_EOI_REGISTER_OFFSET,0x00l);
break;

case 255:
write_apic_register(APIC_EOI_REGISTER_OFFSET,0x00l);
break;

default:break;
}

return cpu_status;
}

#define NO_ERR_ISR_MACRO(x) void __attribute__((naked)) __isr##x()\
{\
asm volatile("cli;pushq $0x0;pushq %0;"::"i"(x));\
save_context();\
asm volatile("mov %rsp,%rdi");\
asm volatile("cld");\
asm volatile("call handle_interrupt");\
restore_context();\
asm volatile("add $16,%rsp;iretq");\
}

#define ERR_ISR_MACRO(x) void __attribute__((naked)) __isr##x()\
{\
asm volatile("cli;pushq %0;"::"i"(x));\
save_context();\
restore_context();\
asm volatile("add $16,%rsp;iretq");\
}

NO_ERR_ISR_MACRO(0 )
NO_ERR_ISR_MACRO(1 )
NO_ERR_ISR_MACRO(2 )
NO_ERR_ISR_MACRO(3 )
NO_ERR_ISR_MACRO(4 )
NO_ERR_ISR_MACRO(5 )
NO_ERR_ISR_MACRO(6 )
NO_ERR_ISR_MACRO(7 )
ERR_ISR_MACRO   (8 )
NO_ERR_ISR_MACRO(9 )
ERR_ISR_MACRO   (10)
ERR_ISR_MACRO   (11)
ERR_ISR_MACRO   (12)
ERR_ISR_MACRO   (13)
ERR_ISR_MACRO   (14)
NO_ERR_ISR_MACRO(15)
NO_ERR_ISR_MACRO(16)
ERR_ISR_MACRO   (17)
NO_ERR_ISR_MACRO(18)

NO_ERR_ISR_MACRO(32)
NO_ERR_ISR_MACRO(33)
NO_ERR_ISR_MACRO(34)
NO_ERR_ISR_MACRO(128)
NO_ERR_ISR_MACRO(255)

void idt_set_descriptor(UINT8 vector,void*isr,UINT8 flags) 
{
idt_desc_t*descriptor=&idt[vector];
descriptor->isr_low   =(UINT64)isr&0xFFFF;
descriptor->kernel_cs =0x8;
descriptor->ist       =0;
descriptor->attributes=flags;
descriptor->isr_mid   =((UINT64)isr>>16)&0xFFFF;
descriptor->isr_high  =((UINT64)isr>>32)&0xFFFFFFFF;
descriptor->reserved  =0;
}

void init_idt()
{
memset(idt,0,sizeof(idt));

idt_set_descriptor(0, (void*)__isr0,INTERRUPT_GATE);
idt_set_descriptor(1, (void*)__isr1,INTERRUPT_GATE);
idt_set_descriptor(2, (void*)__isr2,INTERRUPT_GATE);
idt_set_descriptor(3, (void*)__isr3,INTERRUPT_GATE);
idt_set_descriptor(4, (void*)__isr4,INTERRUPT_GATE);
idt_set_descriptor(5, (void*)__isr5,INTERRUPT_GATE);
idt_set_descriptor(6, (void*)__isr6,INTERRUPT_GATE);
idt_set_descriptor(7, (void*)__isr7,INTERRUPT_GATE);
idt_set_descriptor(8, (void*)__isr8,INTERRUPT_GATE);
idt_set_descriptor(9, (void*)__isr9,INTERRUPT_GATE);
idt_set_descriptor(10,(void*)__isr10,INTERRUPT_GATE);
idt_set_descriptor(11,(void*)__isr11,INTERRUPT_GATE);
idt_set_descriptor(12,(void*)__isr12,INTERRUPT_GATE);
idt_set_descriptor(13,(void*)__isr13,INTERRUPT_GATE);
idt_set_descriptor(14,(void*)__isr14,INTERRUPT_GATE);
idt_set_descriptor(15,(void*)__isr15,INTERRUPT_GATE);
idt_set_descriptor(16,(void*)__isr16,INTERRUPT_GATE);
idt_set_descriptor(17,(void*)__isr17,INTERRUPT_GATE);
idt_set_descriptor(18,(void*)__isr18,INTERRUPT_GATE);

idt_set_descriptor(32,(void*)__isr32,INTERRUPT_GATE);
idt_set_descriptor(33,(void*)__isr33,INTERRUPT_GATE);
idt_set_descriptor(34,(void*)__isr34,INTERRUPT_GATE);

idt_set_descriptor(128,(void*)__isr128,INTERRUPT_GATE);
idt_set_descriptor(255,(void*)__isr255,INTERRUPT_GATE);

idtr.base=(UINT64)&idt[0];
idtr.limit=sizeof(idt)-1;

asm volatile("lidt %0"::"m"(idtr));
}