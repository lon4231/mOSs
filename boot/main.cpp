#include "efi.h"
#include "efi_wrapper.h"
#include "boot.h"

efi_t *efi = nullptr;
kernel_args_t *kernel_args;
boot_data_t    boot_data;

void efi_init(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *systab)
{
    efi = get_efi_context();

    efi->sys = systab;
    efi->cout = systab->ConOut;
    efi->bs = systab->BootServices;
    efi->rs = systab->RuntimeServices;
    efi->img_handle = img_handle;

    efi->loaded_image = (EFI_LOADED_IMAGE_PROTOCOL *)open_protocol(img_handle, EFI_LOADED_IMAGE_PROTOCOL_GUID, img_handle, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    efi->filesys = (EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *)open_protocol(efi->loaded_image->DeviceHandle, EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, img_handle, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    efi->gop = (EFI_GRAPHICS_OUTPUT_PROTOCOL*)locate_protocol(EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID);

    efi->cout->ClearScreen(efi->cout);
}

extern "C" EFIAPI EFI_STATUS emain(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *systab)
{
    efi_init(img_handle, systab);

    printf(u"SHROOM BOOT V1.2\r\n");
    printf(u"firm vendor: %s\r\n", systab->FirmwareVendor);
    printf(u"firm revision: 0x%x\r\n", systab->FirmwareRevision);

    kernel_args = (kernel_args_t *)alloc_pages(SIZE_TO_PAGES(sizeof(kernel_args_t)), EfiLoaderData);
    memset(kernel_args, 0, sizeof(kernel_args_t));

    EFI_FILE_PROTOCOL *kernel_file = open_file(u"\\EFI\\BOOT\\KERNEL.BIN", EFI_FILE_MODE_READ, 0);
    EFI_FILE_INFO kernel_file_info = get_file_info(kernel_file);

    kernel_args->kernel_bin = alloc_pages(SIZE_TO_PAGES(kernel_file_info.FileSize) + KERNEL_BSS_SIZE, EfiLoaderData);
    kernel_args->kernel_bin_pages = SIZE_TO_PAGES(kernel_file_info.FileSize) + KERNEL_BSS_SIZE;

    kernel_args->kernel_stack = alloc_pages(KERNEL_STACK_PAGES, EfiLoaderData);

    kernel_file->Read(kernel_file, &kernel_file_info.FileSize, kernel_args->kernel_bin);

    for (UINTN i = 0; i < efi->sys->NumberOfTableEntries; ++i)
    {
        EFI_CONFIGURATION_TABLE *config_table = efi->sys->ConfigurationTable + i;
        if ((strncmp((char *)config_table->VendorTable, "RSD PTR ", 8) == 0) && (((xsdp_t *)config_table->VendorTable)->Revision > 0))
        {
            kernel_args->xsdp = (xsdp_t *)config_table->VendorTable;
        }
    }

    get_mmap(&kernel_args->mmap);

    UINTN usable_memory = 0;

    for (UINTN i = 0; i < (kernel_args->mmap.size / kernel_args->mmap.desc_size); ++i)
    {
        mmap_mem_desc_t *desc = (mmap_mem_desc_t *)(((UINT8 *)kernel_args->mmap.map) + (i * kernel_args->mmap.desc_size));

        if (desc->Type == EfiConventionalMemory)
        {
            usable_memory += desc->NumberOfPages;
        }
    }

    printf(u"ACPI revision: %s\r\n", (kernel_args->xsdp->Revision > 0) ? u"2.0" : u"1.0");

    printf(u"usable memory: %d MiB\r\n", (usable_memory * PAGE_SIZE) / 0x100000);

    efi->bs->ExitBootServices(efi->img_handle, kernel_args->mmap.key);




    boot_to_kernel(kernel_args,&boot_data);

    asm volatile("cli;hlt");

    return 0;
}
