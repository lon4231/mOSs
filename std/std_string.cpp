#include "std_types.h"
#include "std_string.h"

void *memset(void *dst, UINT8 c, UINTN size)
{
    UINT64 c64;

    UINTN size_64 = size >> 3;
    UINTN rest = size & 7;

    if (size_64 > 0)
    {
        c64 = (c << 0) | (c << 8) | (c << 16) | (c << 24) | (c << 32) | (c << 40) | (c << 48) | (c << 56);
        for (UINTN i = 0; i < size_64; ++i)
        {
            ((UINT64 *)dst)[i] = c64;
        }
    }

    for (UINTN i = 0; i < rest; ++i)
    {
        ((UINT8 *)dst)[(size_64 * sizeof(UINT64)) + i] = c;
    }

    return dst;
}

void *memcpy(void *dst, const void *src, UINTN size)
{
    UINTN size_64 = size >> 3;
    UINTN rest = size & 7;

    for (UINTN i = 0; i < size_64; ++i)
    {
        ((UINT64 *)dst)[i] = ((UINT64 *)src)[i];
    }

    for (UINTN i = 0; i < rest; ++i)
    {
        ((UINT8 *)dst)[(size_64 * sizeof(UINT64)) + i] = ((UINT8 *)src)[(size_64 * sizeof(UINT64)) + i];
    }

    return dst;
}

INTN memcmp(const void *b1, const void *b2, UINTN size)
{
    UINTN size_64 = size >> 3;
    UINTN rest = size & 7;

    for (UINTN i = 0; i < size_64; ++i)
    {
        if (((UINT64 *)b1)[i] != ((UINT64 *)b2)[i])
        {
            return ((UINT64 *)b1)[i] - ((UINT64 *)b2)[i];
        }
    }

    for (UINTN i = 0; i < rest; ++i)
    {
        if (((UINT8 *)b1)[i] != ((UINT8 *)b2)[i])
        {
            return ((UINT8 *)b1)[(size_64 * sizeof(UINT64)) + i] - ((UINT8 *)b2)[(size_64 * sizeof(UINT64)) + i];
        }
    }

    return 0;
}

UINTN strlen(const char *str)
{
    char *ptr = (char *)str;
    while ((*ptr) != '\0')
    {
        ptr++;
    };
    return (UINTN)(ptr - str);
}

INTN strcmp(const char *str1, const char *str2)
{
    UINTN i = 0;
    while (str1[i] && (str1[i] == str2[i]))
    {
        i++;
    }
    return (UINT8)str1[i] - (UINT8)str2[i];
}

INTN strncmp(const char *str1, const char *str2, UINTN size)
{
    UINTN len1 = strlen(str1);
    UINTN len2 = strlen(str2);

    return memcmp(str1, str2, len1 > len2 ? len2 : len1);
}

UINTN c16_strlen(const CHAR16 *str)
{
    CHAR16 *ptr = (CHAR16 *)str;
    while ((*ptr) != u'\0')
    {
        ptr++;
    };
    return (UINTN)(ptr - str);
}

INTN c16_strcmp(const CHAR16 *str1, const CHAR16 *str2)
{
    UINTN i = 0;
    while (str1[i] && (str1[i] == str2[i]))
    {
        i++;
    }
    return (UINT8)str1[i] - (UINT8)str2[i];
}

INTN c16_strncmp(const CHAR16 *str1, const CHAR16 *str2, UINTN size)
{
    UINTN i = 0;
    while ((i < size) && str1[i] && (str1[i] == str2[i]))
    {
        i++;
    }
    return (UINT8)str1[i] - (UINT8)str2[i];
}
