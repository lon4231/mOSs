#pragma once

#include "efi.h"
#include "utils.h"
#include "arch.h"
#include "allocator.h"
#include "virtual_memory.h"



void set_runtime_address_map(alloc_context_t *alloc, MEMORY_MAP_INFO *mmap)
{
    UINTN runtime_descriptors = 0;
    for (UINTN i = 0; i < mmap->size / mmap->desc_size; i++)
    {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)mmap->map + (i * mmap->desc_size));
        if (desc->Attribute & EFI_MEMORY_RUNTIME)
            runtime_descriptors++;
    }
    UINTN runtime_mmap_pages = (runtime_descriptors * mmap->desc_size) + ((PAGE_SIZE - 1) / PAGE_SIZE);
    EFI_MEMORY_DESCRIPTOR *runtime_mmap = (EFI_MEMORY_DESCRIPTOR *)mmap_allocate_pages(alloc, runtime_mmap_pages);
    if (!runtime_mmap)
    {
        return;
    }
    UINTN runtime_mmap_size = runtime_mmap_pages * PAGE_SIZE;
    memset(runtime_mmap, 0, runtime_mmap_size);
    UINTN curr_runtime_desc = 0;
    for (UINTN i = 0; i < mmap->size / mmap->desc_size; i++)
    {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)mmap->map + (i * mmap->desc_size));
        if (desc->Attribute & EFI_MEMORY_RUNTIME)
        {
            EFI_MEMORY_DESCRIPTOR *runtime_desc = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)runtime_mmap + (curr_runtime_desc * mmap->desc_size));
            memcpy(runtime_desc, desc, mmap->desc_size);
            runtime_desc->VirtualStart = runtime_desc->PhysicalStart;
            curr_runtime_desc++;
        }
    }
    efi.runtime_services->SetVirtualAddressMap(runtime_mmap_size, mmap->desc_size, mmap->desc_version, runtime_mmap);
}

void identity_map_mmap(vmem_context_t *vmem, MEMORY_MAP_INFO *mmap)
{
    for (UINTN i = 0; i < mmap->size / mmap->desc_size; i++)
    {
        EFI_MEMORY_DESCRIPTOR *desc =
            (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)mmap->map + (i * mmap->desc_size));

        for (UINTN j = 0; j < desc->NumberOfPages; j++)
            vmem_identity_map_page(vmem, (void *)(desc->PhysicalStart + (j * PAGE_SIZE)), PAGE_FLAGS_ALL);
    }
}

















void arch_boot_and_exit(efi_t *efi,boot_data_t*data)
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

    arch_data.mmap = get_memory_map();

    efi->boot_services->ExitBootServices(efi->image_handle, arch_data.mmap.key);

    alloc_context_t alloc;
    vmem_context_t vmem;

    mmap_allocate_init(&alloc, &arch_data.mmap);
    vmem_init_vmem(&vmem, &alloc);

    identity_map_mmap(&vmem, &arch_data.mmap);

    set_runtime_address_map(&alloc, &arch_data.mmap);





}
