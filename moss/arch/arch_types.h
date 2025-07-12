#ifndef _ARCH_TYPES_DEFINED_
#define _ARCH_TYPES_DEFINED_

#include <cstdint>
#include <cstddef>

#define PAGE_SIZE (4096)
#define SIZE_TO_PAGES(size) ((size+(PAGE_SIZE-1)) / PAGE_SIZE)

#endif