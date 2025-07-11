#include <kernel_init.h>
#include <cstr.h>

gdt_t gdt;
gdtr_t gdtr;

idt_t idt;
idtr_t idtr;

tss_t tss;



inline __attribute__((always_inline)) void setup_gdt()
{
    gdt =
        {
            .null = 0x0000000000000000,
            .kernel_code = 0x00AF9A000000FFFF,
            .kernel_data = 0x00CF92000000FFFF,
            .user_code = 0x00AFFA000000FFFF,
            .user_data = 0x00CFF2000000FFFF,
        };

    gdt.tss_entry.entry =
        ((sizeof(tss_t) - 1) & 0xFFFF) |
        ((((uint64_t)&tss) & 0xFFFF) << 16) |
        ((((uint64_t)&tss) & 0xFF0000) << 16) |
        ((uint64_t)0x89 << 40) |
        ((uint64_t)(((uint64_t)&tss) & 0xFF000000) << 32);

    gdt.tss_entry.ext_base = (((uint64_t)&tss) >> 32) & 0xFFFFFFFF;

    memset(&tss, 0, sizeof(tss_t));
    tss.io_map_base = sizeof(tss_t);

    gdtr.base = (uint64_t)&gdt;
    gdtr.limit = sizeof(gdt_t) - 1;

    SET_GDT(gdtr);
    SET_TSS(0x28);

    printf("GDT... OK\r\n");
}

inline __attribute__((always_inline)) void setup_idt()
{


idtr.base=(uint64_t)&idt;
idtr.limit=sizeof(idt_t)-1;

SET_IDT(idtr);

asm volatile("sti");

printf("IDT... OK\r\n");
}

void kernel_init()
{
    setup_gdt();
    setup_idt();
}