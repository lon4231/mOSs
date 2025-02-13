#include "efi.h"
#include "efi_wrapper.h"
#include "boot.h"

void efi_init(EFI_HANDLE img_handle,EFI_SYSTEM_TABLE*systab)
{
efi.sys=systab;
efi.cout=systab->ConOut;
efi.bs=systab->BootServices;
efi.rs=systab->RuntimeServices;
efi.img_handle=img_handle;

efi.loaded_image=(EFI_LOADED_IMAGE_PROTOCOL*)open_protocol(img_handle,EFI_LOADED_IMAGE_PROTOCOL_GUID,img_handle,NULL,EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
efi.filesys=(EFI_SIMPLE_FILE_SYSTEM_PROTOCOL*)open_protocol(efi.loaded_image->DeviceHandle,EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID,img_handle,NULL,EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);

efi.cout->ClearScreen(efi.cout);
}


extern "C" EFIAPI EFI_STATUS emain(EFI_HANDLE img_handle,EFI_SYSTEM_TABLE*systab)
{
efi_init(img_handle,systab);

printf(u"SHROOM BOOT V1.1\r\n");
printf(u"firm vendor: %s\r\n",systab->FirmwareVendor);
printf(u"firm revision: %x\r\n",systab->FirmwareRevision);

boot_handle_t boot_handle=setup_boot_handle();

exit_bootloader(&boot_handle);


asm volatile("cli;hlt");

return 0;
}