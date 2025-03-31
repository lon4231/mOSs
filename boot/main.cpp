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


    asm volatile("cli;hlt");

    return 0;
}
