#pragma once

#include "efi.h"
#include "std_string.h"
#include "mmap.h"
#include "printf.h"
#include "acpi.h"

struct boot_data_t
{
void* kernel_bin;
UINTN kernel_bin_pages;

mmap_t mmap;

xsdp_t*xsdp;
};

struct kernel_args_t
{
void* kernel_bin;
UINTN kernel_bin_pages;

void* kernel_stack;
UINTN kernel_stack_pages;
    
mmap_t mmap;

xsdp_t*xsdp;    
};

void boot_to_kernel(boot_data_t*boot_data);