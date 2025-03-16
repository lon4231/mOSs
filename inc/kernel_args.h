#pragma once
#include "std_types.h"
#include "mmap.h"
#include "acpi.h"

#define KERNEL_STACK_PAGES 16

struct kernel_args_t
{
void* kernel_bin;
UINTN kernel_bin_pages;

void* kernel_stack;

mmap_t mmap;

xsdp_t*xsdp;
};