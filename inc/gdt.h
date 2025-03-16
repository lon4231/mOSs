#pragma once
#include "std_types.h"

typedef UINT64 gdt_entry_t;

struct gdt_tss_entry_t
{
    UINT64 limit_15_0 : 16;
    UINT64 base_15_0 : 16;
    UINT64 base_23_16 : 8;
    UINT64 type : 4;
    UINT64 s : 1;
    UINT64 dpl : 2;
    UINT64 p : 1;
    UINT64 limit_19_16 : 4;
    UINT64 avl : 1;
    UINT64 l : 1;
    UINT64 d_b : 1;
    UINT64 g : 1;
    UINT64 base_31_24 : 8;
    UINT32 base_63_32;
    UINT32 zero;
};

struct gdt_t
{
    gdt_entry_t null;
    gdt_entry_t kernel_code_64;
    gdt_entry_t kernel_data_64;
    gdt_entry_t user_code_64;
    gdt_entry_t user_data_64;
    gdt_entry_t kernel_code_32;
    gdt_entry_t kernel_data_32;
    gdt_entry_t user_code_32;
    gdt_entry_t user_data_32;
    gdt_tss_entry_t tss_segment;
};

struct tss_t
{
    UINT32 reserved_1;
    UINT32 RSP0_lower;
    UINT32 RSP0_upper;
    UINT32 RSP1_lower;
    UINT32 RSP1_upper;
    UINT32 RSP2_lower;
    UINT32 RSP2_upper;
    UINT32 reserved_2;
    UINT32 reserved_3;
    UINT32 IST1_lower;
    UINT32 IST1_upper;
    UINT32 IST2_lower;
    UINT32 IST2_upper;
    UINT32 IST3_lower;
    UINT32 IST3_upper;
    UINT32 IST4_lower;
    UINT32 IST4_upper;
    UINT32 IST5_lower;
    UINT32 IST5_upper;
    UINT32 IST6_lower;
    UINT32 IST6_upper;
    UINT32 IST7_lower;
    UINT32 IST7_upper;
    UINT32 reserved_4;
    UINT32 reserved_5;
    UINT16 reserved_6;
    UINT16 io_map_base;
};

struct gdtr_t
{
    UINT16 limit;
    UINT64 base;
} __attribute__((packed));