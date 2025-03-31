#include "std_string.h"

void *memset(void *dst, uint8_t c, size_t size)
{
    uint64_t c64;

    size_t size_64 = size >> 3;
    size_t rest = size & 7;

    if (size_64 > 0)
    {
        c64 = (c << 0) | (c << 8) | (c << 16) | (c << 24) | (c << 32) | (c << 40) | (c << 48) | (c << 56);
        for (size_t i = 0; i < size_64; ++i)
        {
            ((uint64_t *)dst)[i] = c64;
        }
    }

    for (size_t i = 0; i < rest; ++i)
    {
        ((uint8_t *)dst)[(size_64 * sizeof(uint64_t)) + i] = c;
    }

    return dst;
}

void *memcpy(void *dst, const void *src, size_t size)
{
    size_t size_64 = size >> 3;
    size_t rest = size & 7;

    for (size_t i = 0; i < size_64; ++i)
    {
        ((uint64_t *)dst)[i] = ((uint64_t *)src)[i];
    }

    for (size_t i = 0; i < rest; ++i)
    {
        ((uint8_t *)dst)[(size_64 * sizeof(uint64_t)) + i] = ((uint8_t *)src)[(size_64 * sizeof(uint64_t)) + i];
    }

    return dst;
}

ssize_t memcmp(const void *b1, const void *b2, size_t size)
{
    size_t size_64 = size >> 3;
    size_t rest = size & 7;

    for (size_t i = 0; i < size_64; ++i)
    {
        if (((uint64_t *)b1)[i] != ((uint64_t *)b2)[i])
        {
            return ((uint64_t *)b1)[i] - ((uint64_t *)b2)[i];
        }
    }

    for (size_t i = 0; i < rest; ++i)
    {
        if (((uint8_t *)b1)[i] != ((uint8_t *)b2)[i])
        {
            return ((uint8_t *)b1)[(size_64 * sizeof(uint64_t)) + i] - ((uint8_t *)b2)[(size_64 * sizeof(uint64_t)) + i];
        }
    }

    return 0;
}

size_t strlen(const char *str)
{
    char *ptr = (char *)str;
    while ((*ptr) != '\0')
    {
        ptr++;
    };
    return (size_t)(ptr - str);
}

ssize_t strcmp(const char *str1, const char *str2)
{
    size_t i = 0;
    while (str1[i] && (str1[i] == str2[i]))
    {
        i++;
    }
    return (uint8_t)str1[i] - (uint8_t)str2[i];
}

ssize_t strncmp(const char *str1, const char *str2, size_t size)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    return memcmp(str1, str2, len1 > len2 ? len2 : len1);
}

size_t c16_strlen(const char16_t *str)
{
    char16_t *ptr = (char16_t *)str;
    while ((*ptr) != u'\0')
    {
        ptr++;
    };
    return (size_t)(ptr - str);
}

ssize_t c16_strcmp(const char16_t *str1, const char16_t *str2)
{
    size_t i = 0;
    while (str1[i] && (str1[i] == str2[i]))
    {
        i++;
    }
    return (uint8_t)str1[i] - (uint8_t)str2[i];
}

ssize_t c16_strncmp(const char16_t *str1, const char16_t *str2, size_t size)
{
    size_t i = 0;
    while ((i < size) && str1[i] && (str1[i] == str2[i]))
    {
        i++;
    }
    return (uint8_t)str1[i] - (uint8_t)str2[i];
}
