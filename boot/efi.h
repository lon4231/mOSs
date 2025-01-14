#pragma once

#include "std_types.h"

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID                   {0x09042a9de,0x23dc,0x4a38,0x96,0xfb,0x7a,0xde,0xd0,0x80,0x51,0x6a}
#define EFI_SIMPLE_POINTER_PROTOCOL_GUID                    {0x031878c87,0x0b75,0x11d5,0x9a,0x4f,0x00,0x90,0x27,0x3f,0xc1,0x4d}
#define EFI_ABSOLUTE_POINTER_PROTOCOL_GUID                  {0x08D59D32B,0xC655,0x4AE9,0x9B,0x15,0xF2,0x59,0x04,0x99,0x2A,0x43}
#define EFI_LOADED_IMAGE_PROTOCOL_GUID                      {0x05B1B31A1,0x9562,0x11d2,0x8E,0x3F,0x00,0xA0,0xC9,0x69,0x72,0x3B}
#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID                {0x0964e5b22,0x6459,0x11d2,0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}
#define EFI_FILE_INFO_ID                                    {0x009576e92,0x6d3f,0x11d2,0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}
#define EFI_FILE_SYSTEM_INFO_ID                             {0x009576e93,0x6d3f,0x11d2,0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}
#define EFI_BLOCK_IO_PROTOCOL_GUID                          {0x0964e5b21,0x6459,0x11d2,0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}
#define EFI_DISK_IO_PROTOCOL_GUID                           {0x0CE345171,0xBA0B,0x11d2,0x8e,0x4F,0x00,0xa0,0xc9,0x69,0x72,0x3b}
#define EFI_PARTITION_INFO_PROTOCOL_GUID                    {0x08cf2f62c,0xbc9b,0x4821,0x80,0x8d,0xec,0x9e,0xc4,0x21,0xa1,0xa0}
#define EFI_GLOBAL_VARIABLE_GUID                            {0x08BE4DF61,0x93CA,0x11d2,0xAA,0x0D,0x00,0xE0,0x98,0x03,0x2B,0x8C}
#define EFI_DEVICE_PATH_PROTOCOL_GUID                       {0x009576e91,0x6d3f,0x11d2,0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}
#define EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID               {0x08b843e20,0x8132,0x4852,0x90,0xcc,0x55,0x1a,0x4e,0x4a,0x7f,0x1c}
#define EFI_ACPI_TABLE_GUID                                 {0x08868e871,0xe4f1,0x11d3,0xbc,0x22,0x00,0x80,0xc7,0x3c,0x88,0x81}
#define ACPI_TABLE_GUID                                     {0x0eb9d2d30,0x2d88,0x11d3,0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}
#define SAL_SYSTEM_TABLE_GUID                               {0x0eb9d2d32,0x2d88,0x11d3,0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}
#define SMBIOS_TABLE_GUID                                   {0x0eb9d2d31,0x2d88,0x11d3,0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}
#define SMBIOS3_TABLE_GUID                                  {0x0f2fd1544,0x9794,0x4a2c,0x99,0x2e,0xe5,0xbb,0xcf,0x20,0xe3,0x94}
#define MPS_TABLE_GUID                                      {0x0eb9d2d2f,0x2d88,0x11d3,0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}
#define ESP_GUID                                            {0x0C12A7328,0xF81F,0x11D2,0xBA,0x4B,0x00,0xA0,0xC9,0x3E,0xC9,0x3B}
#define BASIC_DATA_GUID                                     {0x0EBD0A0A2,0xB9E5,0x4433,0x87,0xC0,0x68,0xB6,0xB7,0x26,0x99,0xC7}
#define ACPI_10_TABLE_GUID ACPI_TABLE_GUID
#define EFI_ACPI_20_TABLE_GUID                              EFI_ACPI_TABLE_GUID


#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL  0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL        0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL       0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER           0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE           0x00000020

#define EFI_FILE_MODE_READ   0x0000000000000001
#define EFI_FILE_MODE_WRITE  0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

#define EFI_FILE_READ_ONLY  0x0000000000000001
#define EFI_FILE_HIDDEN     0x0000000000000002
#define EFI_FILE_SYSTEM     0x0000000000000004
#define EFI_FILE_RESERVED   0x0000000000000008
#define EFI_FILE_DIRECTORY  0x0000000000000010
#define EFI_FILE_ARCHIVE    0x0000000000000020
#define EFI_FILE_VALID_ATTR 0x0000000000000037

#define EFI_MEMORY_UC            0x0000000000000001
#define EFI_MEMORY_WC            0x0000000000000002
#define EFI_MEMORY_WT            0x0000000000000004
#define EFI_MEMORY_WB            0x0000000000000008
#define EFI_MEMORY_UCE           0x0000000000000010
#define EFI_MEMORY_WP            0x0000000000001000
#define EFI_MEMORY_RP            0x0000000000002000
#define EFI_MEMORY_XP            0x0000000000004000
#define EFI_MEMORY_NV            0x0000000000008000
#define EFI_MEMORY_MORE_RELIABLE 0x0000000000010000
#define EFI_MEMORY_RO            0x0000000000020000
#define EFI_MEMORY_SP            0x0000000000040000
#define EFI_MEMORY_CPU_CRYPTO    0x0000000000080000
#define EFI_MEMORY_RUNTIME       0x8000000000000000
#define EFI_MEMORY_ISA_VALID     0x4000000000000000
#define EFI_MEMORY_ISA_MASK      0x0FFFF00000000000

