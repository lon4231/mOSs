#pragma once

#include "efi.h"
#include "efi_wrapper.h"

struct mmap_entry_t
{
    uint32_t Type;
    uint64_t PhysicalStart;
    uint64_t VirtualStart;
    uint64_t NumberOfPages;
    uint64_t Attribute;
};

struct mmap_t
{
    UINTN size;
    mmap_mem_desc_t *map;
    UINTN key;
    UINTN desc_size;
    UINT32 desc_ver;
};

struct boot_data_t
{
    void *xsdp;
    mmap_t*mmap;
};
