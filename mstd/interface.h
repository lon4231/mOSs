#pragma once

#include "mstd.h"
#include "shared.h"

typedef EFI_STATUS(EFIAPI*KERN_GET_VARIABLE)                                             (IN CHAR16*VariableName,IN KERN_GUID*VendorGuid,OUT UINT32*Attributes OPTIONAL,IN OUT UINTN*DataSize,OUT VOID*Data OPTIONAL);
typedef EFI_STATUS(EFIAPI*KERN_GET_NEXT_VARIABLE_NAME)                                   (IN OUT UINTN*VariableNameSize,IN OUT CHAR16*VariableName,IN OUT KERN_GUID*VendorGuid);
typedef EFI_STATUS(EFIAPI*KERN_SET_VARIABLE)                                             (IN CHAR16*VariableName,IN KERN_GUID*VendorGuid,IN UINT32 Attributes,IN UINTN DataSize,IN VOID*Data);
typedef EFI_STATUS(EFIAPI*KERN_QUERY_VARIABLE_INFO)                                      (IN UINT32 Attributes,OUT UINT64*MaximumVariableStorageSize,OUT UINT64*RemainingVariableStorageSize,OUT UINT64*MaximumVariableSize);
typedef EFI_STATUS(EFIAPI*KERN_GET_TIME)                                                 (OUT KERN_TIME*Time,OUT KERN_TIME_CAPABILITIES*Capabilities OPTIONAL);
typedef EFI_STATUS(EFIAPI*KERN_SET_TIME)                                                 (IN KERN_TIME*Time);
typedef EFI_STATUS(EFIAPI*KERN_GET_WAKEUP_TIME)                                          (OUT BOOLEAN*Enabled,OUT BOOLEAN*Pending,OUT KERN_TIME*Time);
typedef EFI_STATUS(EFIAPI*KERN_SET_WAKEUP_TIME)                                          (IN BOOLEAN Enable,IN KERN_TIME*Time OPTIONAL);
typedef EFI_STATUS(EFIAPI*KERN_SET_VIRTUAL_ADDRESS_MAP)                                  (IN UINTN MemoryMapSize,IN UINTN DescriptorSize,IN UINT32 DescriptorVersion,IN MEMORY_DESCRIPTOR_T*VirtualMap);
typedef EFI_STATUS(EFIAPI*KERN_CONVERT_POINTER)                                          (IN UINTN DebugDisposition,IN VOID**Address);
typedef VOID      (EFIAPI*KERN_RESET_SYSTEM)                                             (IN KERN_RESET_TYPE ResetType,IN EFI_STATUS ResetStatus,IN UINTN DataSize,IN VOID*ResetData OPTIONAL);
typedef EFI_STATUS(EFIAPI*KERN_GET_NEXT_HIGH_MONO_COUNT)                                 (OUT UINT32*HighCount);
typedef EFI_STATUS(EFIAPI*KERN_UPDATE_CAPSULE)                                           (IN KERN_CAPSULE_HEADER**CapsuleHeaderArray,IN UINTN CapsuleCount,OPTIONAL IN EFI_PHYSICAL_ADDRESS ScatterGatherList);
typedef EFI_STATUS(EFIAPI*KERN_QUERY_CAPSULE_CAPABILITIES)                               (IN KERN_CAPSULE_HEADER**CapsuleHeaderArray,IN UINTN CapsuleCount,OUT UINT64*MaximumCapsuleSize,OUT KERN_RESET_TYPE*ResetType);

struct KERN_RUNTIME_SERVICES
{
KERN_TABLE_HEADER                Hdr;
KERN_GET_TIME                    GetTime;
KERN_SET_TIME                    SetTime;
KERN_GET_WAKEUP_TIME             GetWakeupTime;
KERN_SET_WAKEUP_TIME             SetWakeupTime;
KERN_SET_VIRTUAL_ADDRESS_MAP     SetVirtualAddressMap;
KERN_CONVERT_POINTER             ConvertPointer;
KERN_GET_VARIABLE                GetVariable;
KERN_GET_NEXT_VARIABLE_NAME      GetNextVariableName;
KERN_SET_VARIABLE                SetVariable;
KERN_GET_NEXT_HIGH_MONO_COUNT    GetNextHighMonotonicCount;
KERN_RESET_SYSTEM                ResetSystem;
KERN_UPDATE_CAPSULE              UpdateCapsule;
KERN_QUERY_CAPSULE_CAPABILITIES  QueryCapsuleCapabilities;
KERN_QUERY_VARIABLE_INFO         QueryVariableInfo;
};

struct boot_config_t
{
UINT32 gop_mode;
};

struct key_t
{
UINT8 ScanCode;
CHAR16 UnicodeChar;
};

struct keymap_entry_t
{
key_t normal;
key_t shifted;
key_t alt_gr;
UINT8 flags;
};

struct sgi_t
{
UINTN w;
UINTN h;
UINT32*buffer;
};

struct alloc_context_t
{
void*           next_page_address;
UINTN           current_descriptor; 
UINTN           remaining_pages;
MEMORY_MAP_INFO*mmap;
};

struct kernel_args_t
{
MEMORY_MAP_INFO       mmap;
sgi_t                 sgi;
alloc_context_t       alloc_context;
KERN_RUNTIME_SERVICES krs;
xsdp_t*               xsdp;

};
