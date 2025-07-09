#ifndef _SHROOM_C_STRING_DEFINED_
#define _SHROOM_C_STRING_DEFINED_

#include <cstdint>
#include <cstddef>

void *memset(void *dst, uint8_t n, size_t size);
void *memcpy(void *dst, const void *src, size_t size);
int memcmp(void *src1, void *src2, size_t size);

size_t strlen(const char*str);
int strcmp(const char*str0,const char*str1);
int strncmp(const char*str0,const char*str1,size_t size);



#endif