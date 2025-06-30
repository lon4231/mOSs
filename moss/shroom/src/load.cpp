#include <kernel.h>
#include <efi_globals.h>
#include <allocator.h>

void *kernel_file_buffer;

alloc_handle_t alloc_handle;

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

    efi_boot_services_handle->AllocatePool(EfiLoaderData, kernel_file_info.FileSize, &kernel_file_buffer);

    kernel_file->Read(kernel_file, &kernel_file_info.FileSize, kernel_file_buffer);

    kernel_file->Close(kernel_file);
}

void get_mmap(memory_map_info_t *mmap)
{
    memset(mmap, 0, sizeof(memory_map_info_t));
    efi_boot_services_handle->GetMemoryMap(&mmap->size, mmap->map, &mmap->key, &mmap->desc_size, &mmap->desc_version);
    mmap->size += mmap->desc_size * 2;
    efi_boot_services_handle->AllocatePool(EfiLoaderData, mmap->size, (VOID **)&mmap->map);
    efi_boot_services_handle->GetMemoryMap(&mmap->size, mmap->map, &mmap->key, &mmap->desc_size, &mmap->desc_version);
    mmap->entry_count = (mmap->size / mmap->desc_size);
}

void jump_to_kernel(kernel_arguments_t *args)
{
    load_kernel(u"\\EFI\\BOOT\\kernel.elf");

    Elf64_Ehdr *elf_ehdr = (Elf64_Ehdr *)kernel_file_buffer;
    Elf64_Shdr *elf_shdrs = (Elf64_Shdr *)(((uint8_t *)kernel_file_buffer) + elf_ehdr->e_shoff);
    Elf64_Phdr *elf_phdrs = (Elf64_Phdr *)(((uint8_t *)kernel_file_buffer) + elf_ehdr->e_phoff);

    char *elf_strtab = ((char *)kernel_file_buffer + elf_shdrs[elf_ehdr->e_shstrndx].sh_offset);

    printf("kernel entry    : 0x%016llx\r\n", elf_ehdr->e_entry);

    printf(" |           name           -   size   -  flag  | \r\n");
    for (Elf64_Half i = 0; i < elf_ehdr->e_shnum; ++i)
    {
        printf(" | %24s -  0x%04llx  - 0x%04llx |\r\n", &elf_strtab[elf_shdrs[i].sh_name], elf_shdrs[i].sh_size, elf_shdrs[i].sh_flags);
    }

    get_mmap(&alloc_handle.mmap);

    efi_boot_services_handle->ExitBootServices(efi_image_handle, alloc_handle.mmap.key);

    init_allocator(&alloc_handle);

    

    asm volatile("cli;hlt");

}