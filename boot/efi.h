#pragma once

#include "std_types.h"
#include "mmap.h"

#define UNDEFINED_FUNC VOID *

#define EFIAPI __attribute__((ms_abi))

typedef UINTN EFI_STATUS;
typedef VOID *EFI_HANDLE;
typedef VOID *EFI_EVENT;
typedef UINT64 EFI_LBA;

typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;

#define EFI_FILE_INFO_ID {0x09576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}
#define EFI_LOADED_IMAGE_PROTOCOL_GUID {0x5B1B31A1, 0x9562, 0x11d2, {0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}}
#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID {0x964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}
#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}}

#define EFI_FILE_MODE_READ 0x0000000000000001
#define EFI_FILE_MODE_WRITE 0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

#define EFI_FILE_READ_ONLY 0x0000000000000001
#define EFI_FILE_HIDDEN 0x0000000000000002
#define EFI_FILE_SYSTEM 0x0000000000000004
#define EFI_FILE_RESERVED 0x0000000000000008
#define EFI_FILE_DIRECTORY 0x0000000000000010
#define EFI_FILE_ARCHIVE 0x0000000000000020
#define EFI_FILE_VALID_ATTR 0x0000000000000037

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL 0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL 0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER 0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE 0x00000020

enum EFI_RESET_TYPE
{
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
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

enum EFI_GRAPHICS_PIXEL_FORMAT
{
PixelRedGreenBlueReserved8BitPerColor,
PixelBlueGreenRedReserved8BitPerColor,
PixelBitMask,
PixelBltOnly,
PixelFormatMax
};


struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
struct EFI_BOOT_SERVICES;
struct EFI_RUNTIME_SERVICES;
struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;
struct EFI_FILE_PROTOCOL;

struct EFI_GUID
{
    UINT32 TimeLow;
    UINT16 TimeMid;
    UINT16 TimeHighAndVersion;
    UINT8 Node[8];
} __attribute__((packed));

struct EFI_MEMORY_DESCRIPTOR
{
    UINT32 Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
};

struct EFI_TABLE_HEADER
{
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
};

struct EFI_CONFIGURATION_TABLE
{
    EFI_GUID VendorGuid;
    VOID *VendorTable;
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

struct EFI_TIME_CAPABILITIES
{
    UINT32 Resolution;
    UINT32 Accuracy;
    BOOLEAN SetsToZero;
};

struct EFI_PIXEL_BITMASK
{
UINT32 RedMask;
UINT32 GreenMask;
UINT32 BlueMask;
UINT32 ReservedMask;
};


struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION
{
    UINT32 Version;
    UINT32 HorizontalResolution;
    UINT32 VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
    EFI_PIXEL_BITMASK PixelInformation;
    UINT32 PixelsPerScanLine;
};


struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE 
{
UINT32 MaxMode;
UINT32 Mode;
EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
UINTN SizeOfInfo;
EFI_PHYSICAL_ADDRESS FrameBufferBase;
UINTN FrameBufferSize;
};
    

typedef EFIAPI EFI_STATUS (*EFI_EXIT_BOOT_SERVICES)(IN EFI_HANDLE ImageHandle, IN UINTN MapKey);
typedef EFI_STATUS(EFIAPI *EFI_ALLOCATE_POOL)(IN EFI_MEMORY_TYPE PoolType, IN UINTN Size, OUT VOID **Buffer);
typedef EFI_STATUS(EFIAPI *EFI_FREE_POOL)(IN VOID *Buffer);
typedef EFI_STATUS(EFIAPI *EFI_ALLOCATE_PAGES)(IN EFI_ALLOCATE_TYPE Type, IN EFI_MEMORY_TYPE MemoryType, IN UINTN Pages, IN OUT EFI_PHYSICAL_ADDRESS *Memory);
typedef EFI_STATUS(EFIAPI *EFI_FREE_PAGES)(IN EFI_PHYSICAL_ADDRESS Memory, IN UINTN Pages);
typedef EFI_STATUS(EFIAPI *EFI_GET_MEMORY_MAP)(IN OUT UINTN *MemoryMapSize, OUT EFI_MEMORY_DESCRIPTOR *MemoryMap, OUT UINTN *MapKey, OUT UINTN *DescriptorSize, OUT UINT32 *DescriptorVersion);

typedef EFI_STATUS (*EFI_GET_TIME)(OUT EFI_TIME *Time, OUT EFI_TIME_CAPABILITIES *Capabilities OPTIONAL);
typedef EFI_STATUS (*EFI_SET_TIME)(IN EFI_TIME *Time);
typedef EFI_STATUS (*EFI_SET_VIRTUAL_ADDRESS_MAP)(IN UINTN MemoryMapSize, IN UINTN DescriptorSize, IN UINT32 DescriptorVersion, IN EFI_MEMORY_DESCRIPTOR *VirtualMap);
typedef VOID(EFIAPI *EFI_RESET_SYSTEM)(IN EFI_RESET_TYPE ResetType, IN EFI_STATUS ResetStatus, IN UINTN DataSize, IN VOID *ResetData OPTIONAL);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_STRING)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN CHAR16 *String);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_CLEAR_SCREEN)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME)(IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This, OUT EFI_FILE_PROTOCOL **Root);
typedef EFI_STATUS(EFIAPI *EFI_FILE_OPEN)(IN EFI_FILE_PROTOCOL *This, OUT EFI_FILE_PROTOCOL **NewHandle, IN CHAR16 *FileName, IN UINT64 OpenMode, IN UINT64 Attributes);
typedef EFI_STATUS(EFIAPI *EFI_FILE_CLOSE)(IN EFI_FILE_PROTOCOL *This);
typedef EFI_STATUS(EFIAPI *EFI_FILE_DELETE)(IN EFI_FILE_PROTOCOL *This);
typedef EFI_STATUS(EFIAPI *EFI_FILE_READ)(IN EFI_FILE_PROTOCOL *This, IN OUT UINTN *BufferSize, OUT VOID *Buffer);
typedef EFI_STATUS(EFIAPI *EFI_FILE_WRITE)(IN EFI_FILE_PROTOCOL *This, IN OUT UINTN *BufferSize, IN VOID *Buffer);
typedef EFI_STATUS(EFIAPI *EFI_FILE_SET_POSITION)(IN EFI_FILE_PROTOCOL *This, IN UINT64 Position);
typedef EFI_STATUS(EFIAPI *EFI_FILE_GET_POSITION)(IN EFI_FILE_PROTOCOL *This, OUT UINT64 *Position);
typedef EFI_STATUS(EFIAPI *EFI_FILE_GET_INFO)(IN EFI_FILE_PROTOCOL *This, IN EFI_GUID *InformationType, IN OUT UINTN *BufferSize, OUT VOID *Buffer);
typedef EFI_STATUS(EFIAPI *EFI_FILE_SET_INFO)(IN EFI_FILE_PROTOCOL *This, IN EFI_GUID *InformationType, IN UINTN BufferSize, IN VOID *Buffer);

