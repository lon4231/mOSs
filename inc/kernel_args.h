#pragma once
#include "std_types.h"
#include "mmap.h"
#include "acpi.h"

struct kernel_args_t
{
void* kernel_bin;
UINTN kernel_bin_pages;

void* kernel_stack;

mmap_t mmap;

xsdp_t*xsdp;    
};