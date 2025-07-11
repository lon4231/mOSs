#ifndef _MOSS_KERNEL_BOOT_INTERFACE_DEFINED_
#define _MOSS_KERNEL_BOOT_INTERFACE_DEFINED_

#include <arch.h>
#include <boot_memory_map.h>


struct kernel_arguments_t
{
    acpi_xsdp_t *xsdp;
    boot_memory_map_t*bmmap;
};

#endif