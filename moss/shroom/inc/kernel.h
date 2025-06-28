#ifndef _SHROOM_KERNEL_INTERFACE_DEFINED_
#define _SHROOM_KERNEL_INTERFACE_DEFINED_

#include <cstr.h>
#include <elf/elf.h>
#include <arch.h>

struct kernel_handle_t
{
    void *kernel_code;
    size_t kernel_code_size;

    void *kernel_stack;
    size_t kernel_stack_size;
};

struct kernel_arguments_t
{
    acpi_xsdp_t *xsdp;
};

void load_kernel(kernel_handle_t *handle, const char16_t *path);
void jump_to_kernel(kernel_handle_t *handle, kernel_arguments_t *args);

#endif