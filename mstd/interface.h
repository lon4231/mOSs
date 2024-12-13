#pragma once

#include "mstd.h"
#include "shared.h"

enum DRIVER_TYPE
{
DRIVER_NULL,
DRIVER_DISK,
DRIVER_NETWORKING,
DRIVER_SOUND,
DRIVER_GRAPHICS,
DRIVER_KEYBOARD,
DRIVER_MOUSE,
DRIVER_SPECIAL,
};

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

struct driver_entry_t
{
UINT8        type;
CHAR16       path[256];
};

struct boot_config_t
{
UINT32 gop_mode;
UINT32 driver_count;
driver_entry_t*entries;
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
MEMORY_MAP_INFO            mmap;
sgi_t                      sgi;
alloc_context_t            alloc_context;
KERN_RUNTIME_SERVICES      krs;
xsdt_t*                    xdst;
page_table_t*              pml4;
};

UINT64 get_mmap_usable_pages(MEMORY_MAP_INFO*mmap) 
{
UINT64 total_pages=0;
for(UINTN i=0;i<mmap->size/mmap->desc_size;++i)
{
MEMORY_DESCRIPTOR_T*desc=(MEMORY_DESCRIPTOR_T*)((UINT8*)mmap->map+(i*mmap->desc_size));
if(desc->Type==MTConventionalMemory)
{total_pages+=desc->NumberOfPages;}
}
return total_pages;
}

void*mmap_allocate_pages(alloc_context_t*alloc_context,UINTN pages)
{
if (alloc_context->remaining_pages<pages)
{
UINTN i=alloc_context->current_descriptor+1;
for (;i<alloc_context->mmap->size/alloc_context->mmap->desc_size;++i)
{
MEMORY_DESCRIPTOR_T*desc=(MEMORY_DESCRIPTOR_T*)((UINT8*)alloc_context->mmap->map+(i*alloc_context->mmap->desc_size));

if (desc->Type==MTConventionalMemory&&desc->NumberOfPages>=pages)
{
alloc_context->current_descriptor=i;
alloc_context->remaining_pages=desc->NumberOfPages-pages;
alloc_context->next_page_address=(void*)(desc->PhysicalStart+(pages*PAGE_SIZE));
return (void*)desc->PhysicalStart;
}
}

if (i>=alloc_context->mmap->size/alloc_context->mmap->desc_size)
{return nullptr;}
}

alloc_context->remaining_pages-=pages;
void*page=alloc_context->next_page_address;
alloc_context->next_page_address=(void*)((UINT8*)page+(pages*PAGE_SIZE));
return page;
}

