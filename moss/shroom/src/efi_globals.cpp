#include "efi_globals.h"

EFI_SYSTEM_TABLE*efi_systab_handle;

EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*efi_cout_handle;
EFI_SIMPLE_TEXT_INPUT_PROTOCOL*efi_cin_handle;

EFI_BOOT_SERVICES*efi_boot_services_handle;
EFI_RUNTIME_SERVICES*efi_runtime_services_handle;

EFI_SIMPLE_FILE_SYSTEM_PROTOCOL efi_fs_protocol_handle;
EFI_HANDLE efi_image_handle;


void init_efi_services(EFI_SYSTEM_TABLE*systab,EFI_HANDLE img_handle)
{
efi_systab_handle=systab;
efi_image_handle=img_handle;

efi_cout_handle=systab->ConOut;
efi_cin_handle=systab->ConIn;

efi_boot_services_handle=systab->BootServices;
efi_runtime_services_handle=systab->RuntimeServices;



}
