#include <cstr.h>

void *memset(void *dst, uint8_t n, size_t size)
{
    if (size == 0)
    {
        return dst;
    }

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

void *memcpy(void *dst, const void *src, size_t size)
{
    if (size == 0 || dst == src)
        return dst;

    uint8_t *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;

    while (size >= sizeof(uint64_t))
    {
        *(uint64_t *)d = *(const uint64_t *)s;
        d += sizeof(uint64_t);
        s += sizeof(uint64_t);
        size -= sizeof(uint64_t);
    }

    while (size--)
    {
        *d++ = *s++;
    }

    return dst;
}

int memcmp(void *src1, void *src2, size_t size)
{
    const uint8_t *s1 = (const uint8_t *)src1;
    const uint8_t *s2 = (const uint8_t *)src2;

    while (size >= sizeof(uint64_t))
    {
        uint64_t a = *(const uint64_t *)s1;
        uint64_t b = *(const uint64_t *)s2;

        if (a != b)
        {
            for (int i = 0; i < 8; ++i)
            {
                uint8_t byte_a = (a >> (i * 8)) & 0xFF;
                uint8_t byte_b = (b >> (i * 8)) & 0xFF;
                if (byte_a != byte_b)
                    return (int)byte_a - (int)byte_b;
            }
        }

        s1 += sizeof(uint64_t);
        s2 += sizeof(uint64_t);
        size -= sizeof(uint64_t);
    }

    while (size--)
    {
        if (*s1 != *s2)
            return (int)(*s1) - (int)(*s2);
        s1++;
        s2++;
    }

    return 0;
}


size_t strlen(const char*str)
{
const char*original=str;

while(*str!=0)
{str++;}

return (size_t)(str-original);
}

int strcmp(const char*str0,const char*str1)
{
if(strlen(str0)!=strlen(str1)){return -1;}

return memcmp((void*)str0,(void*)str1,strlen(str0));
}

int strncmp(const char*str0,const char*str1,size_t size)
{

return 1;
}
