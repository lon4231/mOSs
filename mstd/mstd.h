#pragma once


#include <cstdint>
#include <cstddef>
#include <cstdarg>
#include <array>


#define EFIAPI __attribute__((ms_abi))

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#define SIZE_TO_PAGES(x) (((x)+(PAGE_SIZE)-1)/(PAGE_SIZE))


#define PAGE_SIZE 4096
#define PHYS_PAGE_ADDR_MASK  0x000FFFFFFFFFF000
#define KERNEL_START_ADDRESS 0xFFFFFFFF80000000


#define IN
#define OUT
#define OPTIONAL
#define CONST const

typedef bool            BOOLEAN;
typedef ssize_t         INTN;
typedef size_t          UINTN;
typedef int8_t          INT8;
typedef uint8_t         UINT8;
typedef int16_t         INT16;
typedef uint16_t        UINT16;
typedef int32_t         INT32;
typedef uint32_t        UINT32;
typedef int64_t         INT64;
typedef uint64_t        UINT64;
typedef char            CHAR8;

typedef char16_t        CHAR16;

typedef void            VOID;

typedef UINTN           EFI_STATUS;
typedef VOID*           EFI_HANDLE;
typedef VOID*           EFI_EVENT;
typedef UINT64          EFI_LBA;
typedef UINTN           EFI_TPL;

typedef UINT64          EFI_PHYSICAL_ADDRESS;
typedef UINT64          EFI_VIRTUAL_ADDRESS;

VOID*memcpy(VOID*dst,VOID*src,UINTN len) 
{
UINT8*p=(UINT8*)dst;
UINT8*q=(UINT8*)src;
for (UINTN i=0;i<len;i++)
p[i]=q[i];
return dst;
}

INTN memcmp(VOID*m1,VOID*m2,UINTN len) 
{
UINT8*p=(UINT8*)m1;
UINT8*q=(UINT8*)m2;
for (UINTN i = 0; i < len; i++)
if(p[i]!=q[i])return(INTN)(p[i])-(INTN)(q[i]);
return 0;
}

VOID*memset(VOID*dst,UINT8 c,UINTN len) 
{
UINT8*p=(UINT8*)dst;
for(UINTN i=0;i<len;i++)
p[i]=c;
return dst;
}

INTN strcmp(const char*str0,const char*str1,UINTN len)
{
UINT8*p=(UINT8*)str0;
UINT8*q=(UINT8*)str1;
for (UINTN i = 0; i < len; i++)
if(p[i]!=q[i])return(INTN)(p[i])-(INTN)(q[i]);
return 0;
}