struct EFI_GUID;
struct EFI_TABLE_HEADER;
struct EFI_SYSTEM_TABLE;
struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
struct SIMPLE_TEXT_OUTPUT_MODE;
struct EFI_RUNTIME_SERVICES;
struct EFI_BOOT_SERVICES;
struct EFI_CONFIGURATION_TABLE;
struct EFI_INPUT_KEY;
struct EFI_MEMORY_DESCRIPTOR;
struct EFI_CAPSULE_TABLE;
struct EFI_CAPSULE_HEADER;
struct EFI_TIME_CAPABILITIES;
struct EFI_TIME;
struct EFI_CAPSULE_BLOCK_DESCRIPTOR;
struct EFI_SIMPLE_POINTER_PROTOCOL;
struct EFI_SIMPLE_POINTER_STATE;
struct EFI_SIMPLE_POINTER_MODE;
struct EFI_GRAPHICS_OUTPUT_PROTOCOL;
struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;
struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;
struct EFI_PIXEL_BITMASK;
struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL;
struct EFI_DEVICE_PATH_PROTOCOL;
struct EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;
struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;
struct EFI_FILE_PROTOCOL;
struct EFI_FILE_IO_TOKEN;

enum EFI_RESET_TYPE
{
EfiResetCold,
EfiResetWarm,
EfiResetShutdown,
EfiResetPlatformSpecific
};

enum EFI_GRAPHICS_PIXEL_FORMAT
{
PixelRedGreenBlueReserved8BitPerColor,
PixelBlueGreenRedReserved8BitPerColor,
PixelBitMask,
PixelBltOnly,
PixelFormatMax
};

enum EFI_GRAPHICS_OUTPUT_BLT_OPERATION
{
EfiBltVideoFill,
EfiBltVideoToBltBuffer,
EfiBltBufferToVideo,
EfiBltVideoToVideo,
EfiGraphicsOutputBltOperationMax
};

enum EFI_TIMER_DELAY
{
TimerCancel,
TimerPeriodic,
TimerRelative
};

enum EFI_ALLOCATE_TYPE 
{
AllocateAnyPages,
AllocateMaxAddress,
AllocateAddress,
MaxAllocateType
};

enum EFI_MEMORY_TYPE 
{
EfiReservedMemoryType,
EfiLoaderCode,
EfiLoaderData,
EfiBootServicesCode,
EfiBootServicesData,
EfiRuntimeServicesCode,
EfiRuntimeServicesData,
EfiConventionalMemory,
EfiUnusableMemory,
EfiACPIReclaimMemory,
EfiACPIMemoryNVS,
EfiMemoryMappedIO,
EfiMemoryMappedIOPortSpace,
EfiPalCode,
EfiPersistentMemory,
EfiUnacceptedMemoryType,
EfiMaxMemoryType
};

enum EFI_INTERFACE_TYPE
{
EFI_NATIVE_INTERFACE
};

enum EFI_LOCATE_SEARCH_TYPE
{
AllHandles,
ByRegisterNotify,
ByProtocol
};


