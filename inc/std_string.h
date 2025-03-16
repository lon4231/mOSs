#pragma once

#include "std_types.h"

#define SIZE_TO_PAGES(x) (((x) + (PAGE_SIZE) - 1) / (PAGE_SIZE))

void *memset(void *dst, UINT8 c, UINTN size);
void *memcpy(void *dst, const void *src, UINTN size);
INTN memcmp(const void *b1, const void *b2, UINTN size);
UINTN strlen(const char *str);
INTN strcmp(const char *str1, const char *str2);
INTN strncmp(const char *str1, const char *str2, UINTN size);
UINTN c16_strlen(const CHAR16 *str);
INTN c16_strcmp(const CHAR16 *str1, const CHAR16 *str2);
INTN c16_strncmp(const CHAR16 *str1, const CHAR16 *str2, UINTN size);