typedef EFI_STATUS(EFIAPI *EFI_OPEN_PROTOCOL)(IN EFI_HANDLE Handle, IN EFI_GUID *Protocol, OUT VOID **Interface OPTIONAL, IN EFI_HANDLE AgentHandle, IN EFI_HANDLE ControllerHandle, IN UINT32 Attributes);
typedef EFI_STATUS(EFIAPI *EFI_LOCATE_PROTOCOL)(IN EFI_GUID *Protocol, IN VOID *Registration OPTIONAL, OUT VOID **Interface);

struct EFI_BOOT_SERVICES
{
    EFI_TABLE_HEADER Hdr;
    UNDEFINED_FUNC RaiseTPL;
    UNDEFINED_FUNC RestoreTPL;
    EFI_ALLOCATE_PAGES AllocatePages;
    EFI_FREE_PAGES FreePages;
    EFI_GET_MEMORY_MAP GetMemoryMap;
    EFI_ALLOCATE_POOL AllocatePool;
    EFI_FREE_POOL FreePool;
    UNDEFINED_FUNC CreateEvent;
    UNDEFINED_FUNC SetTimer;
    UNDEFINED_FUNC WaitForEvent;
    UNDEFINED_FUNC SignalEvent;
    UNDEFINED_FUNC CloseEvent;
    UNDEFINED_FUNC CheckEvent;
    UNDEFINED_FUNC InstallProtocolInterface;
    UNDEFINED_FUNC ReinstallProtocolInterface;
    UNDEFINED_FUNC UninstallProtocolInterface;
    UNDEFINED_FUNC HandleProtocol;
    VOID *Reserved;
    UNDEFINED_FUNC RegisterProtocolNotify;
    UNDEFINED_FUNC LocateHandle;
    UNDEFINED_FUNC LocateDevicePath;
    UNDEFINED_FUNC InstallConfigurationTable;
    UNDEFINED_FUNC LoadImage;
    UNDEFINED_FUNC StartImage;
    UNDEFINED_FUNC Exit;
    UNDEFINED_FUNC UnloadImage;
    EFI_EXIT_BOOT_SERVICES ExitBootServices;
    UNDEFINED_FUNC GetNextMonotonicCount;
    UNDEFINED_FUNC Stall;
    UNDEFINED_FUNC SetWatchdogTimer;
    UNDEFINED_FUNC ConnectControlle;
    UNDEFINED_FUNC DisconnectController;
    EFI_OPEN_PROTOCOL OpenProtocol;
    UNDEFINED_FUNC CloseProtocol;
    UNDEFINED_FUNC OpenProtocolInformation;
    UNDEFINED_FUNC ProtocolsPerHandle;
    UNDEFINED_FUNC LocateHandleBuffer;
    EFI_LOCATE_PROTOCOL LocateProtocol;
    UNDEFINED_FUNC InstallMultipleProtocolInterfaces;
    UNDEFINED_FUNC UninstallMultipleProtocolInterfaces;
    UNDEFINED_FUNC CalculateCrc32;
    UNDEFINED_FUNC CopyMem;
    UNDEFINED_FUNC SetMem;
    UNDEFINED_FUNC CreateEventEx;
};