typedef EFI_STATUS(EFIAPI*EFI_INPUT_RESET)                                              (IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL*This,IN BOOLEAN ExtendedVerification);
typedef EFI_STATUS(EFIAPI*EFI_INPUT_READ_KEY)                                           (IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL*This,OUT EFI_INPUT_KEY*Key);
typedef EFI_STATUS(EFIAPI*EFI_TEXT_RESET)                                               (IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*This,IN BOOLEAN ExtendedVerification);
typedef EFI_STATUS(EFIAPI*EFI_TEXT_STRING)                                              (IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*This,IN CHAR16*String);
typedef EFI_STATUS(EFIAPI*EFI_TEXT_TEST_STRING)                                         (IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*This,IN CHAR16*String);
typedef EFI_STATUS(EFIAPI*EFI_TEXT_QUERY_MODE)                                          (IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*This,IN UINTN ModeNumber,OUT UINTN*Columns,OUT UINTN*Rows);
typedef EFI_STATUS(EFIAPI*EFI_TEXT_SET_MODE)                                            (IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*This,IN UINTN ModeNumber);
typedef EFI_STATUS(EFIAPI*EFI_TEXT_SET_ATTRIBUTE)                                       (IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*This,IN UINTN Attribute);
typedef EFI_STATUS(EFIAPI*EFI_TEXT_CLEAR_SCREEN)                                        (IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*This);
typedef EFI_STATUS(EFIAPI*EFI_TEXT_SET_CURSOR_POSITION)                                 (IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*This,IN UINTN Column,IN UINTN Row);
typedef EFI_STATUS(EFIAPI*EFI_TEXT_ENABLE_CURSOR)                                       (IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*This,IN BOOLEAN Visible);
typedef EFI_STATUS(EFIAPI*EFI_GET_VARIABLE)                                             (IN CHAR16*VariableName,IN EFI_GUID*VendorGuid,OUT UINT32*Attributes OPTIONAL,IN OUT UINTN*DataSize,OUT VOID*Data OPTIONAL);
typedef EFI_STATUS(EFIAPI*EFI_GET_NEXT_VARIABLE_NAME)                                   (IN OUT UINTN*VariableNameSize,IN OUT CHAR16*VariableName,IN OUT EFI_GUID*VendorGuid);
typedef EFI_STATUS(EFIAPI*EFI_SET_VARIABLE)                                             (IN CHAR16*VariableName,IN EFI_GUID*VendorGuid,IN UINT32 Attributes,IN UINTN DataSize,IN VOID*Data);
typedef EFI_STATUS(EFIAPI*EFI_QUERY_VARIABLE_INFO)                                      (IN UINT32 Attributes,OUT UINT64*MaximumVariableStorageSize,OUT UINT64*RemainingVariableStorageSize,OUT UINT64*MaximumVariableSize);
typedef EFI_STATUS(EFIAPI*EFI_GET_TIME)                                                 (OUT EFI_TIME*Time,OUT EFI_TIME_CAPABILITIES*Capabilities OPTIONAL);
typedef EFI_STATUS(EFIAPI*EFI_SET_TIME)                                                 (IN EFI_TIME*Time);
typedef EFI_STATUS(EFIAPI*EFI_GET_WAKEUP_TIME)                                          (OUT BOOLEAN*Enabled,OUT BOOLEAN*Pending,OUT EFI_TIME*Time);
typedef EFI_STATUS(EFIAPI*EFI_SET_WAKEUP_TIME)                                          (IN BOOLEAN Enable,IN EFI_TIME*Time OPTIONAL);
typedef EFI_STATUS(EFIAPI*EFI_SET_VIRTUAL_ADDRESS_MAP)                                  (IN UINTN MemoryMapSize,IN UINTN DescriptorSize,IN UINT32 DescriptorVersion,IN EFI_MEMORY_DESCRIPTOR*VirtualMap);
typedef EFI_STATUS(EFIAPI*EFI_CONVERT_POINTER)                                          (IN UINTN DebugDisposition,IN VOID**Address);
typedef VOID      (EFIAPI*EFI_RESET_SYSTEM)                                             (IN EFI_RESET_TYPE ResetType,IN EFI_STATUS ResetStatus,IN UINTN DataSize,IN VOID*ResetData OPTIONAL);
typedef EFI_STATUS(EFIAPI*EFI_GET_NEXT_HIGH_MONO_COUNT)                                 (OUT UINT32*HighCount);
typedef EFI_STATUS(EFIAPI*EFI_UPDATE_CAPSULE)                                           (IN EFI_CAPSULE_HEADER**CapsuleHeaderArray,IN UINTN CapsuleCount,OPTIONAL IN EFI_PHYSICAL_ADDRESS ScatterGatherList);
typedef EFI_STATUS(EFIAPI*EFI_QUERY_CAPSULE_CAPABILITIES)                               (IN EFI_CAPSULE_HEADER**CapsuleHeaderArray,IN UINTN CapsuleCount,OUT UINT64*MaximumCapsuleSize,OUT EFI_RESET_TYPE*ResetType);
typedef EFI_STATUS(EFIAPI*EFI_SIMPLE_POINTER_RESET)                                     (IN EFI_SIMPLE_POINTER_PROTOCOL*This,IN BOOLEAN ExtendedVerification);
typedef EFI_STATUS(EFIAPI*EFI_SIMPLE_POINTER_GET_STATE)                                 (IN EFI_SIMPLE_POINTER_PROTOCOL*This,OUT EFI_SIMPLE_POINTER_STATE*State);
typedef EFI_STATUS(EFIAPI*EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE)                      (IN EFI_GRAPHICS_OUTPUT_PROTOCOL*This,IN UINT32 ModeNumber,OUT UINTN*SizeOfInfo,OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION**Info);
typedef EFI_STATUS(EFIAPI*EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE)                        (IN EFI_GRAPHICS_OUTPUT_PROTOCOL*This,IN UINT32 ModeNumber);
typedef EFI_STATUS(EFIAPI*EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT)                             (IN EFI_GRAPHICS_OUTPUT_PROTOCOL*This,IN OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL*BltBuffer,OPTIONAL IN EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation,IN UINTN SourceX,IN UINTN SourceY,IN UINTN DestinationX,IN UINTN DestinationY,IN UINTN Width,IN UINTN Height,IN UINTN Delta OPTIONAL);
typedef VOID      (EFIAPI*EFI_EVENT_NOTIFY)                                             (IN EFI_EVENT Event,IN VOID*Context);
typedef EFI_STATUS(EFIAPI*EFI_CREATE_EVENT)                                             (IN UINT32 Type,IN EFI_TPL NotifyTpl,IN EFI_EVENT_NOTIFY NotifyFunction,OPTIONAL IN VOID*NotifyContext,OPTIONAL OUT EFI_EVENT*Event);
typedef EFI_STATUS(EFIAPI*EFI_CREATE_EVENT_EX)                                          (IN UINT32 Type,IN EFI_TPL NotifyTpl,IN EFI_EVENT_NOTIFY NotifyFunction OPTIONAL,IN CONST VOID*NotifyContext OPTIONAL,IN CONST EFI_GUID*EventGroup OPTIONAL,OUT EFI_EVENT*Event);
typedef EFI_STATUS(EFIAPI*EFI_CLOSE_EVENT)                                              (IN EFI_EVENT Event);
typedef EFI_STATUS(EFIAPI*EFI_SIGNAL_EVENT)                                             (IN EFI_EVENT Event);
typedef EFI_STATUS(EFIAPI*EFI_WAIT_FOR_EVENT)                                           (IN UINTN NumberOfEvents,IN EFI_EVENT*Event,OUT UINTN*Index);
typedef EFI_STATUS(EFIAPI*EFI_CHECK_EVENT)                                              (IN EFI_EVENT Event);
typedef EFI_STATUS(EFIAPI*EFI_SET_TIMER)                                                (IN EFI_EVENT Event,IN EFI_TIMER_DELAY Type,IN UINT64 TriggerTime);
typedef EFI_TPL   (EFIAPI*EFI_RAISE_TPL)                                                (IN EFI_TPL NewTpl);
typedef VOID      (EFIAPI*EFI_RESTORE_TPL)                                              (IN EFI_TPL OldTpl);
typedef EFI_STATUS(EFIAPI*EFI_ALLOCATE_PAGES)                                           (IN EFI_ALLOCATE_TYPE Type,IN EFI_MEMORY_TYPE MemoryType,IN UINTN Pages,IN OUT EFI_PHYSICAL_ADDRESS*Memory);
typedef EFI_STATUS(EFIAPI*EFI_FREE_PAGES)                                               (IN EFI_PHYSICAL_ADDRESS Memory,IN UINTN Pages);
typedef EFI_STATUS(EFIAPI*EFI_GET_MEMORY_MAP)                                           (IN OUT UINTN*MemoryMapSize,OUT EFI_MEMORY_DESCRIPTOR*MemoryMap,OUT UINTN*MapKey,OUT UINTN*DescriptorSize,OUT UINT32*DescriptorVersion); 
typedef EFI_STATUS(EFIAPI*EFI_ALLOCATE_POOL)                                            (IN EFI_MEMORY_TYPE PoolType,IN UINTN Size,OUT VOID**Buffer);
typedef EFI_STATUS(EFIAPI*EFI_FREE_POOL)                                                (IN VOID*Buffer);
typedef EFI_STATUS(EFIAPI*EFI_INSTALL_PROTOCOL_INTERFACE)                               (IN OUT EFI_HANDLE*Handle,IN EFI_GUID*Protocol,IN EFI_INTERFACE_TYPE InterfaceType,IN VOID*Interface);
typedef EFI_STATUS(EFIAPI*EFI_UNINSTALL_PROTOCOL_INTERFACE)                             (IN EFI_HANDLE Handle,IN EFI_GUID*Protocol,IN VOID*Interface);
typedef EFI_STATUS(EFIAPI*EFI_REINSTALL_PROTOCOL_INTERFACE)                             (IN EFI_HANDLE Handle,IN EFI_GUID*Protocol,IN VOID*OldInterface,IN VOID*NewInterface);
typedef EFI_STATUS(EFIAPI*EFI_REGISTER_PROTOCOL_NOTIFY)                                 (IN EFI_GUID*Protocol,IN EFI_EVENT Event,OUT VOID**Registration);
typedef EFI_STATUS(EFIAPI*EFI_LOCATE_HANDLE)                                            (IN EFI_LOCATE_SEARCH_TYPE SearchType,IN EFI_GUID*Protocol OPTIONAL,IN VOID*SearchKey OPTIONAL,IN OUT UINTN*BufferSize,OUT EFI_HANDLE*Buffer);
typedef EFI_STATUS(EFIAPI*EFI_HANDLE_PROTOCOL)                                          (IN EFI_HANDLE Handle,IN EFI_GUID*Protocol,OUT VOID**Interface);
typedef EFI_STATUS(EFIAPI*EFI_LOCATE_DEVICE_PATH)                                       (IN EFI_GUID*Protocol,IN OUT EFI_DEVICE_PATH_PROTOCOL**DevicePath,OUT EFI_HANDLE*Device);
typedef EFI_STATUS(EFIAPI*EFI_OPEN_PROTOCOL)                                            (IN EFI_HANDLE Handle,IN EFI_GUID*Protocol,OUT VOID**Interface OPTIONAL,IN EFI_HANDLE AgentHandle,IN EFI_HANDLE ControllerHandle,IN UINT32 Attributes);
typedef EFI_STATUS(EFIAPI*EFI_CLOSE_PROTOCOL)                                           (IN EFI_HANDLE Handle,IN EFI_GUID*Protocol,IN EFI_HANDLE AgentHandle,IN EFI_HANDLE ControllerHandle);
typedef EFI_STATUS(EFIAPI*EFI_OPEN_PROTOCOL_INFORMATION)                                (IN EFI_HANDLE Handle,IN EFI_GUID*Protocol,OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY**EntryBuffer,OUT UINTN*EntryCount);
typedef EFI_STATUS(EFIAPI*EFI_CONNECT_CONTROLLER)                                       (IN EFI_HANDLE ControllerHandle,IN EFI_HANDLE*DriverImageHandle OPTIONAL,IN EFI_DEVICE_PATH_PROTOCOL*RemainingDevicePath OPTIONAL,IN BOOLEAN Recursive);
typedef EFI_STATUS(EFIAPI*EFI_DISCONNECT_CONTROLLER)                                    (IN EFI_HANDLE ControllerHandle,IN EFI_HANDLE DriverImageHandle OPTIONAL,IN EFI_HANDLE ChildHandle OPTIONAL);
typedef EFI_STATUS(EFIAPI*EFI_PROTOCOLS_PER_HANDLE)                                     (IN EFI_HANDLE Handle,OUT EFI_GUID***ProtocolBuffer,OUT UINTN*ProtocolBufferCount);
typedef EFI_STATUS(EFIAPI*EFI_LOCATE_HANDLE_BUFFER)                                     (IN EFI_LOCATE_SEARCH_TYPE SearchType,IN EFI_GUID*Protocol OPTIONAL,IN VOID*SearchKey OPTIONAL,OUT UINTN*NoHandles,OUT EFI_HANDLE**Buffer);
typedef EFI_STATUS(EFIAPI*EFI_LOCATE_PROTOCOL)                                          (IN EFI_GUID*Protocol,IN VOID*Registration OPTIONAL,OUT VOID**Interface);
typedef EFI_STATUS(EFIAPI*EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)                     (IN OUT EFI_HANDLE*Handle,...);
typedef EFI_STATUS(EFIAPI*EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)                   (IN EFI_HANDLE Handle,...);
typedef EFI_STATUS(EFIAPI*EFI_IMAGE_LOAD)                                               (IN BOOLEAN BootPolicy,IN EFI_HANDLE ParentImageHandle,IN EFI_DEVICE_PATH_PROTOCOL*DevicePath OPTIONAL,IN VOID*SourceBuffer OPTIONAL,IN UINTN SourceSize,OUT EFI_HANDLE*ImageHandle);
typedef EFI_STATUS(EFIAPI*EFI_IMAGE_START)                                              (IN EFI_HANDLE ImageHandle,OUT UINTN*ExitDataSize,OUT CHAR16**ExitData OPTIONAL);
typedef EFI_STATUS(EFIAPI*EFI_IMAGE_UNLOAD)                                             (IN EFI_HANDLE ImageHandle);
typedef EFI_STATUS(EFIAPI*EFI_IMAGE_ENTRY_POINT)                                        (IN EFI_HANDLE ImageHandle,IN EFI_SYSTEM_TABLE*SystemTable);
typedef EFI_STATUS(EFIAPI*EFI_EXIT)                                                     (IN EFI_HANDLE ImageHandle,IN EFI_STATUS ExitStatus,IN UINTN ExitDataSize,IN CHAR16*ExitData OPTIONAL);
typedef EFI_STATUS(EFIAPI*EFI_EXIT_BOOT_SERVICES)                                       (IN EFI_HANDLE ImageHandle,IN UINTN MapKey);
typedef EFI_STATUS(EFIAPI*EFI_SET_WATCHDOG_TIMER)                                       (IN UINTN Timeout,IN UINT64 WatchdogCode,IN UINTN DataSize,IN CHAR16*WatchdogData OPTIONAL);
typedef EFI_STATUS(EFIAPI*EFI_STALL)                                                    (IN UINTN Microseconds);
typedef VOID      (EFIAPI*EFI_COPY_MEM)                                                 (IN VOID*Destination,IN VOID*Source,IN UINTN Length);
typedef VOID      (EFIAPI*EFI_SET_MEM)                                                  (IN VOID*Buffer,IN UINTN Size,IN UINT8 Value);
typedef EFI_STATUS(EFIAPI*EFI_GET_NEXT_MONOTONIC_COUNT)                                 (OUT UINT64*Count);
typedef EFI_STATUS(EFIAPI*EFI_INSTALL_CONFIGURATION_TABLE)                              (IN EFI_GUID*Guid,IN VOID*Table);
typedef EFI_STATUS(EFIAPI*EFI_CALCULATE_CRC32)                                          (IN VOID*Data,IN UINTN DataSize,OUT UINT32*Crc32);
typedef EFI_STATUS(EFIAPI*EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME)                  (IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL*This,OUT EFI_FILE_PROTOCOL**Root);
typedef EFI_STATUS(EFIAPI*EFI_FILE_OPEN)                                                (IN EFI_FILE_PROTOCOL*This,OUT EFI_FILE_PROTOCOL**NewHandle,IN CHAR16*FileName,IN UINT64 OpenMode,IN UINT64 Attributes);
typedef EFI_STATUS(EFIAPI*EFI_FILE_CLOSE)                                               (IN EFI_FILE_PROTOCOL*This);
typedef EFI_STATUS(EFIAPI*EFI_FILE_DELETE)                                              (IN EFI_FILE_PROTOCOL*This);
typedef EFI_STATUS(EFIAPI*EFI_FILE_READ)                                                (IN EFI_FILE_PROTOCOL*This,IN OUT UINTN*BufferSize,OUT VOID*Buffer);
typedef EFI_STATUS(EFIAPI*EFI_FILE_WRITE)                                               (IN EFI_FILE_PROTOCOL*This,IN OUT UINTN*BufferSize,IN VOID*Buffer);
typedef EFI_STATUS(EFIAPI*EFI_FILE_OPEN_EX)                                             (IN EFI_FILE_PROTOCOL*This,OUT EFI_FILE_PROTOCOL**NewHandle,IN CHAR16*FileName,IN UINT64 OpenMode,IN UINT64 Attributes,IN OUT EFI_FILE_IO_TOKEN*Token);
typedef EFI_STATUS(EFIAPI*EFI_FILE_READ_EX)                                             (IN EFI_FILE_PROTOCOL*This,IN OUT EFI_FILE_IO_TOKEN*Token);
typedef EFI_STATUS(EFIAPI*EFI_FILE_WRITE_EX)                                            (IN EFI_FILE_PROTOCOL*This,IN OUT EFI_FILE_IO_TOKEN*Token);
typedef EFI_STATUS(EFIAPI*EFI_FILE_FLUSH_EX)                                            (IN EFI_FILE_PROTOCOL*This,IN OUT EFI_FILE_IO_TOKEN*Token);
typedef EFI_STATUS(EFIAPI*EFI_FILE_SET_POSITION)                                        (IN EFI_FILE_PROTOCOL*This,IN UINT64 Position);
typedef EFI_STATUS(EFIAPI*EFI_FILE_GET_POSITION)                                        (IN EFI_FILE_PROTOCOL*This,OUT UINT64*Position);
typedef EFI_STATUS(EFIAPI*EFI_FILE_GET_INFO)                                            (IN EFI_FILE_PROTOCOL*This,IN EFI_GUID*InformationType,IN OUT UINTN*BufferSize,OUT VOID*Buffer);
typedef EFI_STATUS(EFIAPI*EFI_FILE_SET_INFO)                                            (IN EFI_FILE_PROTOCOL*This,IN EFI_GUID*InformationType,IN UINTN BufferSize,IN VOID*Buffer);
typedef EFI_STATUS(EFIAPI*EFI_FILE_FLUSH)                                               (IN EFI_FILE_PROTOCOL*This);



