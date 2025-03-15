#include "std_types.h"

struct page_table_entry_t
{
union
{
UINT64 value;
struct
{
UINT64 present    :1;
UINT64 rw         :1;
UINT64 user       :1;
UINT64 pwt        :1;
UINT64 pcd        :1;
UINT64 accessed   :1;
UINT64 dirty      :1;
UINT64 pat        :1;
UINT64 global     :1;
UINT64 available  :3;
UINT64 frame      :40;
UINT64 reserved   :11;
UINT64 nx         :1;
};
};
}__attribute__((packed));

struct page_table_t
{
page_table_entry_t entries[512];
}__attribute__((packed));

typedef void(*virtual_memory_page_request)();

struct vmem_handle_t
{
virtual_memory_page_request request_page;
page_table_t*pml4;
};

void vmem_map_page(vmem_handle_t*vmem,void*phys_addr,void*virt_addr,UINT32 flags);