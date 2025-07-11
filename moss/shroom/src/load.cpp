#include <kernel.h>
#include <efi_globals.h>
#include <allocator.h>
#include <virtual_map.h>

typedef void (*kernel_entry_t)(kernel_arguments_t *kargs);

void *kernel_file_buffer;

alloc_handle_t alloc_handle;
vmem_table_t vmm_handle;
kernel_arguments_t *kargs;

uint64_t hh_addr;

void map_hh_continous(vmem_table_t *vmm, void *phys, uint64_t pages)
{
    for (uint64_t i = 0; i < pages; ++i)
    {
        map_page(vmm, phys, (void *)hh_addr, 0b111);
        hh_addr += PAGE_SIZE;
    }
}

EFI_FILE_INFO get_file_info(EFI_FILE_PROTOCOL *file)
{
    EFI_FILE_INFO info;

    UINTN info_size = sizeof(EFI_FILE_INFO);
    EFI_GUID guid = EFI_FILE_INFO_ID;

    file->GetInfo(file, &guid, &info_size, &info);

    return info;
}

void load_kernel(const char16_t *path)
{

    EFI_FILE_PROTOCOL *kernel_file;
    EFI_FILE_INFO kernel_file_info;

    {
        EFI_FILE_PROTOCOL *root_file;
        efi_fs_protocol_handle->OpenVolume(efi_fs_protocol_handle, &root_file);
        root_file->Open(root_file, &kernel_file, (char16_t *)path, EFI_FILE_MODE_READ, 0);
        root_file->Close(root_file);
        kernel_file_info = get_file_info(kernel_file);
    }

    efi_boot_services_handle->AllocatePages(AllocateAnyPages, EfiLoaderData, SIZE_TO_PAGES(kernel_file_info.FileSize), (EFI_PHYSICAL_ADDRESS *)&kernel_file_buffer);

    kernel_file->Read(kernel_file, &kernel_file_info.FileSize, kernel_file_buffer);

    kernel_file->Close(kernel_file);
}

void get_mmap(memory_map_info_t *mmap)
{
    memset(mmap, 0, sizeof(memory_map_info_t));
    efi_boot_services_handle->GetMemoryMap(&mmap->size, mmap->map, &mmap->key, &mmap->desc_size, &mmap->desc_version);
    mmap->size += mmap->desc_size * 2;
    efi_boot_services_handle->AllocatePages(AllocateAnyPages, EfiLoaderData, SIZE_TO_PAGES(mmap->size), (EFI_PHYSICAL_ADDRESS *)&mmap->map);
    efi_boot_services_handle->GetMemoryMap(&mmap->size, mmap->map, &mmap->key, &mmap->desc_size, &mmap->desc_version);
    mmap->entry_count = (mmap->size / mmap->desc_size);
}

void build_boot_mmap()
{
    memory_map_info_t *mmap = &alloc_handle.mmap;
}

