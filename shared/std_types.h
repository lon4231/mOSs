#pragma once

#include <cstdint>
#include <cstddef>
#include <cstdarg>
#include <array>

#define EFIAPI __attribute__((ms_abi))

#define PAGE_SIZE 4096
#define PHYS_PAGE_ADDR_MASK 0x000FFFFFFFFFF000
#define KERNEL_START_ADDRESS 0xFFFFFFFF80000000

#define KERNEL_STACK_SIZE 64

#define IN
#define OUT
#define OPTIONAL
#define CONST const

typedef bool BOOLEAN;
typedef ssize_t INTN;
typedef size_t UINTN;
typedef int8_t INT8;
typedef uint8_t UINT8;
typedef int16_t INT16;
typedef uint16_t UINT16;
typedef int32_t INT32;
typedef uint32_t UINT32;
typedef int64_t INT64;
typedef uint64_t UINT64;
typedef char CHAR8;

typedef char16_t CHAR16;

typedef void VOID;

typedef UINTN EFI_STATUS;
typedef VOID *EFI_HANDLE;
typedef VOID *EFI_EVENT;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;

typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;

struct MEMORY_DESCRIPTOR_T
{
    UINT32 Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
};

struct MEMORY_MAP_INFO
{
    UINTN size;
    MEMORY_DESCRIPTOR_T *map;
    UINTN key;
    UINTN desc_size;
    UINT32 desc_version;
};