#pragma once

#include <cstdint>
#include <cstddef>

void *memset(void *dst, uint8_t c, size_t size);
void *memcpy(void *dst, const void *src, size_t size);
ssize_t memcmp(const void *b1, const void *b2, size_t size);
size_t strlen(const char *str);
ssize_t strcmp(const char *str1, const char *str2);
ssize_t strncmp(const char *str1, const char *str2, size_t size);
size_t c16_strlen(const char16_t *str);
ssize_t c16_strcmp(const char16_t *str1, const char16_t *str2);
ssize_t c16_strncmp(const char16_t *str1, const char16_t *str2, size_t size);