void jump_to_kernel(kernel_arguments_t *args)
{
    gdt_t gdt;
    tss_t tss;
    gdtr_t gdtr;
    void *kernel_stack;
    uint64_t kernel_stack_size;

    kargs = args;

    load_kernel(u"\\EFI\\BOOT\\kernel.elf");

    Elf64_Ehdr *elf_ehdr = (Elf64_Ehdr *)kernel_file_buffer;
    Elf64_Shdr *elf_shdrs = (Elf64_Shdr *)(((uint8_t *)kernel_file_buffer) + elf_ehdr->e_shoff);
    Elf64_Phdr *elf_phdrs = (Elf64_Phdr *)(((uint8_t *)kernel_file_buffer) + elf_ehdr->e_phoff);
    char *elf_strtab = ((char *)kernel_file_buffer + elf_shdrs[elf_ehdr->e_shstrndx].sh_offset);

    hh_addr = 0;
    for (UINTN i = 0; i < elf_ehdr->e_phnum; ++i)
    {
        if (elf_phdrs[i].p_type != PT_LOAD)
            continue;

        if (hh_addr < elf_phdrs[i].p_vaddr)
        {
            hh_addr = elf_phdrs[i].p_vaddr;
        }
    }

    /*SEPARATOR*/

    get_mmap(&alloc_handle.mmap);

    efi_boot_services_handle->ExitBootServices(efi_image_handle, alloc_handle.mmap.key);

    init_allocator(&alloc_handle);
    init_vmem_table(&vmm_handle, &alloc_handle);

    for (UINTN i = 0; i < alloc_handle.mmap.entry_count; ++i)
    {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)(((uint8_t *)alloc_handle.mmap.map) + (i * alloc_handle.mmap.desc_size));

        if ((desc->Type == EfiLoaderCode) || (desc->Type == EfiLoaderData) || (desc->Type == EfiBootServicesCode) || (desc->Type == EfiBootServicesData) || (desc->Type == EfiConventionalMemory))
        {
            for (UINT64 n = 0; n < desc->NumberOfPages; ++n)
            {
                map_page(&vmm_handle, (void *)(desc->PhysicalStart + (n * PAGE_SIZE)), (void *)(desc->PhysicalStart + (n * PAGE_SIZE)), 0b111);
            }
        }
    }

    build_boot_mmap();

    for (UINTN i = 0; i < elf_ehdr->e_phnum; ++i)
    {

        if (elf_phdrs[i].p_type != PT_LOAD)
            continue;

        uint64_t to_write = elf_phdrs[i].p_filesz;
        for (uint64_t n = 0; n < SIZE_TO_PAGES(elf_phdrs[i].p_memsz); ++n)
        {
            void *new_page = alloc_page(&alloc_handle);
            memset(new_page, 0, PAGE_SIZE);

            memcpy(new_page, (void *)((uint64_t)kernel_file_buffer + elf_phdrs[i].p_offset + (elf_phdrs[i].p_filesz - to_write)), (to_write > PAGE_SIZE) ? PAGE_SIZE : to_write);
            (to_write > PAGE_SIZE) ? (to_write -= PAGE_SIZE) : (to_write = 0);

            map_hh_continous(&vmm_handle, new_page, 1);
        }

        kernel_stack_size = (elf_phdrs[i].p_vaddr + (SIZE_TO_PAGES(elf_phdrs[i].p_memsz) * PAGE_SIZE));
    }

    for (uint8_t i = 0; i < SETUP_STACK_SIZE; ++i)
    {
        void *new_page = alloc_page(&alloc_handle);
        memset(new_page, 0, PAGE_SIZE);

        map_hh_continous(&vmm_handle, new_page, 1);
    }
    kernel_stack_size = SETUP_STACK_SIZE * PAGE_SIZE;
    
    for (UINTN i = 0; i < alloc_handle.mmap.entry_count; ++i)
    {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)(((uint8_t *)alloc_handle.mmap.map) + (i * alloc_handle.mmap.desc_size));

        if (desc->Type == EfiConventionalMemory)
        {
            map_hh_continous(&vmm_handle,(void*)desc->PhysicalStart,desc->NumberOfPages);
        }
    }

    gdt =
        {
            .null = 0x0000000000000000,
            .kernel_code = 0x00AF9A000000FFFF,
            .kernel_data = 0x00CF92000000FFFF,
            .user_code = 0x00AFFA000000FFFF,
            .user_data = 0x00CFF2000000FFFF,
        };

    gdt.tss_entry.entry =
        ((sizeof(tss_t) - 1) & 0xFFFF) |
        ((((uint64_t)&tss) & 0xFFFF) << 16) |
        ((((uint64_t)&tss) & 0xFF0000) << 16) |
        ((uint64_t)0x89 << 40) |
        ((uint64_t)(((uint64_t)&tss) & 0xFF000000) << 32);

    gdt.tss_entry.ext_base = (((uint64_t)&tss) >> 32) & 0xFFFFFFFF;

    memset(&tss, 0, sizeof(tss_t));
    tss.io_map_base = sizeof(tss_t);

    gdtr.base = (uint64_t)&gdt;
    gdtr.limit = sizeof(gdt_t) - 1;

    asm volatile("cli\n");

    SET_CR3(vmm_handle.pml4);
    SET_GDT(gdtr);
    SET_TSS(0x28);
    SWITCH_GDT_SEG(0x8, 0x10);
    SET_STACK((uint64_t)kernel_stack + kernel_stack_size);

    asm volatile(
        "callq *%[entry]\n" ::
            [entry] "r"(elf_ehdr->e_entry),
        "c"(args));
}