struct EFI_GUID
{
UINT32 TimeLow;
UINT16 TimeMid;
UINT16 TimeHighAndVersion;
UINT8  ClockSeqHighAndReserved;
UINT8  ClockSeqLow;
UINT8  Node[6];
}__attribute__((packed));

struct EFI_TABLE_HEADER
{
UINT64 Signature;
UINT32 Revision;
UINT32 HeaderSize;
UINT32 CRC32;
UINT32 Reserved;
};

struct EFI_SYSTEM_TABLE
{
EFI_TABLE_HEADER                        Hdr;
CHAR16*                                 FirmwareVendor;
UINT32                                  FirmwareRevision;
EFI_HANDLE                              ConsoleInHandle;
EFI_SIMPLE_TEXT_INPUT_PROTOCOL*         ConIn;
EFI_HANDLE                              ConsoleOutHandle;
EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*        ConOut;
EFI_HANDLE                              StandardErrorHandle;
EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*        StdErr;
EFI_RUNTIME_SERVICES*                   RuntimeServices;
EFI_BOOT_SERVICES*                      BootServices;
UINTN                                   NumberOfTableEntries;
EFI_CONFIGURATION_TABLE*                ConfigurationTable;
};

struct EFI_RUNTIME_SERVICES
{
EFI_TABLE_HEADER                Hdr;
EFI_GET_TIME                    GetTime;
EFI_SET_TIME                    SetTime;
EFI_GET_WAKEUP_TIME             GetWakeupTime;
EFI_SET_WAKEUP_TIME             SetWakeupTime;
EFI_SET_VIRTUAL_ADDRESS_MAP     SetVirtualAddressMap;
EFI_CONVERT_POINTER             ConvertPointer;
EFI_GET_VARIABLE                GetVariable;
EFI_GET_NEXT_VARIABLE_NAME      GetNextVariableName;
EFI_SET_VARIABLE                SetVariable;
EFI_GET_NEXT_HIGH_MONO_COUNT    GetNextHighMonotonicCount;
EFI_RESET_SYSTEM                ResetSystem;
EFI_UPDATE_CAPSULE              UpdateCapsule;
EFI_QUERY_CAPSULE_CAPABILITIES  QueryCapsuleCapabilities;
EFI_QUERY_VARIABLE_INFO         QueryVariableInfo;
};