struct EFI_RUNTIME_SERVICES
{
    EFI_TABLE_HEADER Hdr;
    EFI_GET_TIME GetTime;
    EFI_SET_TIME SetTime;
    UNDEFINED_FUNC GetWakeupTime;
    UNDEFINED_FUNC SetWakeupTime;
    EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
    UNDEFINED_FUNC ConvertPointer;
    UNDEFINED_FUNC GetVariable;
    UNDEFINED_FUNC GetNextVariableName;
    UNDEFINED_FUNC SetVariable;
    UNDEFINED_FUNC GetNextHighMonotonicCount;
    EFI_RESET_SYSTEM ResetSystem;
    UNDEFINED_FUNC UpdateCapsule;
    UNDEFINED_FUNC QueryCapsuleCapabilities;
    UNDEFINED_FUNC QueryVariableInfo;
};

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
{
    UNDEFINED_FUNC Reset;
    EFI_TEXT_STRING OutputString;
    UNDEFINED_FUNC TestString;
    UNDEFINED_FUNC QueryMode;
    UNDEFINED_FUNC SetMode;
    UNDEFINED_FUNC SetAttribute;
    EFI_TEXT_CLEAR_SCREEN ClearScreen;
    UNDEFINED_FUNC SetCursorPosition;
    UNDEFINED_FUNC EnableCursor;
    void *Mode;
};

struct EFI_SYSTEM_TABLE
{
    EFI_TABLE_HEADER Hdr;
    CHAR16 *FirmwareVendor;
    UINT32 FirmwareRevision;
    EFI_HANDLE ConsoleInHandle;
    void *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    EFI_HANDLE StandardErrorHandle;
    void *StdErr;
    EFI_RUNTIME_SERVICES *RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    UINTN NumberOfTableEntries;
    EFI_CONFIGURATION_TABLE *ConfigurationTable;
};

struct EFI_FILE_INFO
{
    UINT64 Size;
    UINT64 FileSize;
    UINT64 PhysicalSize;
    EFI_TIME CreateTime;
    EFI_TIME LastAccessTime;
    EFI_TIME ModificationTime;
    UINT64 Attribute;
    CHAR16 FileName[256];
};

struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL
{
    UINT64 Revision;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME OpenVolume;
};

struct EFI_FILE_PROTOCOL
{
    UINT64 Revision;
    EFI_FILE_OPEN Open;
    EFI_FILE_CLOSE Close;
    EFI_FILE_DELETE Delete;
    EFI_FILE_READ Read;
    EFI_FILE_WRITE Write;
    EFI_FILE_GET_POSITION GetPosition;
    EFI_FILE_SET_POSITION SetPosition;
    EFI_FILE_GET_INFO GetInfo;
    EFI_FILE_SET_INFO SetInfo;
    UNDEFINED_FUNC Flush;
    UNDEFINED_FUNC OpenEx;
    UNDEFINED_FUNC ReadEx;
    UNDEFINED_FUNC WriteEx;
    UNDEFINED_FUNC FlushEx;
};

struct EFI_LOADED_IMAGE_PROTOCOL
{
    UINT32 Revision;
    EFI_HANDLE ParentHandle;
    EFI_SYSTEM_TABLE *SystemTable;
    EFI_HANDLE DeviceHandle;
    void *FilePath;
    VOID *Reserved;
    UINT32 LoadOptionsSize;
    VOID *LoadOptions;
    VOID *ImageBase;
    UINT64 ImageSize;
    EFI_MEMORY_TYPE ImageCodeType;
    EFI_MEMORY_TYPE ImageDataType;
    UNDEFINED_FUNC Unload;
};

struct EFI_GRAPHICS_OUTPUT_PROTOCOL 
{
UNDEFINED_FUNC QueryMode;
UNDEFINED_FUNC SetMode;
UNDEFINED_FUNC Blt;
EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
};
    