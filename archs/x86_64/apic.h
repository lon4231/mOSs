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
#define PIT_MODE_COMMAND_REGISTER 0x43

#define IO_APIC_IRQ_TIMER_INDEX 0x14

#define PIT_COUNTER_VALUE 0x4A9

#define PIT_CONFIGURATION_BYTE 0b00110100

#define CALIBRATION_MS_TO_WAIT 30

#define APIC_TIMER_SET_PERIODIC 0x20000
#define APIC_TIMER_SET_MASKED 0x10000

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

uint32_t read_io_apic_register(uint8_t offset)
{
*(volatile uint32_t*) ioapic_context.remmaped_address=offset;
return *(volatile uint32_t*) (ioapic_context.remmaped_address + 0x10);
}

void write_io_apic_register(uint8_t offset,uint32_t value) 
{
*(volatile uint32_t*) ioapic_context.remmaped_address=offset;
*(volatile uint32_t*) (ioapic_context.remmaped_address + 0x10)=value;
}
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

uint32_t spurious_interrupt_register=read_apic_register(APIC_SPURIOUS_VECTOR_REGISTER_OFFSET);
write_apic_register(APIC_SPURIOUS_VECTOR_REGISTER_OFFSET,APIC_SOFTWARE_ENABLE | APIC_SPURIOUS_INTERRUPT);

disable_pic();
}

void parse_ioapic_src_overrides()
{
for(UINT32 i=0;i<get_madt_size();++i)
{
madt_entry_t madt_entry=get_madt_entry(i);
if(madt_entry.type==MADT_IO_APIC_INTERRUPT_SOURCE_OVERRIDE)
{ioapic_context.source_overrides_count++;}
}
ioapic_context.source_overrides=(io_apic_source_override_item_t*)mmap_allocate_pages(&kargs->alloc_context,SIZE_TO_PAGES(sizeof(io_apic_source_override_item_t)*ioapic_context.source_overrides_count));
ioapic_context.source_overrides_count=0;
for(UINT32 i=0;i<get_madt_size();++i)
{
madt_entry_t madt_entry=get_madt_entry(i);
if(madt_entry.type==MADT_IO_APIC_INTERRUPT_SOURCE_OVERRIDE)
{
madt_ioapic_interrupts_source_override_t*entry=(madt_ioapic_interrupts_source_override_t*)madt_entry.entry_ptr;
ioapic_context.source_overrides[ioapic_context.source_overrides_count].bus_source=entry->bus_src;
ioapic_context.source_overrides[ioapic_context.source_overrides_count].flags=entry->flags;
ioapic_context.source_overrides[ioapic_context.source_overrides_count].global_system_interrupt=entry->global_sys_interrupt;
ioapic_context.source_overrides[ioapic_context.source_overrides_count].irq_source=entry->irq_src;

ioapic_context.source_overrides_count++;
}
}
}

int read_io_apic_redirect(uint8_t index,io_apic_redirect_entry_t *redtbl_entry){
if (index < 0x10 || index > 0x3F) {
return -1;
}
if ((index%2) != 0) {
return -1;
}
uint32_t lower_part;
uint32_t upper_part;
lower_part=read_io_apic_register(index);
upper_part=read_io_apic_register(index+1);
uint64_t raw_value=((uint64_t) upper_part << 32) | ((uint64_t) lower_part);
redtbl_entry->raw=raw_value;
return 0;
}

int write_io_apic_redirect(uint8_t index,io_apic_redirect_entry_t redtbl_entry) {
if (index < 0x10 || index > 0x3F) {
return -1;
}
if ((index%2) != 0) {
return -1;
}
uint32_t upper_part=(uint32_t) (redtbl_entry.raw >> 32);
uint32_t lower_part=(uint32_t) redtbl_entry.raw;
/* pretty_logf(Verbose,": Lower part: %x,: upper part: %x",lower_part,upper_part); */
write_io_apic_register(index,lower_part);
write_io_apic_register(index+1,upper_part);
return 0;
}