struct EFI_BOOT_SERVICES
{
EFI_TABLE_HEADER                            Hdr;
EFI_RAISE_TPL                               RaiseTPL;
EFI_RESTORE_TPL                             RestoreTPL;
EFI_ALLOCATE_PAGES                          AllocatePages;
EFI_FREE_PAGES                              FreePages;
EFI_GET_MEMORY_MAP                          GetMemoryMap;
EFI_ALLOCATE_POOL                           AllocatePool;
EFI_FREE_POOL                               FreePool;
EFI_CREATE_EVENT                            CreateEvent;
EFI_SET_TIMER                               SetTimer;
EFI_WAIT_FOR_EVENT                          WaitForEvent;
EFI_SIGNAL_EVENT                            SignalEvent;
EFI_CLOSE_EVENT                             CloseEvent;
EFI_CHECK_EVENT                             CheckEvent;
EFI_INSTALL_PROTOCOL_INTERFACE              InstallProtocolInterface;
EFI_REINSTALL_PROTOCOL_INTERFACE            ReinstallProtocolInterface;
EFI_UNINSTALL_PROTOCOL_INTERFACE            UninstallProtocolInterface;
EFI_HANDLE_PROTOCOL                         HandleProtocol;
VOID*                                       Reserved;
EFI_REGISTER_PROTOCOL_NOTIFY                RegisterProtocolNotify;
EFI_LOCATE_HANDLE                           LocateHandle;
EFI_LOCATE_DEVICE_PATH                      LocateDevicePath;
EFI_INSTALL_CONFIGURATION_TABLE             InstallConfigurationTable;
EFI_IMAGE_UNLOAD                            LoadImage;
EFI_IMAGE_START                             StartImage;
EFI_EXIT                                    Exit;
EFI_IMAGE_UNLOAD                            UnloadImage;
EFI_EXIT_BOOT_SERVICES                      ExitBootServices;
EFI_GET_NEXT_MONOTONIC_COUNT                GetNextMonotonicCount;
EFI_STALL                                   Stall;
EFI_SET_WATCHDOG_TIMER                      SetWatchdogTimer;
EFI_CONNECT_CONTROLLER                      ConnectController; 
EFI_DISCONNECT_CONTROLLER                   DisconnectController;
EFI_OPEN_PROTOCOL                           OpenProtocol;
EFI_CLOSE_PROTOCOL                          CloseProtocol;
EFI_OPEN_PROTOCOL_INFORMATION               OpenProtocolInformation;
EFI_PROTOCOLS_PER_HANDLE                    ProtocolsPerHandle;
EFI_LOCATE_HANDLE_BUFFER                    LocateHandleBuffer;
EFI_LOCATE_PROTOCOL                         LocateProtocol;
EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES  InstallMultipleProtocolInterfaces; 
EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES  UninstallMultipleProtocolInterfaces; 
EFI_CALCULATE_CRC32                         CalculateCrc32;
EFI_COPY_MEM                                CopyMem;
EFI_SET_MEM                                 SetMem;
EFI_CREATE_EVENT_EX                         CreateEventEx; 
};



struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL
{
EFI_INPUT_RESET     Reset;
EFI_INPUT_READ_KEY  ReadKeyStroke;
EFI_EVENT           WaitForKey;
};

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL 
{
EFI_TEXT_RESET                  Reset;
EFI_TEXT_STRING                 OutputString;
EFI_TEXT_TEST_STRING            TestString;
EFI_TEXT_QUERY_MODE             QueryMode;
EFI_TEXT_SET_MODE               SetMode;
EFI_TEXT_SET_ATTRIBUTE          SetAttribute;
EFI_TEXT_CLEAR_SCREEN           ClearScreen;
EFI_TEXT_SET_CURSOR_POSITION    SetCursorPosition;
EFI_TEXT_ENABLE_CURSOR          EnableCursor;
SIMPLE_TEXT_OUTPUT_MODE*        Mode;
};

struct EFI_SIMPLE_POINTER_PROTOCOL 
{
EFI_SIMPLE_POINTER_RESET     Reset;
EFI_SIMPLE_POINTER_GET_STATE GetState;
EFI_EVENT                    WaitForInput;
EFI_SIMPLE_POINTER_MODE*     Mode;
};

struct EFI_GRAPHICS_OUTPUT_PROTOCOL 
{
EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE QueryMode;
EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE   SetMode;
EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT        Blt;
EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE*      Mode;
};

