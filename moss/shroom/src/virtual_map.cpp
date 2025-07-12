#include <virtual_map.h>


void init_vmem_table(vmem_table_t*vmm,alloc_handle_t*allocator)
{
vmm->allocator=allocator;
vmm->pml4=(page_table_t*)alloc_page(vmm->allocator);
memset(vmm->pml4,0,sizeof(page_table_t));
}

void*map_page(vmem_table_t*vmm,void*phys_addr,void*virt_addr,uint16_t flags)
{
uint16_t pt_root_index=((uint64_t)virt_addr>>39)&0x1FF;
uint16_t pt_l3_index=((uint64_t)virt_addr>>30)&0x1FF;
uint16_t pt_l2_index=((uint64_t)virt_addr>>21)&0x1FF;
uint16_t pt_l1_index=((uint64_t)virt_addr>>12)&0x1FF;

if((vmm->pml4->entries[pt_root_index]&1)!=1)
{
void*new_l3_page_table=alloc_page(vmm->allocator);
memset(new_l3_page_table,0,sizeof(page_table_t));
vmm->pml4->entries[pt_root_index]=(((uint64_t)new_l3_page_table)&0x000FFFFFFFFFF000)|(flags&0xFFF);
}
page_table_t*pt_l3_table=(page_table_t*)(vmm->pml4->entries[pt_root_index]&0x000FFFFFFFFFF000);

if((pt_l3_table->entries[pt_l3_index]&1)!=1)
{
void*new_l2_page_table=alloc_page(vmm->allocator);
memset(new_l2_page_table,0,sizeof(page_table_t));
pt_l3_table->entries[pt_l3_index]=(((uint64_t)new_l2_page_table)&0x000FFFFFFFFFF000)|(flags&0xFFF);
}
page_table_t*pt_l2_table=(page_table_t*)(pt_l3_table->entries[pt_l3_index]&0x000FFFFFFFFFF000);

if((pt_l2_table->entries[pt_l2_index]&1)!=1)
{
void*new_l1_page_table=alloc_page(vmm->allocator);
memset(new_l1_page_table,0,sizeof(page_table_t));
pt_l2_table->entries[pt_l2_index]=(((uint64_t)new_l1_page_table)&0x000FFFFFFFFFF000)|(flags&0xFFF);
}
page_table_t*pt_l1_table=(page_table_t*)(pt_l2_table->entries[pt_l2_index]&0x000FFFFFFFFFF000);

pt_l1_table->entries[pt_l1_index] = ((uint64_t)phys_addr & 0x000FFFFFFFFFF000) | (flags & 0xFFF);


return virt_addr;
}