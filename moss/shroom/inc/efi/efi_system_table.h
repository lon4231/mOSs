#ifndef _EFI_SYSTEM_TABLE_DEFINED_
#define _EFI_SYSTEM_TABLE_DEFINED_

#include <efi_types.h>
#include <efi_simple_text_input_protocol.h>
#include <efi_simple_text_output_protocol.h>
#include <efi_runtime_services.h>
#include <efi_boot_services.h>

struct EFI_SYSTEM_TABLE;

struct EFI_CONFIGURATION_TABLE
{
    EFI_GUID VendorGuid;
    VOID *VendorTable;
};

struct EFI_SYSTEM_TABLE
{
    EFI_TABLE_HEADER Hdr;
    CHAR16 *FirmwareVendor;
    UINT32 FirmwareRevision;
    EFI_HANDLE ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    EFI_HANDLE StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
    EFI_RUNTIME_SERVICES *RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    UINTN NumberOfTableEntries;
    EFI_CONFIGURATION_TABLE *ConfigurationTable;
};

#endif