struct EFI_DEVICE_PATH_PROTOCOL 
{
UINT8 Type;
UINT8 SubType;
UINT8 Length[2];
};

struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL 
{
UINT64                                      Revision;
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME OpenVolume;
};

struct EFI_FILE_PROTOCOL
{
UINT64                  Revision;
EFI_FILE_OPEN           Open;
EFI_FILE_CLOSE          Close;
EFI_FILE_DELETE         Delete;
EFI_FILE_READ           Read;
EFI_FILE_WRITE          Write;
EFI_FILE_GET_POSITION   GetPosition;
EFI_FILE_SET_POSITION   SetPosition;
EFI_FILE_GET_INFO       GetInfo;
EFI_FILE_SET_INFO       SetInfo;
EFI_FILE_FLUSH          Flush;
EFI_FILE_OPEN_EX        OpenEx;
EFI_FILE_READ_EX        ReadEx;
EFI_FILE_WRITE_EX       WriteEx;
EFI_FILE_FLUSH_EX       FlushEx; 
};

struct EFI_LOADED_IMAGE_PROTOCOL 
{
UINT32                    Revision;
EFI_HANDLE                ParentHandle;
EFI_SYSTEM_TABLE*         SystemTable;
EFI_HANDLE                DeviceHandle;
EFI_DEVICE_PATH_PROTOCOL* FilePath;
VOID*                     Reserved;
UINT32                    LoadOptionsSize;
VOID*                     LoadOptions;
VOID*                     ImageBase;
UINT64                    ImageSize;
EFI_MEMORY_TYPE           ImageCodeType;
EFI_MEMORY_TYPE           ImageDataType;
EFI_IMAGE_UNLOAD          Unload;
};


