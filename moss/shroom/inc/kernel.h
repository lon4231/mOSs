#ifndef _SHROOM_KERNEL_INTERFACE_DEFINED_
#define _SHROOM_KERNEL_INTERFACE_DEFINED_

#include <cstr.h>
#include <elf/elf.h>
#include <arch.h>

#define SETUP_STACK_SIZE 4

struct kernel_arguments_t
{
    acpi_xsdp_t *xsdp;
};

void jump_to_kernel(kernel_arguments_t *args);

#endif