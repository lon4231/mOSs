#pragma once

#include "mstdi.h"
#include "globals.h"
#include "alloc.h"


void interrupt_default_handle()
{
save_context();

restore_context();
asm volatile("iretq");
}



void idt_set_descriptor(uint8_t vector,void*isr,uint8_t flags) 
{
idt_desc_t*descriptor=&idt[vector];

descriptor->isr_low=(uint64_t)isr&0xFFFF;
descriptor->kernel_cs=0x8;
descriptor->ist=0;
descriptor->attributes=flags;
descriptor->isr_mid=((uint64_t)isr>>16)&0xFFFF;
descriptor->isr_high=((uint64_t)isr>>32)&0xFFFFFFFF;
descriptor->reserved=0;
}

void remap_pic() 
{
outb(0x20,0x11);
outb(0xA0,0x11);
outb(0x21,0x20);
outb(0xA1,0x28);
outb(0x21,0x04);
outb(0xA1,0x02);
outb(0x21,0x01);
outb(0xA1,0x01);
outb(0x21,0x00);
outb(0xA1,0x00);
}

void init_idt()
{
remap_pic();

for (UINTN i=0;i<256;++i)
{idt_set_descriptor(i,(void*)interrupt_default_handle,INTERRUPT_GATE);}

idtr.base=(UINT64)&idt;
idtr.limit=(sizeof(idt_desc_t)*256)-1;

asm volatile("lidt %0"::"m"(idtr));
asm volatile("sti");
}
