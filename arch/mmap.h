#pragma once

#include "std_types.h"

#define MMAP_MEMORY_UC                 0x0000000000000001
#define MMAP_MEMORY_WC                 0x0000000000000002
#define MMAP_MEMORY_WT                 0x0000000000000004
#define MMAP_MEMORY_WB                 0x0000000000000008
#define MMAP_MEMORY_UCE                0x0000000000000010
#define MMAP_MEMORY_WP                 0x0000000000001000
#define MMAP_MEMORY_RP                 0x0000000000002000
#define MMAP_MEMORY_XP                 0x0000000000004000
#define MMAP_MEMORY_NV                 0x0000000000008000
#define MMAP_MEMORY_MORE_RELIABLE      0x0000000000010000
#define MMAP_MEMORY_RO                 0x0000000000020000
#define MMAP_MEMORY_SP                 0x0000000000040000
#define MMAP_MEMORY_CPU_CRYPTO         0x0000000000080000
#define MMAP_MEMORY_RUNTIME            0x8000000000000000
#define MMAP_MEMORY_ISA_VALID          0x4000000000000000
#define MMAP_MEMORY_ISA_MASK           0x0FFFF00000000000

struct mmap_memory_desc_t
{
UINT32 Type;
UINT64 PhysicalStart;
UINT64 VirtualStart;
UINT64 NumberOfPages;
UINT64 Attribute;
};

struct mmap_t
{
UINTN                   size;
mmap_memory_desc_t*     map;
UINTN                   key;
UINTN                   desc_size;
UINT32                  desc_ver;
};