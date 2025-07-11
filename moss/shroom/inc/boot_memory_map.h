#ifndef _BOOT_MEMORY_MAP_DEFINED_
#define _BOOT_MEMORY_MAP_DEFINED_

#include <cstdint>
#include <cstddef>

enum BOOT_MMAP_ENTRY_TYPE
{
BOOT_MMAP_ENTRY_INVALID,
BOOT_MMAP_ENTRY_USABLE,
BOOT_MMAP_ENTRY_RESERVED,
};

struct boot_memory_map_node_t
{
    void *virtual_range;
    uint64_t size;
    uint16_t type;
    boot_memory_map_node_t *next;
};

struct boot_memory_map_t
{
    uint32_t node_count;
    boot_memory_map_node_t *head;
};

#endif