#include "virtual_memory.h"
#include "std_string.h"

#define PHYS_ADDR_MASK 0x000FFFFFFFFFF000

void init_vmm(vmm_handle_t *vmm, pmm_handle_t *pmm)
{
    vmm->pmm = pmm;
    vmm->pml4 = (page_table_t *)pmm_request_page(pmm);
    memset(vmm->pml4, 0, sizeof(page_table_t));
    vmm->higher_half_index = 0;
}

void vmm_map_page(vmm_handle_t *vmm, void *phys_addr, void *virt_addr, UINT32 flags)
{

    UINT64 pml4_index = (((UINT64)virt_addr) >> 39) & 0x1FF;
    UINT64 pdpt_index = (((UINT64)virt_addr) >> 30) & 0x1FF;
    UINT64 pdt_index = (((UINT64)virt_addr) >> 21) & 0x1FF;
    UINT64 pt_index = (((UINT64)virt_addr) >> 12) & 0x1FF;

    if (!(vmm->pml4->entries[pml4_index].value & PAGE_TABLE_FLAGS_PRESENT))
    {
        void *pdpt_page = nullptr;
        pdpt_page = pmm_request_page(vmm->pmm);
        memset(pdpt_page, 0, sizeof(page_table_t));
        vmm->pml4->entries[pml4_index].value = (UINT64)pdpt_page | flags;
    }

    page_table_t *pdpt = (page_table_t *)(vmm->pml4->entries[pml4_index].value & PHYS_ADDR_MASK);
    if (!(pdpt->entries[pdpt_index].value & PAGE_TABLE_FLAGS_PRESENT))
    {
        void *pdt_page = nullptr;
        pdt_page = pmm_request_page(vmm->pmm);
        memset(pdt_page, 0, sizeof(page_table_t));
        pdpt->entries[pdpt_index].value = (UINT64)pdt_page | flags;
    }

    page_table_t *pdt = (page_table_t *)(pdpt->entries[pdpt_index].value & PHYS_ADDR_MASK);
    if (!(pdt->entries[pdt_index].value & PAGE_TABLE_FLAGS_PRESENT))
    {
        void *pt_page = nullptr;
        pt_page = pmm_request_page(vmm->pmm);
        memset(pt_page, 0, sizeof(page_table_t));
        pdt->entries[pdt_index].value = (UINT64)pt_page | flags;
    }

    page_table_t *pt = (page_table_t *)(pdt->entries[pdt_index].value & PHYS_ADDR_MASK);
    pt->entries[pt_index].value = ((UINT64)phys_addr & PHYS_ADDR_MASK) | flags;
}

void vmm_map_pages(vmm_handle_t *vmm, void *phys_addr, void *virt_addr, UINT32 flags, UINTN pages)
{
    for (UINTN i = 0; i < pages; ++i)
    {
        vmm_map_page(vmm, ((UINT8 *)phys_addr) + (i * PAGE_SIZE), ((UINT8 *)virt_addr) + (i * PAGE_SIZE), flags);
    }
}

void *vmm_map_higher_half(vmm_handle_t *vmm, void *phys_addr, UINT32 flags, UINTN pages)
{
    void *virt_addr = (void *)(HIGHER_HALF_START_ADDRESS + (vmm->higher_half_index * PAGE_SIZE));
    vmm_map_pages(vmm, phys_addr, virt_addr, flags, pages);
    vmm->higher_half_index += pages;
    return virt_addr;
}

void *virt_to_phys_addr(vmm_handle_t *vmm, void *virt_addr)
{
    UINT64 pml4_index = (((UINT64)virt_addr) >> 39) & 0x1FF;
    UINT64 pdpt_index = (((UINT64)virt_addr) >> 30) & 0x1FF;
    UINT64 pdt_index = (((UINT64)virt_addr) >> 21) & 0x1FF;
    UINT64 pt_index = (((UINT64)virt_addr) >> 12) & 0x1FF;

    page_table_t *pdpt = (page_table_t *)(vmm->pml4->entries[pml4_index].value & PHYS_ADDR_MASK);
    if (pdpt == nullptr)
    {
        return nullptr;
    }

    page_table_t *pdt = (page_table_t *)(pdpt->entries[pdpt_index].value & PHYS_ADDR_MASK);
    if (pdt == nullptr)
    {
        return nullptr;
    }

    page_table_t *pt = (page_table_t *)(pdt->entries[pdt_index].value & PHYS_ADDR_MASK);
    if (pt == nullptr)
    {
        return nullptr;
    }

    return (void *)(pt->entries[pt_index].value & PHYS_ADDR_MASK);
}
