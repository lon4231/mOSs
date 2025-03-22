#include "boot.h"
#include "std_string.h"

void boot_to_kernel(kernel_args_t *kernel_args, boot_data_t *boot_data)
{
    kernel_args->gdt.null = 0x0000000000000000;
    kernel_args->gdt.kernel_code_64 = 0x00AF9A000000FFFF;
    kernel_args->gdt.kernel_data_64 = 0x00CF92000000FFFF;
    kernel_args->gdt.user_code_64 = 0x00AFFA000000FFFF;
    kernel_args->gdt.user_data_64 = 0x00CFF2000000FFFF;
    kernel_args->gdt.kernel_code_32 = 0x00CF9A000000FFFF;
    kernel_args->gdt.kernel_data_32 = 0x00CF92000000FFFF;
    kernel_args->gdt.user_code_32 = 0x00CFFA000000FFFF;
    kernel_args->gdt.user_data_32 = 0x00CFF2000000FFFF;

    UINT64 tss_base = (UINT64)&kernel_args->tss;
    UINT64 tss_limit = sizeof(kernel_args->tss) - 1;

    *((UINT64 *)&kernel_args->gdt.tss_segment) = 0x0000890000000067;
    kernel_args->gdt.tss_segment.base_15_0 = tss_base & 0xFFFF,
    kernel_args->gdt.tss_segment.base_23_16 = (tss_base >> 16) & 0xFF,
    kernel_args->gdt.tss_segment.base_31_24 = (tss_base >> 24) & 0xFF,
    kernel_args->gdt.tss_segment.base_63_32 = (tss_base >> 32) & 0xFFFFFFFF,

    kernel_args->gdtr.base = (UINT64)&kernel_args->gdt;
    kernel_args->gdtr.limit = sizeof(gdt_t) - 1;

    kernel_args->tss.io_map_base = sizeof(tss_t);

    kernel_args->idtr.base = (UINT64)&kernel_args->idt;
    kernel_args->idtr.limit = sizeof(idt_t) - 1;

    init_pmm(&kernel_args->pmm, &kernel_args->mmap);
    init_vmm(&kernel_args->vmm, &kernel_args->pmm);

    for (UINTN i = 0; i < (kernel_args->mmap.size / kernel_args->mmap.desc_size); ++i)
    {
        mmap_mem_desc_t *desc = (mmap_mem_desc_t *)(((UINT8 *)kernel_args->mmap.map) + (i * kernel_args->mmap.desc_size));
        if (desc->Type == 1)
        {
            vmm_map_pages(&kernel_args->vmm, (void *)desc->PhysicalStart, (void *)desc->PhysicalStart, 0b111, desc->NumberOfPages);
        }
    }

    kernel_args->dm.device_count=0;
    kernel_args->dm.head=nullptr;

    device_node_t *fb_device = (device_node_t *)pmm_request_page(&kernel_args->pmm);
    sgi_t *sgi = (sgi_t *)(&fb_device[1]);
    *sgi= boot_data->sgi;
    vmm_map_pages(&kernel_args->vmm,sgi->buffer,sgi->buffer,0b111,SIZE_TO_PAGES(sgi->width*sgi->height*sizeof(sgi_pixel_t)));
    fb_device->dev_id = DEVICE_ID_FRAMEBUFFER;
    fb_device->dev_data = sgi;

    vmm_map_pages(&kernel_args->vmm,fb_device,fb_device,0b111,1);

    add_device(&kernel_args->dm, fb_device);

    kernel_args->kernel_bin = vmm_map_higher_half(&kernel_args->vmm, kernel_args->kernel_bin, 0b111, kernel_args->kernel_bin_pages);
    kernel_args->kernel_stack = vmm_map_higher_half(&kernel_args->vmm, kernel_args->kernel_stack, 0b111, KERNEL_STACK_PAGES);
    kernel_args = (kernel_args_t *)vmm_map_higher_half(&kernel_args->vmm, kernel_args, 0b111, SIZE_TO_PAGES(sizeof(kernel_args_t)));

    memset(boot_data->sgi.buffer, 0, boot_data->sgi.width * boot_data->sgi.height * sizeof(sgi_pixel_t));

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

	"movq %[page_table], %%CR3;"
        
	"movq %[kstack], %%RSP;"
        "callq %[kernel_bin];" ::
	[gdt] "m"(kernel_args->gdtr),
        [tss] "r"(0x48),
        [idtr] "m"(kernel_args->idtr),
        [page_table] "r"(kernel_args->vmm.pml4),
        [kstack] "gm"(kernel_args->kernel_stack + (KERNEL_STACK_PAGES * PAGE_SIZE)),
        [kernel_bin] "r"(kernel_args->kernel_bin), "c"(kernel_args)
        : "rax", "memory");

    asm volatile("cli;hlt");
}
