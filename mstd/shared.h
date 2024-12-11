#pragma once

#include "mstd.h"
#include "arch_include.h"

enum KERN_RESET_TYPE
{
KernResetCold,
KernResetWarm,
KernResetShutdown,
KernResetPlatformSpecific
};

enum MEMORY_TYPE
{
MTReservedMemoryType,
MTLoaderCode,
MTLoaderData,
MTBootServicesCode,
MTBootServicesData,
MTRuntimeServicesCode,
MTRuntimeServicesData,
MTConventionalMemory,
MTUnusableMemory,
MTACPIReclaimMemory,
MTACPIMemoryNVS,
MTMemoryMappedIO,
MTMemoryMappedIOPortSpace,
MTPalCode,
MTPersistentMemory,
MTUnacceptedMemoryType,
MTMaxMemoryType
};


struct MEMORY_DESCRIPTOR_T
{
UINT32               Type;
EFI_PHYSICAL_ADDRESS PhysicalStart;
EFI_VIRTUAL_ADDRESS  VirtualStart;
UINT64               NumberOfPages;
UINT64               Attribute;
};

struct KERN_GUID
{
UINT32 TimeLow;
UINT16 TimeMid;
UINT16 TimeHighAndVersion;
UINT8  ClockSeqHighAndReserved;
UINT8  ClockSeqLow;
UINT8  Node[6];
}__attribute__((packed));

struct KERN_TIME
{UINT16 Year;UINT8 Month;UINT8 Day;UINT8 Hour; UINT8 Minute;UINT8 Second;UINT8 Pad1;UINT32 Nanosecond;INT16 TimeZone;UINT8 Daylight;UINT8 Pad2;};

struct KERN_TIME_CAPABILITIES
{UINT32 Resolution;UINT32 Accuracy;BOOLEAN SetsToZero;};

struct KERN_TABLE_HEADER
{
UINT64 Signature;
UINT32 Revision;
UINT32 HeaderSize;
UINT32 CRC32;
UINT32 Reserved;
};

struct KERN_CAPSULE_HEADER
{KERN_GUID CapsuleGuid;UINT32 HeaderSize;UINT32 Flags;UINT32 CapsuleImageSize;};


struct MEMORY_MAP_INFO
{
UINTN               size;
MEMORY_DESCRIPTOR_T*map;
UINTN               key;
UINTN               desc_size;
UINT32              desc_version;
};
