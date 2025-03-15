#include "std_types.h"
#include "mmap.h"

struct phys_mem_handle_t
{
mmap_t*mmap;


};

void*get_indexed_usable_page(mmap_t*mmap,UINTN index);
