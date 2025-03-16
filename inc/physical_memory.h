#include "std_types.h"
#include "mmap.h"

struct phys_mem_handle_t
{
mmap_t*mmap;
UINTN reserved_pages;
UINTN usable_pages;

};

void init_phys_mem(phys_mem_handle_t*phys_mem,mmap_t*mmap);

void*get_indexed_usable_page(mmap_t*mmap,UINTN index);

void*phys_mem_reserve_page(phys_mem_handle_t*phys_mem);