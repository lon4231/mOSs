#pragma once

#include "mmap.h"
#include "acpi.h"
#include "gdt.h"
#include "kernel_args.h"
#include "sgi.h"

struct boot_data_t
{
sgi_t sgi;

};

void boot_to_kernel(kernel_args_t *kernel_args,boot_data_t*boot_data);
