#ifndef _ARCH_PAGE_TABLES_DEFINED_
#define _ARCH_PAGE_TABLES_DEFINED_

#include <arch_types.h>

typedef uint64_t page_table_entry_t;

struct page_table_t
{
    page_table_entry_t entries[512];
};

#endif