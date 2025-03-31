#include "efi_wrapper.h"

efi_t internal_efi;

efi_t *get_efi_context()
{
    return &internal_efi;
}

void _putchar(CHAR16 chr)
{
    CHAR16 buf[2] = {chr, 0};
    internal_efi.cout->OutputString(internal_efi.cout, buf);
}

void *locate_protocol(EFI_GUID protocol)
{
    void *interface;
    internal_efi.bs->LocateProtocol(&protocol, NULL, &interface);
    return interface;
}

void *open_protocol(EFI_HANDLE handle, EFI_GUID protocol, EFI_HANDLE ahandle, EFI_HANDLE chandle, UINT32 attr)
{
    void *interface;
    internal_efi.bs->OpenProtocol(handle, &protocol, &interface, ahandle, chandle, attr);
    return interface;
}

void *alloc_pages(UINTN pages, EFI_MEMORY_TYPE mt)
{
    void *allocated;
    internal_efi.bs->AllocatePages(AllocateAnyPages, mt, pages, (EFI_PHYSICAL_ADDRESS *)&allocated);
    return allocated;
}

void free_pages(void *address, UINTN pages)
{
    internal_efi.bs->FreePages((EFI_PHYSICAL_ADDRESS)address, pages);
}

EFI_FILE_PROTOCOL *get_root_file()
{
    EFI_FILE_PROTOCOL *root;
    internal_efi.filesys->OpenVolume(internal_efi.filesys, &root);
    return root;
}

EFI_FILE_PROTOCOL *open_file(const CHAR16 *path, UINT64 open, UINT64 attr)
{
    EFI_FILE_PROTOCOL *root = get_root_file();
    EFI_FILE_PROTOCOL *file = nullptr;
    root->Open(root, &file, (CHAR16 *)path, open, attr);
    root->Close(root);
    return file;
}

EFI_FILE_INFO get_file_info(EFI_FILE_PROTOCOL *file)
{
    EFI_GUID guid = EFI_FILE_INFO_ID;
    EFI_FILE_INFO file_info;
    UINTN file_info_size = sizeof(EFI_FILE_INFO);
    file->GetInfo(file, &guid, &file_info_size, &file_info);
    return file_info;
}

void get_mmap(mmap_t *mmap)
{
    memset(mmap, 0, sizeof(mmap));

    internal_efi.bs->GetMemoryMap(&mmap->size,
                                  (EFI_MEMORY_DESCRIPTOR *)mmap->map,
                                  &mmap->key,
                                  &mmap->desc_size,
                                  &mmap->desc_ver);
    mmap->size += mmap->desc_size * 2;
    mmap->map = (mmap_mem_desc_t *)alloc_pages(SIZE_TO_PAGES(mmap->size), EfiLoaderData);
    internal_efi.bs->GetMemoryMap(&mmap->size,
                                  (EFI_MEMORY_DESCRIPTOR *)mmap->map,
                                  &mmap->key,
                                  &mmap->desc_size,
                                  &mmap->desc_ver);
}
