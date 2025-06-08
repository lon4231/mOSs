#ifndef _EFI_RUNTIME_SERVICES_DEFINED_
#define _EFI_RUNTIME_SERVICES_DEFINED_

#include <efi_types.h>
#include <efi_memory_map.h>

enum EFI_RESET_TYPE
{
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific,
};

struct EFI_TABLE_HEADER
{
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
};

struct EFI_TIME_CAPABILITIES
{
    UINT32 Resolution;
    UINT32 Accuracy;
    BOOLEAN SetsToZero;
};

struct EFI_TIME
{
    UINT16 Year;
    UINT8 Month;
    UINT8 Day;
    UINT8 Hour;
    UINT8 Minute;
    UINT8 Second;
    UINT8 Pad1;
    UINT32 Nanosecond;
    INT16 TimeZone;
    UINT8 Daylight;
    UINT8 Pad2;
};

struct EFI_CAPSULE_HEADER
{
    EFI_GUID CapsuleGuid;
    UINT32 HeaderSize;
    UINT32 Flags;
    UINT32 CapsuleImageSize;
};

struct EFI_CAPSULE_BLOCK_DESCRIPTOR
{
    UINT64 Length;
    union
    {
        EFI_PHYSICAL_ADDRESS DataBlock;
        EFI_PHYSICAL_ADDRESS ContinuationPointer;
    } Union;
};

typedef EFI_STATUS EFI_GET_TIME(OUT EFI_TIME *Time, OUT EFI_TIME_CAPABILITIES *Capabilities OPTIONAL);
typedef EFI_STATUS EFI_SET_TIME(IN EFI_TIME *Time);
typedef EFI_STATUS EFI_GET_WAKEUP_TIME(OUT BOOLEAN *Enabled, OUT BOOLEAN *Pending, OUT EFI_TIME *Time);
typedef EFI_STATUS EFI_SET_WAKEUP_TIME(IN BOOLEAN Enable, IN EFI_TIME *Time OPTIONAL);
typedef EFI_STATUS EFI_SET_VIRTUAL_ADDRESS_MAP(IN UINTN MemoryMapSize, IN UINTN DescriptorSize, IN UINT32 DescriptorVersion, IN EFI_MEMORY_DESCRIPTOR *VirtualMap);
typedef EFI_STATUS EFI_CONVERT_POINTER(IN UINTN DebugDisposition, IN VOID **Address);
typedef EFI_STATUS EFI_GET_VARIABLE(IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid, OUT UINT32 *Attributes OPTIONAL, IN OUT UINTN *DataSize, OUT VOID *Data OPTIONAL);
typedef EFI_STATUS EFI_GET_NEXT_VARIABLE_NAME(IN OUT UINTN *VariableNameSize, IN OUT CHAR16 *VariableName, IN OUT EFI_GUID *VendorGuid);
typedef EFI_STATUS EFI_SET_VARIABLE(IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid, IN UINT32 Attributes, IN UINTN DataSize, IN VOID *Data);
typedef EFI_STATUS EFI_GET_NEXT_HIGH_MONO_COUNT(OUT UINT32 *HighCount);
typedef VOID(EFIAPI *EFI_RESET_SYSTEM)(IN EFI_RESET_TYPE ResetType, IN EFI_STATUS ResetStatus, IN UINTN DataSize, IN VOID *ResetData OPTIONAL);
typedef EFI_STATUS EFI_UPDATE_CAPSULE(IN EFI_CAPSULE_HEADER **CapsuleHeaderArray, IN UINTN CapsuleCount, IN EFI_PHYSICAL_ADDRESS ScatterGatherList OPTIONAL);
typedef EFI_STATUS EFI_QUERY_CAPSULE_CAPABILITIES(IN EFI_CAPSULE_HEADER **CapsuleHeaderArray, IN UINTN CapsuleCount, OUT UINT64 *MaximumCapsuleSize, OUT EFI_RESET_TYPE *ResetType);
typedef EFI_STATUS EFI_QUERY_VARIABLE_INFO(IN UINT32 Attributes, OUT UINT64 *MaximumVariableStorageSize, OUT UINT64 *RemainingVariableStorageSize, OUT UINT64 *MaximumVariableSize);

struct EFI_RUNTIME_SERVICES
{
    EFI_TABLE_HEADER Hdr;
    EFI_GET_TIME GetTime;
    EFI_SET_TIME SetTime;
    EFI_GET_WAKEUP_TIME GetWakeupTime;
    EFI_SET_WAKEUP_TIME SetWakeupTime;
    EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
    EFI_CONVERT_POINTER ConvertPointer;
    EFI_GET_VARIABLE GetVariable;
    EFI_GET_NEXT_VARIABLE_NAME GetNextVariableName;
    EFI_SET_VARIABLE SetVariable;
    EFI_GET_NEXT_HIGH_MONO_COUNT GetNextHighMonotonicCount;
    EFI_RESET_SYSTEM ResetSystem;
    EFI_UPDATE_CAPSULE UpdateCapsule;
    EFI_QUERY_CAPSULE_CAPABILITIES QueryCapsuleCapabilities;
    EFI_QUERY_VARIABLE_INFO QueryVariableInfo;
};

#endif
