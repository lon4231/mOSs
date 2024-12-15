#pragma once

#include "mstdi.h"
#include "arch.h"
#include "cpu.h"
#include "globals.h"
#include "tty.h"
#include "apic.h"

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

void default_interrupt_handler()
{
save_context();

restore_context();

asm volatile("iretq");
}


void init_idt()
{
for(UINTN i=0;i<256;++i)
{idt_set_descriptor(i,(void*)default_interrupt_handler,INTERRUPT_GATE);}



idtr.base=(UINT64)&idt[0];
idtr.limit=sizeof(idt)-1;

asm volatile("lidt %0"::"m"(idtr));
}