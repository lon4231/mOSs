#pragma once 

#include "std_types.h"

#define KRN_MEMORY_UC            0x0000000000000001
#define KRN_MEMORY_WC            0x0000000000000002
#define KRN_MEMORY_WT            0x0000000000000004
#define KRN_MEMORY_WB            0x0000000000000008
#define KRN_MEMORY_UCE           0x0000000000000010
#define KRN_MEMORY_WP            0x0000000000001000
#define KRN_MEMORY_RP            0x0000000000002000
#define KRN_MEMORY_XP            0x0000000000004000
#define KRN_MEMORY_NV            0x0000000000008000
#define KRN_MEMORY_MORE_RELIABLE 0x0000000000010000
#define KRN_MEMORY_RO            0x0000000000020000
#define KRN_MEMORY_SP            0x0000000000040000
#define KRN_MEMORY_CPU_CRYPTO    0x0000000000080000
#define KRN_MEMORY_RUNTIME       0x8000000000000000
#define KRN_MEMORY_ISA_VALID     0x4000000000000000
#define KRN_MEMORY_ISA_MASK      0x0FFFF00000000000

enum KRN_RESET_TYPE
{
KRNResetCold,
KRNResetWarm,
KRNResetShutdown,
KRNResetPlatformSpecific
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

struct KRN_GUID
{
UINT32 TimeLow;
UINT16 TimeMid;
UINT16 TimeHighAndVersion;
UINT8  ClockSeqHighAndReserved;
UINT8  ClockSeqLow;
UINT8  Node[6];
}__attribute__((packed));

struct KRN_TIME
{UINT16 Year;UINT8 Month;UINT8 Day;UINT8 Hour; UINT8 Minute;UINT8 Second;UINT8 Pad1;UINT32 Nanosecond;INT16 TimeZone;UINT8 Daylight;UINT8 Pad2;};

struct KRN_TIME_CAPABILITIES
{UINT32 Resolution;UINT32 Accuracy;BOOLEAN SetsToZero;};

struct KRN_TABLE_HEADER
{
UINT64 Signature;
UINT32 Revision;
UINT32 HeaderSize;
UINT32 CRC32;
UINT32 Reserved;
};

struct KRN_CAPSULE_HEADER
{KRN_GUID CapsuleGuid;UINT32 HeaderSize;UINT32 Flags;UINT32 CapsuleImageSize;};

enum vmem_page_flags
{
PAGE_PRESENT   =(1<<0),
PAGE_READWRITE =(1<<1),
PAGE_USER      =(1<<2),
};

typedef EFI_STATUS(EFIAPI*KRN_GET_VARIABLE)                                             (IN CHAR16*VariableName,IN KRN_GUID*VendorGuid,OUT UINT32*Attributes OPTIONAL,IN OUT UINTN*DataSize,OUT VOID*Data OPTIONAL);
typedef EFI_STATUS(EFIAPI*KRN_GET_NEXT_VARIABLE_NAME)                                   (IN OUT UINTN*VariableNameSize,IN OUT CHAR16*VariableName,IN OUT KRN_GUID*VendorGuid);
typedef EFI_STATUS(EFIAPI*KRN_SET_VARIABLE)                                             (IN CHAR16*VariableName,IN KRN_GUID*VendorGuid,IN UINT32 Attributes,IN UINTN DataSize,IN VOID*Data);
typedef EFI_STATUS(EFIAPI*KRN_QUERY_VARIABLE_INFO)                                      (IN UINT32 Attributes,OUT UINT64*MaximumVariableStorageSize,OUT UINT64*RemainingVariableStorageSize,OUT UINT64*MaximumVariableSize);
typedef EFI_STATUS(EFIAPI*KRN_GET_TIME)                                                 (OUT KRN_TIME*Time,OUT KRN_TIME_CAPABILITIES*Capabilities OPTIONAL);
typedef EFI_STATUS(EFIAPI*KRN_SET_TIME)                                                 (IN KRN_TIME*Time);
typedef EFI_STATUS(EFIAPI*KRN_GET_WAKEUP_TIME)                                          (OUT BOOLEAN*Enabled,OUT BOOLEAN*Pending,OUT KRN_TIME*Time);
typedef EFI_STATUS(EFIAPI*KRN_SET_WAKEUP_TIME)                                          (IN BOOLEAN Enable,IN KRN_TIME*Time OPTIONAL);
typedef EFI_STATUS(EFIAPI*KRN_SET_VIRTUAL_ADDRESS_MAP)                                  (IN UINTN MemoryMapSize,IN UINTN DescriptorSize,IN UINT32 DescriptorVersion,IN MEMORY_DESCRIPTOR_T*VirtualMap);
typedef EFI_STATUS(EFIAPI*KRN_CONVERT_POINTER)                                          (IN UINTN DebugDisposition,IN VOID**Address);
typedef VOID      (EFIAPI*KRN_RESET_SYSTEM)                                             (IN KRN_RESET_TYPE ResetType,IN EFI_STATUS ResetStatus,IN UINTN DataSize,IN VOID*ResetData OPTIONAL);
typedef EFI_STATUS(EFIAPI*KRN_GET_NEXT_HIGH_MONO_COUNT)                                 (OUT UINT32*HighCount);
typedef EFI_STATUS(EFIAPI*KRN_UPDATE_CAPSULE)                                           (IN KRN_CAPSULE_HEADER**CapsuleHeaderArray,IN UINTN CapsuleCount,OPTIONAL IN EFI_PHYSICAL_ADDRESS ScatterGatherList);
typedef EFI_STATUS(EFIAPI*KRN_QUERY_CAPSULE_CAPABILITIES)                               (IN KRN_CAPSULE_HEADER**CapsuleHeaderArray,IN UINTN CapsuleCount,OUT UINT64*MaximumCapsuleSize,OUT KRN_RESET_TYPE*ResetType);

struct idt_entry_t
{
UINT16        isr_low;
UINT16        kernel_cs;
UINT8	      ist;
UINT8         attributes;
UINT16        isr_mid;
UINT32        isr_high;
UINT32        reserved;
}__attribute__((packed));

struct page_table_t
{UINT64 entries[512];};


struct idtr_t
{
UINT16	      limit;
UINT64	      base;
} __attribute__((packed));

typedef UINT64 gdt_desc_t;

struct gdt_tss_desc_t
{
UINT16 limit_low;
UINT16 base_low;
UINT8  base_mid;
UINT8  access;
UINT8  flags;
UINT8  base_high;
UINT32 base_upper;
UINT32 reserved;
}__attribute__((packed));

struct gdtr_t
{
UINT16 size;
UINT64 ptr;
}__attribute__((packed));

struct tss_t 
{
UINT32 prev_tss;
UINT32 esp0;
UINT32 ss0;
UINT32 esp1;
UINT32 ss1;
UINT32 esp2;
UINT32 ss2;
UINT32 cr3;
UINT32 eip;
UINT32 eflags;
UINT32 eax;
UINT32 ecx;
UINT32 edx;
UINT32 ebx;
UINT32 esp;
UINT32 ebp;
UINT32 esi;
UINT32 edi;
UINT32 es;
UINT32 cs;
UINT32 ss;
UINT32 ds;
UINT32 fs;
UINT32 gs;
UINT32 ldt;
UINT16 trap;
UINT16 iomap_base;
}__attribute__((packed));

struct rsdp_t 
{
CHAR8  Signature[8];
UINT8  Checksum;
CHAR8  OEMID[6];
UINT8  Revision;
UINT32 RsdtAddress;
}__attribute__((packed));

struct xsdp_t
{
CHAR8    Signature[8];
UINT8    Checksum;
CHAR8    OEMID[6];
UINT8    Revision;
UINT32   RsdtAddress;
UINT32   Length;
UINT64   XsdtAddress;
UINT8    ExtendedChecksum;
UINT8    reserved[3];
}__attribute__((packed));

struct gdt_t
{
gdt_desc_t     null;
gdt_desc_t     k_code;
gdt_desc_t     k_data;
gdt_desc_t     u_code;
gdt_desc_t     u_data;
gdt_tss_desc_t tss;
}__attribute__((packed));


struct KRN_RUNTIME_SERVICES
{
KRN_TABLE_HEADER                Hdr;
KRN_GET_TIME                    GetTime;
KRN_SET_TIME                    SetTime;
KRN_GET_WAKEUP_TIME             GetWakeupTime;
KRN_SET_WAKEUP_TIME             SetWakeupTime;
KRN_SET_VIRTUAL_ADDRESS_MAP     SetVirtualAddressMap;
KRN_CONVERT_POINTER             ConvertPointer;
KRN_GET_VARIABLE                GetVariable;
KRN_GET_NEXT_VARIABLE_NAME      GetNextVariableName;
KRN_SET_VARIABLE                SetVariable;
KRN_GET_NEXT_HIGH_MONO_COUNT    GetNextHighMonotonicCount;
KRN_RESET_SYSTEM                ResetSystem;
KRN_UPDATE_CAPSULE              UpdateCapsule;
KRN_QUERY_CAPSULE_CAPABILITIES  QueryCapsuleCapabilities;
KRN_QUERY_VARIABLE_INFO         QueryVariableInfo;
};

struct screen_handle_t
{
UINT32*fb;
UINTN w;
UINTN h;
};

struct alloc_context_t
{
MEMORY_MAP_INFO*mmap;
UINT8*          bitmap;
UINTN           total_pages;
};

struct vmem_context_t
{
UINTN offset;
UINTN page;
page_table_t*pml4;
alloc_context_t*alloc;
KRN_RUNTIME_SERVICES*runtime_services;

screen_handle_t*sc;
};



struct arch_data_t
{
MEMORY_MAP_INFO mmap;
KRN_RUNTIME_SERVICES*runtime_services;

xsdp_t*         xsdp;
tss_t           tss;

alloc_context_t alloc;
vmem_context_t  vmem;

gdt_t           gdt;
gdtr_t          gdtr;
};


struct kernel_data_t
{
void*           kernel_buffer;
UINTN           kernel_size;
void*           kernel_stack;

UINTN           driver_count;
UINTN*          driver_pages_count;
void**          driver_buffers;

screen_handle_t screen_handle;
};

struct kernel_handle_t
{
arch_data_t   arch;
kernel_data_t kdata;

};

