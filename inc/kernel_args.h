#pragma once
#include "std_types.h"
#include "mmap.h"
#include "acpi.h"
#include "gdt.h"
#include "idt.h"
#include "physical_memory.h"
#include "virtual_memory.h"
#include "device_manager.h"

#define KERNEL_STACK_PAGES 16
#define KERNEL_BSS_SIZE 16

struct kernel_args_t
{
    void *kernel_bin;
    UINTN kernel_bin_pages;

    void *kernel_stack;

    mmap_t mmap;

    xsdp_t *xsdp;

    gdt_t gdt;
    tss_t tss;
    gdtr_t gdtr;

    idt_t idt;
    idtr_t idtr;

    pmm_handle_t pmm;
    vmm_handle_t vmm;
    device_manager_t dm;
};