void init_ioapic()
{
madt_ioapic_t*ioapic_entry;
for(UINT32 i=0;i<get_madt_size();++i)
{
madt_entry_t entry=get_madt_entry(i);
if(entry.type==MADT_IO_APIC)
{ioapic_entry=(madt_ioapic_t*)entry.entry_ptr;break;}
}

ioapic_context.base_address=ioapic_entry->ioapic_address;
ioapic_context.remmaped_address=(UINTN)vmem_map_page(vmem_context,(void*)ioapic_context.base_address,1);

parse_ioapic_src_overrides();
}

void set_irq(uint8_t irq_type,uint8_t redirect_table_pos,uint8_t idt_entry,uint8_t destination_field,uint32_t flags,bool masked) {
uint8_t counter=0;
uint8_t selected_pin=irq_type;
io_apic_redirect_entry_t entry;
entry.raw=flags | (idt_entry & 0xFF);
while(counter < ioapic_context.source_overrides_count) {
if(ioapic_context.source_overrides[counter].irq_source == irq_type) {
selected_pin=ioapic_context.source_overrides[counter].global_system_interrupt;
if((ioapic_context.source_overrides[counter].flags & 0b11) == 2) {
entry.pin_polarity=0b1;
} else  {
entry.pin_polarity=0b0;
}
entry.trigger_mode=(((ioapic_context.source_overrides[counter].flags >> 2) & 0b11) == 2);
break;
}
counter++;
}
entry.destination_field=destination_field;
entry.interrupt_mask=masked;
write_io_apic_redirect(redirect_table_pos,entry);
io_apic_redirect_entry_t read_entry;
int ret_val=read_io_apic_redirect(IOREDTBL1,&read_entry);
}

int set_irq_mask(uint8_t redirect_table_pos,bool masked_status) {
io_apic_redirect_entry_t read_entry;
int ret_val=read_io_apic_redirect(redirect_table_pos,&read_entry);
if(ret_val == 0) {
read_entry.interrupt_mask=masked_status;
write_io_apic_redirect(redirect_table_pos,read_entry);
} 
else  
{return -1;}
return 0;
}

UINT32 calibrate_apic() 
{
outb(PIT_MODE_COMMAND_REGISTER,0b00110100);
outb(PIT_CHANNEL_0_DATA_PORT,PIT_COUNTER_VALUE & 0xFF);
outb(PIT_CHANNEL_0_DATA_PORT,(PIT_COUNTER_VALUE >> 8));
write_apic_register(APIC_TIMER_INITIAL_COUNT_REGISTER_OFFSET,0);
write_apic_register(APIC_TIMER_CONFIGURATION_OFFSET,APIC_TIMER_DIVIDER_2);
set_irq_mask(IOREDTBL2,false);
write_apic_register(APIC_TIMER_INITIAL_COUNT_REGISTER_OFFSET,(uint32_t)-1);
while(apic_context.pit_ticks < CALIBRATION_MS_TO_WAIT);
uint32_t current_apic_count=read_apic_register(APIC_TIMER_CURRENT_COUNT_REGISTER_OFFSET);
write_apic_register(APIC_TIMER_INITIAL_COUNT_REGISTER_OFFSET,0);
set_irq_mask(IOREDTBL2,true);
uint32_t time_elapsed=((uint32_t)-1)-current_apic_count;
uint32_t apic_calibrated_ticks=time_elapsed/CALIBRATION_MS_TO_WAIT;
apic_context.timer_ticks_base=apic_calibrated_ticks;
apic_context.timer_divisor=APIC_TIMER_DIVIDER_2;
return apic_calibrated_ticks;
}

void start_apic_timer(uint32_t initial_count,uint32_t flags,uint8_t divider) {

write_apic_register(APIC_TIMER_INITIAL_COUNT_REGISTER_OFFSET,initial_count);
write_apic_register(APIC_TIMER_CONFIGURATION_OFFSET,divider);
write_apic_register(APIC_TIMER_LVT_OFFSET,flags | APIC_TIMER_IDT_ENTRY);
asm("sti");
}