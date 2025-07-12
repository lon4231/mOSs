#ifndef _ARCH_GDT_DEFINED_
#define _ARCH_GDT_DEFINED_

#include <arch_types.h>

typedef uint64_t gdt_entry_t;

struct tss_entry_t
{
    gdt_entry_t entry;
    uint32_t ext_base;
    uint32_t reserved;
};

typedef struct
{
    uint32_t reserved_1;
    uint32_t rsp0_lower;
    uint32_t rsp0_upper;
    uint32_t rsp1_lower;
    uint32_t rsp1_upper;
    uint32_t rsp2_lower;
    uint32_t rsp2_upper;
    uint32_t reserved_2;
    uint32_t reserved_3;
    uint32_t ist1_lower;
    uint32_t ist1_upper;
    uint32_t ist2_lower;
    uint32_t ist2_upper;
    uint32_t ist3_lower;
    uint32_t ist3_upper;
    uint32_t ist4_lower;
    uint32_t ist4_upper;
    uint32_t ist5_lower;
    uint32_t ist5_upper;
    uint32_t ist6_lower;
    uint32_t ist6_upper;
    uint32_t ist7_lower;
    uint32_t ist7_upper;
    uint32_t reserved_4;
    uint32_t reserved_5;
    uint16_t reserved_6;
    uint16_t io_map_base;
} tss_t;

struct gdt_t
{
    gdt_entry_t null;
    gdt_entry_t kernel_code;
    gdt_entry_t kernel_data;

    gdt_entry_t user_code;
    gdt_entry_t user_data;

    tss_entry_t tss_entry;
};

struct gdtr_t
{
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));


#endif