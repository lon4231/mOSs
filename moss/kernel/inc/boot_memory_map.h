#ifndef _BOOT_MEMORY_MAP_DEFINED_
#define _BOOT_MEMORY_MAP_DEFINED_

#include <cstdint>
#include <cstddef>

struct boot_memory_map_node_t
{
    void *virtual_range;
    uint64_t size;
    boot_memory_map_node_t *next;
};

struct boot_memory_map_t
{
    uint32_t node_count;
    boot_memory_map_node_t *head;
};

#endif