#pragma once

#include "std_types.h"
#include "std_mem.h"
#include "types.h"
#include "extra.h"
#include "alloc.h"
#include "vmem.h"

gdt_tss_desc_t set_tss_desc(UINT64 base, UINT32 limit, UINT8 access, UINT8 flags)
{
    gdt_tss_desc_t desc;
    desc.limit_low = limit & 0xFFFF;
    desc.base_low = base & 0xFFFF;
    desc.base_mid = (base >> 16) & 0xFF;
    desc.access = access;
    desc.flags = (limit >> 16) & 0x0F;
    desc.flags |= (flags & 0xF0);
    desc.base_high = (base >> 24) & 0xFF;
    desc.base_upper = (base >> 32) & 0xFFFFFFFF;
    desc.reserved = 0;
    return desc;
}

void arch_load_to_kernel(kernel_handle_t handle)
{
    mmap_allocate_init(&handle.arch.alloc, &handle.arch.mmap);

    handle.arch.vmem.runtime_services = handle.arch.runtime_services;
    handle.arch.vmem.pml4 = (page_table_t *)mmap_allocate_pages(&handle.arch.alloc, 1);
    handle.arch.vmem.alloc = &handle.arch.alloc;
    handle.arch.vmem.offset = KERNEL_START_ADDRESS;
    handle.arch.vmem.page = 0;
    handle.arch.vmem.sc = &handle.kdata.screen_handle;

    vmem_identity_map_efi_mmap(&handle.arch.vmem);
    vmem_set_runtime_address_map(&handle.arch.vmem);

    vmem_map_pages(&handle.arch.vmem, handle.kdata.kernel_buffer, handle.kdata.kernel_size);

    for (UINTN i = 0; i < SIZE_TO_PAGES(handle.kdata.screen_handle.w * handle.kdata.screen_handle.h * 4); i++)
    {
        vmem_identity_map_page(&handle.arch.vmem, ((UINTN)handle.kdata.screen_handle.fb) + (i * PAGE_SIZE), &handle.arch.mmap);
    }

    handle.kdata.kernel_stack = mmap_allocate_pages(&handle.arch.alloc, KERNEL_STACK_SIZE);
    handle.kdata.kernel_stack = vmem_map_pages(&handle.arch.vmem, handle.kdata.kernel_stack, KERNEL_STACK_SIZE);

    memset(&handle.arch.tss, 0, sizeof(tss_t));
    handle.arch.tss.iomap_base = sizeof(tss_t);

    handle.arch.gdt.null = 0x0000000000000000;
    handle.arch.gdt.k_code = 0x00AF9A000000FFFF;
    handle.arch.gdt.k_data = 0x00CF92000000FFFF;
    handle.arch.gdt.u_code = 0x00AFFA000000FFFF;
    handle.arch.gdt.u_data = 0x00CFF2000000FFFF;

    handle.arch.gdt.tss.base_low = (((UINTN)&handle.arch.tss)) & 0xFFFF;
    handle.arch.gdt.tss.base_mid = (((UINTN)&handle.arch.tss) >> 16) & 0xFF;
    handle.arch.gdt.tss.base_high = (((UINTN)&handle.arch.tss) >> 24) & 0xFF;
    handle.arch.gdt.tss.base_upper = (((UINTN)&handle.arch.tss) >> 32) & 0xFFFFFFFF;

    handle.arch.gdt.tss.limit_low = sizeof(tss_t) - 1;
    handle.arch.gdt.tss.flags = 0x0;
    handle.arch.gdt.tss.access = 0x89;

    handle.arch.gdtr.ptr = (UINT64)&handle.arch.gdt;
    handle.arch.gdtr.size = sizeof(gdt_t) - 1;

    kernel_handle_t *handle_ptr = &handle;

    asm volatile(
        "cli\n"
        "movq %[pml4], %%CR3\n"
        "lgdt %[gdt]\n"
        "ltr %[tss]\n"
        "pushq $0x8\n"
        "leaq 1f(%%RIP), %%RAX\n"
        "pushq %%RAX\n"
        "lretq\n"
        "1:\n"
        "movq $0x10, %%RAX\n"
        "movq %%RAX, %%DS\n"
        "movq %%RAX, %%ES\n"
        "movq %%RAX, %%FS\n"
        "movq %%RAX, %%GS\n"
        "movq %%RAX, %%SS\n"
        "movq %[stack], %%RSP\n"
        "callq *%[entry]\n" ::
            [pml4] "r"(handle.arch.vmem.pml4),
        [gdt] "m"(handle.arch.gdtr), [tss] "r"((UINT16)0x28),
        [stack] "gm"(((UINTN)handle.kdata.kernel_stack) + KERNEL_STACK_SIZE * PAGE_SIZE),
        [entry] "r"(KERNEL_START_ADDRESS), "c"(handle_ptr)
        : "rax", "memory");

    no_interrupt_halt();
}