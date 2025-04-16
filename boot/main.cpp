#include "efi.h"
#include "efi_wrapper.h"

efi_t *efi = nullptr;

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
    efi->gop = (EFI_GRAPHICS_OUTPUT_PROTOCOL *)locate_protocol(EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID);

    efi->cout->ClearScreen(efi->cout);
}

extern "C" EFIAPI EFI_STATUS emain(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *systab)
{
    efi_init(img_handle, systab);

    printf(u"SHROOM_BOOT V1.3\r\n");
    printf(u"FIRMWARE_VENDOR: %s\r\n", systab->FirmwareVendor);
    printf(u"FIRMWARE_REVISION: %llx\r\n", systab->FirmwareRevision);

    EFI_FILE_PROTOCOL *kernel_file = open_file(u"\\EFI\\BOOT\\KERNEL.BIN", EFI_FILE_MODE_READ, 0);
    EFI_FILE_INFO kernel_file_info = get_file_info(kernel_file);

    printf(u"KERNEL_SIZE: %d KiB\r\n\n", kernel_file_info.FileSize / 1024);

    xsdp_t *xsdp = nullptr;
    for (UINTN i = 0; i < systab->NumberOfTableEntries; ++i)
    {
        if (memcmp(systab->ConfigurationTable[i].VendorTable, (void *)"RSD PTR ", 8) == 0)
        {
            if (xsdp == nullptr)
            {
                xsdp = (xsdp_t *)systab->ConfigurationTable[i].VendorTable;
                printf(u"XSDP FOUND WITH REVISION: %d\r\n",xsdp->Revision);
            }
            else
            {
                if (((xsdp_t *)systab->ConfigurationTable[i].VendorTable)->Revision > xsdp->Revision)
                {
                    xsdp=(xsdp_t *)systab->ConfigurationTable[i].VendorTable;
                    printf(u"NEWER XSDP FOUND WITH REVISION: %d\r\n",xsdp->Revision);
                }
            }
        }
    }
    
    


    asm volatile("cli;hlt");
    return 0;
}
