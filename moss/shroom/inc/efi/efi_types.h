#ifndef _EFI_TYPES_DEFINED_
#define _EFI_TYPES_DEFINED_

#define EFIAPI __attribute__((ms_abi))

#include <cstdint>
#include <cstddef>
#include <sys/types.h>


#define IN
#define OUT
#define OPTIONAL
#define CONST const

typedef uint8_t BOOLEAN;
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

struct EFI_GUID
{
    UINT32 TimeLow;
    UINT16 TimeMid;
    UINT16 TimeHighAndVersion;
    UINT8  ClockSeqHighAndReserved;
    UINT8  ClockSeqLow;
    UINT8  Node[6];
}__attribute__((packed));

typedef UINTN EFI_STATUS;
typedef VOID *EFI_HANDLE;
typedef VOID *EFI_EVENT;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;

typedef UINTN EFI_PHYSICAL_ADDRESS;
typedef UINTN EFI_VIRTUAL_ADDRESS;

#endif