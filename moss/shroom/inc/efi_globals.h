#ifndef _EFI_GLOBALS_DEFINED_
#define _EFI_GLOBALS_DEFINED_

#include <efi/efi.h>

extern EFI_SYSTEM_TABLE *efi_systab_handle;
extern EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *efi_cout_handle;
extern EFI_SIMPLE_TEXT_INPUT_PROTOCOL *efi_cin_handle;

extern EFI_BOOT_SERVICES *efi_boot_services_handle;
extern EFI_RUNTIME_SERVICES *efi_runtime_services_handle;

extern EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *efi_fs_protocol_handle;
extern EFI_HANDLE efi_image_handle;


extern UINTN efi_graphics_output_protocol_count;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL **efi_graphics_output_protocol_handles;

void init_efi_services(EFI_SYSTEM_TABLE *systab, EFI_HANDLE img_handle);

#endif