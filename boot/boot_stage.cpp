#include "boot.h"
#include "std_string.h"


void boot_to_kernel(kernel_args_t *boot_data)
{
    boot_data->gdt.null = 0x0000000000000000;
    boot_data->gdt.kernel_code_64 = 0x00AF9A000000FFFF;
    boot_data->gdt.kernel_data_64 = 0x00CF92000000FFFF;
    boot_data->gdt.user_code_64 = 0x00AFFA000000FFFF;
    boot_data->gdt.user_data_64 = 0x00CFF2000000FFFF;
    boot_data->gdt.kernel_code_32 = 0x00CF9A000000FFFF;
    boot_data->gdt.kernel_data_32 = 0x00CF92000000FFFF;
    boot_data->gdt.user_code_32 = 0x00CFFA000000FFFF;
    boot_data->gdt.user_data_32 = 0x00CFF2000000FFFF;

    UINT64 tss_base = (UINT64)&boot_data->tss;
    UINT64 tss_limit = sizeof(boot_data->tss) - 1;

    *((UINT64 *)&boot_data->gdt.tss_segment) = 0x0000890000000067;
    boot_data->gdt.tss_segment.base_15_0 = tss_base & 0xFFFF,
    boot_data->gdt.tss_segment.base_23_16 = (tss_base >> 16) & 0xFF,
    boot_data->gdt.tss_segment.base_31_24 = (tss_base >> 24) & 0xFF,
    boot_data->gdt.tss_segment.base_63_32 = (tss_base >> 32) & 0xFFFFFFFF,

    boot_data->gdtr.base = (UINT64)&boot_data->gdt;
    boot_data->gdtr.limit = sizeof(gdt_t) - 1;

    boot_data->tss.io_map_base = sizeof(tss_t);

    boot_data->idtr.base = (UINT64)&boot_data->idt;
    boot_data->idtr.limit = sizeof(idt_t) - 1;

    init_pmm(&boot_data->pmm, &boot_data->mmap);
    init_vmm(&boot_data->vmm, &boot_data->pmm);


    for(UINTN i=0;i<(boot_data->mmap.size/boot_data->mmap.desc_size);++i)
    {
        mmap_mem_desc_t*desc=(mmap_mem_desc_t*)(((UINT8*)boot_data->mmap.map)+(i*boot_data->mmap.desc_size));
        if(desc->Type==1)
        {vmm_map_pages(&boot_data->vmm,(void*)desc->PhysicalStart,(void*)desc->PhysicalStart,0b111,desc->NumberOfPages);}
    }

    boot_data->kernel_bin=vmm_map_higher_half(&boot_data->vmm,boot_data->kernel_bin,0b111,boot_data->kernel_bin_pages);
    boot_data->kernel_stack=vmm_map_higher_half(&boot_data->vmm,boot_data->kernel_stack,0b111,KERNEL_STACK_PAGES);
    boot_data=(kernel_args_t*)vmm_map_higher_half(&boot_data->vmm,boot_data,0b111,SIZE_TO_PAGES(sizeof(kernel_args_t)));


    asm volatile(
        "cli;"
        "lgdt %[gdt];"
        "ltr %[tss];"
        "lidt %[idtr];"
        
        "pushq $0x8;"
        "leaq 1f(%%RIP), %%RAX;"
        "pushq %%RAX;"
        "lretq;"
        
        "1:;"
        "movq $0x10, %%RAX;"
        "movq %%RAX, %%DS;"
        "movq %%RAX, %%ES;"
        "movq %%RAX, %%FS;"
        "movq %%RAX, %%GS;"
        "movq %%RAX, %%SS;"
        
        
        "movq %[page_table],%%CR3;"
        "movq %[kstack], %%RSP;"
        "callq %[kernel_bin];" ::
        [gdt] "m"(boot_data->gdtr),
        [tss] "r"(0x48),
        [idtr] "m"(boot_data->idtr),
        [page_table]"r"(boot_data->vmm.pml4),
        [kstack] "gm"(boot_data->kernel_stack + (KERNEL_STACK_PAGES * PAGE_SIZE)),
        [kernel_bin] "r"(boot_data->kernel_bin), "c"(boot_data)
        : "rax", "memory");

    asm volatile("cli;hlt");
}
