#pragma once

#include "efi.h"
#include "utils.h"
#include "arch.h"
#include "allocator.h"
#include "virtual_memory.h"

void arch_boot_and_exit(efi_t *efi)
{
    arch_kernel_data_t arch_data;

    memset(&arch_data, 0, sizeof(arch_kernel_data_t));

    for (UINTN i = 0; i < efi->system_table->NumberOfTableEntries; ++i)
    {
        EFI_CONFIGURATION_TABLE table = efi->system_table->ConfigurationTable[i];

        if (strncmp((char *)table.VendorTable, "RSD PTR ", 8) == 0)
        {
            arch_data.xsdp = (xsdp_t *)table.VendorTable;
            if (arch_data.xsdp->Revision > 0)
            {
                break;
            }
        }
    }

    arch_data.tss.io_map_base = sizeof(tss_t);

    arch_data.gdt.null = 0x0000000000000000;
    arch_data.gdt.kernel_code = 0x00AF9A000000FFFF;
    arch_data.gdt.kernel_data = 0x00CF92000000FFFF;
    arch_data.gdt.user_code = 0x00AFFA000000FFFF;
    arch_data.gdt.user_data = 0x00CFF2000000FFFF;

    arch_data.gdt.tss.entry =
        (0x0000890000000000) |
        (sizeof(tss_t) - 1) |
        ((((UINTN)&arch_data.tss) & 0xFFFFFF) << 16) |
        ((((UINTN)&arch_data.tss) & 0xFF000000) << 32);
    arch_data.gdt.tss.base = ((UINTN)&arch_data.tss >> 32) & 0xFFFFFFFF;
    
    arch_data.mmap=get_memory_map();

    efi->boot_services->ExitBootServices(efi->image_handle,arch_data.mmap.key);

    alloc_context_t alloc;
    vmem_context_t vmem;

    mmap_allocate_init(&alloc,&arch_data.mmap);
    vmem_init_vmem(&vmem,&alloc);

    vmem_map_page(&vmem,&vmem,(void*)0xFFFFFFFF80000000,PAGE_FLAGS_ALL);
}

