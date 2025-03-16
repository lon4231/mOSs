#pragma once

#include "mmap.h"
#include "acpi.h"
#include "gdt.h"
#include "kernel_args.h"

void boot_to_kernel(kernel_args_t*boot_data);