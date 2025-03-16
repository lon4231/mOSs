#include "std_types.h"
#include "mmap.h"

struct pmm_handle_t
{
mmap_t*mmap;
UINTN reserved_pages;
UINTN usable_pages;

};

void init_pmm(pmm_handle_t*phys_mem,mmap_t*mmap);

void*get_indexed_usable_page(mmap_t*mmap,UINTN index);

void*pmm_reserve_page(pmm_handle_t*phys_mem);
