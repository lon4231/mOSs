#ifndef _SHROOM_KERNEL_INTERFACE_DEFINED_
#define _SHROOM_KERNEL_INTERFACE_DEFINED_

#include <cstr.h>
#include <elf/elf.h>
#include <arch.h>

struct kernel_elf_section_t
{
void*phys_addr;
void*virt_addr;
size_t size;
};

struct kernel_arguments_t
{
    acpi_xsdp_t *xsdp;
};

void jump_to_kernel(kernel_arguments_t *args);

#endif