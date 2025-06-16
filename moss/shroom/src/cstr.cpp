#include <cstr.h>

void *memset(void *dst, uint8_t n, size_t size)
{
    if(size==0){return dst;}

    uint8_t *ptr = (uint8_t *)dst;
    uint64_t n64 = (uint64_t)n;
    n64 |= n64 << 8;
    n64 |= n64 << 16;
    n64 |= n64 << 32;

    while (size >= sizeof(uint64_t))
    {
        *(uint64_t *)ptr = n64;
        ptr += sizeof(uint64_t);
        size -= sizeof(uint64_t);
    }
    while (size--)
    {
        *ptr++ = n;
    }

    return dst;
}

void *memcpy(void *dst, const void *src, size_t size);
int memcmp(void *src1, void *src2, size_t size);
