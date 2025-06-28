#ifndef _EFI_LOADED_IMAGE_PROTOCOL_DEFINED_
#define _EFI_LOADED_IMAGE_PROTOCOL_DEFINED_

#include <efi/efi_types.h>
#include <efi/efi_boot_services.h>

#define EFI_LOADED_IMAGE_PROTOCOL_GUID {0x5B1B31A1,0x9562, 0x11d2,0x8E, 0x3F,{0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}}

struct EFI_LOADED_IMAGE_PROTOCOL
{
    UINT32 Revision;
    EFI_HANDLE ParentHandle;
    EFI_SYSTEM_TABLE *SystemTable;
    EFI_HANDLE DeviceHandle;
    EFI_DEVICE_PATH_PROTOCOL *FilePath;
    VOID *Reserved;
    UINT32 LoadOptionsSize;
    VOID *LoadOptions;
    VOID *ImageBase;
    UINT64 ImageSize;
    EFI_MEMORY_TYPE ImageCodeType;
    EFI_MEMORY_TYPE ImageDataType;
    EFI_IMAGE_UNLOAD Unload;
};

#endif