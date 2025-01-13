#pragma once

#include "std_types.h"

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#define SIZE_TO_PAGES(x) (((x)+(PAGE_SIZE)-1)/(PAGE_SIZE))

VOID*memcpy(VOID*dst,VOID*src,UINTN len)
{
UINT64*dst64=(UINT64*)dst;
UINT64*src64=(UINT64*)src;
UINTN len_UINT64=len / sizeof(UINT64);
for(UINTN i=0;i<len_UINT64;++i){dst64[i]=src64[i];}
UINT8*dst8=(UINT8*)(dst64+len_UINT64);
UINT8*src8=(UINT8*)(src64+len_UINT64);
UINTN remaining_bytes=len%sizeof(UINT64);
for(UINTN i=0;i<remaining_bytes;++i)
{dst8[i]=src8[i];}
return dst;
}


INTN memcmp(VOID*m1,VOID*m2,UINTN len)
{
UINT8*p=(UINT8*)m1;
UINT8*q=(UINT8*)m2;
for (UINTN i=0; i < len; i++)
if(p[i]!=q[i])return(INTN)(p[i])-(INTN)(q[i]);
return 0;
}

VOID*memset(VOID*dst,UINT8 c,UINTN len) 
{
UINT64*dst64=(UINT64*) dst;
UINT64 c64=(UINT64)c;
c64|=(c64<<8);
c64|=(c64<<16);
c64|=(c64<<32);
UINTN len_UINT64=len/sizeof(UINT64);
for (UINTN i=0;i<len_UINT64;++i) 
{dst64[i]=c64;}
UINT8*dst8=(UINT8*)(dst64 + len_UINT64);
UINTN remaining_bytes=len%sizeof(UINT64);
for (UINTN i=0;i<remaining_bytes;++i) 
{dst8[i]=c;}
return dst;
}

INTN strcmp(const char*str0,const char*str1,UINTN len)
{
UINT8*p=(UINT8*)str0;
UINT8*q=(UINT8*)str1;
for (UINTN i=0; i < len; i++)
if(p[i]!=q[i])return(INTN)(p[i])-(INTN)(q[i]);
return 0;
}

void c16_strcpy(CHAR16*dest,const CHAR16*src) 
{
INTN i=0;
while(src[i]!=u'\0') 
{dest[i]=src[i];++i;}
dest[i]=u'\0';
}