struct EFI_SIMPLE_POINTER_MODE
{UINT64 ResolutionX;UINT64 ResolutionY;UINT64 ResolutionZ;BOOLEAN LeftButton;BOOLEAN RightButton;};

struct EFI_INPUT_KEY
{UINT16 ScanCode;CHAR16 UnicodeChar;};

struct EFI_SIMPLE_POINTER_STATE
{INT32 RelativeMovementX;INT32 RelativeMovementY;INT32 RelativeMovementZ;BOOLEAN LeftButton;BOOLEAN RightButton;};

struct SIMPLE_TEXT_OUTPUT_MODE 
{INT32 MaxMode;INT32 Mode;INT32 Attribute;INT32 CursorColumn;INT32 CursorRow;BOOLEAN CursorVisible;};

struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE
{UINT32 MaxMode;UINT32 Mode;EFI_GRAPHICS_OUTPUT_MODE_INFORMATION*Info;UINTN SizeOfInfo;EFI_PHYSICAL_ADDRESS FrameBufferBase;UINTN FrameBufferSize;};

struct EFI_PIXEL_BITMASK 
{UINT32 RedMask;UINT32 GreenMask;UINT32 BlueMask;UINT32 ReservedMask;};

struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION 
{UINT32 Version;UINT32 HorizontalResolution;UINT32 VerticalResolution;EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;EFI_PIXEL_BITMASK PixelInformation;UINT32 PixelsPerScanLine;};

struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL 
{UINT8 Blue;UINT8 Green;UINT8 Red;UINT8 Reserved;};

struct EFI_CONFIGURATION_TABLE
{EFI_GUID VendorGuid;VOID*VendorTable;};

struct EFI_TIME
{UINT16 Year;UINT8 Month;UINT8 Day;UINT8 Hour; UINT8 Minute;UINT8 Second;UINT8 Pad1;UINT32 Nanosecond;INT16 TimeZone;UINT8 Daylight;UINT8 Pad2;};

struct EFI_TIME_CAPABILITIES
{UINT32 Resolution;UINT32 Accuracy;BOOLEAN SetsToZero;};

struct EFI_CAPSULE_HEADER
{EFI_GUID CapsuleGuid;UINT32 HeaderSize;UINT32 Flags;UINT32 CapsuleImageSize;};

struct EFI_CAPSULE_TABLE
{UINT32 CapsuleArrayNumber;VOID*CapsulePtr[1];};

struct EFI_MEMORY_DESCRIPTOR
{UINT32 Type;EFI_PHYSICAL_ADDRESS PhysicalStart;EFI_VIRTUAL_ADDRESS VirtualStart;UINT64 NumberOfPages;UINT64 Attribute;};

struct EFI_CAPSULE_BLOCK_DESCRIPTOR
{UINT64 Length;union{EFI_PHYSICAL_ADDRESS DataBlock;EFI_PHYSICAL_ADDRESS ContinuationPointer;}Union;};

struct EFI_OPEN_PROTOCOL_INFORMATION_ENTRY{EFI_HANDLE AgentHandle;EFI_HANDLE ControllerHandle;UINT32 Attributes;UINT32 OpenCount;};

struct EFI_FILE_IO_TOKEN{EFI_EVENT Event;EFI_STATUS Status;UINTN BufferSize;VOID*Buffer;};

struct EFI_FILE_INFO{UINT64 Size;UINT64 FileSize;UINT64 PhysicalSize;EFI_TIME CreateTime;EFI_TIME LastAccessTime;EFI_TIME ModificationTime;UINT64 Attribute;CHAR16 FileName[256];};

