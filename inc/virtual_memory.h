#include "std_types.h"

enum PAGE_TABLE_FLAGS
{
PAGE_TABLE_FLAGS_PRESENT=1,
PAGE_TABLE_FLAGS_RW     =2,
PAGE_TABLE_FLAGS_USER   =4,
};

struct page_table_entry_t
{
UINT64 value;
}__attribute__((packed));

struct page_table_t
{
page_table_entry_t entries[512];
}__attribute__((packed));

typedef void*(*vmm_page_request)();
typedef void (*vmm_page_free_request)(void*phys_addr);

struct vmm_handle_t
{
vmm_page_request request_page;
vmm_page_free_request free_page;
page_table_t*pml4;
};

void init_vmm(vmm_handle_t*vmm,void*pml4_page);

void vmm_map_page(vmm_handle_t*vmem,void*phys_addr,void*virt_addr,UINT32 flags);

void vmm_map_pages(vmm_handle_t*vmem,void*phys_addr,void*virt_addr,UINT32 flags,UINTN pages);
