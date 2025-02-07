#include "efi.h"
#include "efi_wrapper.h"

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

void*kernel_buffer=nullptr;
UINTN kernel_pages=0;

EFI_FILE_PROTOCOL*kernel_file=open_file(u"\\EFI\\BOOT\\kernel.bin",EFI_FILE_MODE_READ,0);

EFI_FILE_INFO kernel_file_info=get_file_info(kernel_file);

kernel_pages=SIZE_TO_PAGES(kernel_file_info.FileSize)+2;


kernel_file->Close(kernel_file);



asm volatile("cli;hlt");

return 0;
}