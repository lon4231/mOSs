#pragma once

#include "mstd.h"

enum INTERRUPT_TYPE
{
INTERRUPT_GATE=0x8E,
TRAP_GATE=0x8F,
};

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
UINT32 Type;
EFI_PHYSICAL_ADDRESS PhysicalStart;
EFI_VIRTUAL_ADDRESS VirtualStart;
UINT64 NumberOfPages;
UINT64 Attribute;
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
UINTN   size;
MEMORY_DESCRIPTOR_T*map;
UINTN   key;
UINTN   desc_size;
UINT32  desc_version;
};

struct page_table_t 
{
UINT64 entries[512];
};

enum 
{
PAGE_PRESENT  =(1<<0),
PAGE_READWRITE=(1<<1),
PAGE_USER      =(1<<2),
};

struct x86_64_desc_t
{
union 
{
UINT64 value;
struct 
{
UINT64 limit_15_0:  16;
UINT64 base_15_0:   16;
UINT64 base_23_16:  8;
UINT64 type:        4;
UINT64 s:           1; 
UINT64 dpl:         2; 
UINT64 p:           1; 
UINT64 limit_19_16: 4;
UINT64 avl:         1; 
UINT64 l:           1; 
UINT64 d_b:         1; 
UINT64 g:           1; 
UINT64 base_31_24:  8;
};
};
};

struct tss_ldt_desc_t
{
x86_64_desc_t descriptor;
UINT32 base_63_32;
UINT32 zero;
};

struct tss_t
{
UINT32 reserved_1;
UINT32 RSP0_lower;
UINT32 RSP0_upper;
UINT32 RSP1_lower;
UINT32 RSP1_upper;
UINT32 RSP2_lower;
UINT32 RSP2_upper;
UINT32 reserved_2;
UINT32 reserved_3;
UINT32 IST1_lower;
UINT32 IST1_upper;
UINT32 IST2_lower;
UINT32 IST2_upper;
UINT32 IST3_lower;
UINT32 IST3_upper;
UINT32 IST4_lower;
UINT32 IST4_upper;
UINT32 IST5_lower;
UINT32 IST5_upper;
UINT32 IST6_lower;
UINT32 IST6_upper;
UINT32 IST7_lower;
UINT32 IST7_upper;
UINT32 reserved_4;
UINT32 reserved_5;
UINT16 reserved_6;
UINT16 io_map_base;
};

struct gdt_t
{
x86_64_desc_t  null;
x86_64_desc_t  kernel_code_64;
x86_64_desc_t  kernel_data_64;
x86_64_desc_t  user_code_64;
x86_64_desc_t  user_data_64;
x86_64_desc_t  kernel_code_32;
x86_64_desc_t  kernel_data_32;
x86_64_desc_t  user_code_32;
x86_64_desc_t  user_data_32;
tss_ldt_desc_t tss;
};

struct desc_reg_t
{
UINT16 limit;
UINT64 base; 
}__attribute__((packed));

struct idt_desc_t
{
UINT16 isr_low;
UINT16 kernel_cs;
UINT8	 ist;
UINT8  attributes;
UINT16 isr_mid;
UINT32 isr_high;
UINT32 reserved;
}__attribute__((packed));

struct idtr_t
{
UINT16 limit;
UINT64 base;
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
} __attribute__ ((packed));

struct acpi_header_t
{
CHAR8   Signature[4];
UINT32  Length;
UINT8   Revision;
UINT8   Checksum;
CHAR8   OEMID[6];
CHAR8   OEMTableID[8];
UINT32  OEMRevision;
UINT32  CreatorID;
UINT32  CreatorRevision;
};

struct xsdt_t 
{
acpi_header_t header;
};

struct madt_t
{
acpi_header_t header;
UINT32 lica;
UINT32 flags;

};

struct gas_t
{
  UINT8 AddressSpace;
  UINT8 BitWidth;
  UINT8 BitOffset;
  UINT8 AccessSize;
  UINT64 Address;
};

struct fadt_t
{
acpi_header_t h;
UINT32        FirmwareCtrl;
UINT32        Dsdt;
UINT8         Reserved;
UINT8         PreferredPowerManagementProfile;
UINT16        SCI_Interrupt;
UINT32        SMI_CommandPort;
UINT8         AcpiEnable;
UINT8         AcpiDisable;
UINT8         S4BIOS_REQ;
UINT8         PSTATE_Control;
UINT32        PM1aEventBlock;
UINT32        PM1bEventBlock;
UINT32        PM1aControlBlock;
UINT32        PM1bControlBlock;
UINT32        PM2ControlBlock;
UINT32        PMTimerBlock;
UINT32        GPE0Block;
UINT32        GPE1Block;
UINT8         PM1EventLength;
UINT8         PM1ControlLength;
UINT8         PM2ControlLength;
UINT8         PMTimerLength;
UINT8         GPE0Length;
UINT8         GPE1Length;
UINT8         GPE1Base;
UINT8         CStateControl;
UINT16        WorstC2Latency;
UINT16        WorstC3Latency;
UINT16        FlushSize;
UINT16        FlushStride;
UINT8         DutyOffset;
UINT8         DutyWidth;
UINT8         DayAlarm;
UINT8         MonthAlarm;
UINT8         Century;
UINT16        BootArchitectureFlags;
UINT8         Reserved2;
UINT32        Flags;
gas_t         ResetReg;
UINT8         ResetValue;
UINT8         Reserved3[3];
UINT64        X_FirmwareControl;
UINT64        X_Dsdt;
gas_t         X_PM1aEventBlock;
gas_t         X_PM1bEventBlock;
gas_t         X_PM1aControlBlock;
gas_t         X_PM1bControlBlock;
gas_t         X_PM2ControlBlock;
gas_t         X_PMTimerBlock;
gas_t         X_GPE0Block;
gas_t         X_GPE1Block;
};

struct srat_t
{
char signature[4];  
UINT32 length;    
UINT8  rev;       
UINT8  checksum;  
UINT8  OEMID[6];  
UINT64 OEMTableID;
UINT32 OEMRev;    
UINT32 creatorID; 
UINT32 creatorRev;
UINT8 reserved[12];
} __attribute__((packed));

struct mcfg_entry_t
{
UINT64 base_address;
UINT16 group_number;
UINT8  pci_start;
UINT8  pci_end;
UINT32 reserved;
};

struct mcfg_t
{
acpi_header_t header;
UINT64	      reserved;
};

struct pci_entry_t
{
uint16_t vendor_id;
uint16_t device_id;
uint8_t class_code;
uint8_t subclass;
uint8_t prog_if;
uint8_t revision_id;
uint32_t bar[6];
};
