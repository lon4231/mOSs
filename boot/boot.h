#pragma once

#include "mmap.h"
#include "acpi.h"
#include "gdt.h"
#include "kernel_args.h"

#define KERNEL_STACK_PAGES 16

struct boot_data_t
{
void* kernel_bin;
UINTN kernel_bin_pages;

void*kernel_stack;

mmap_t mmap;

xsdp_t*xsdp;
};


void boot_to_kernel(boot_data_t*boot_data);