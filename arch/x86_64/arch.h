#pragma once

#include "acpi.h"
#include "gdt.h"

struct MEMORY_DESCRIPTOR_T
{
    UINT32 Type;
    UINTN PhysicalStart;
    UINTN VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
} __attribute__((packed));

struct MEMORY_MAP_INFO
{
    UINTN size;
    MEMORY_DESCRIPTOR_T *map;
    UINTN key;
    UINTN desc_size;
    UINT32 desc_version;
} __attribute__((packed));

struct idt_entry_t
{
    UINT16 isr_low;
    UINT16 kernel_cs;
    UINT8 ist;
    UINT8 attributes;
    UINT16 isr_mid;
    UINT32 isr_high;
    UINT32 reserved;
} __attribute__((packed));

struct arch_kernel_data_t
{
    xsdp_t *xsdp;
    gdt_t gdt;
    tss_t tss;
    MEMORY_MAP_INFO mmap;
} __attribute__((packed));