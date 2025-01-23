#pragma once

#include "std_dtypes.h"

typedef UINT64 gdt_entry_t;

struct tss_gdt_entry_t
{
gdt_entry_t entry;
UINT32      base;
UINT32      zero;
}__attribute__((packed));

struct gdt_t
{
gdt_entry_t     null;
gdt_entry_t     kernel_code;
gdt_entry_t     kernel_data;
gdt_entry_t     user_code;
gdt_entry_t     user_data;
tss_gdt_entry_t tss;
}__attribute__((packed));

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
}__attribute__((packed));