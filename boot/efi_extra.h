#pragma once

#include "efi.h"
#include "std_mem.h"
#include "printf.h"

EFI_HANDLE image_handle;
EFI_SYSTEM_TABLE *systab;
EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *cout;
EFI_SIMPLE_TEXT_INPUT_PROTOCOL *cin;
EFI_BOOT_SERVICES *boot_services;
EFI_RUNTIME_SERVICES *runtime_services;

EFI_GRAPHICS_OUTPUT_PROTOCOL *efi_graphics_protocol;
EFI_LOADED_IMAGE_PROTOCOL *efi_loaded_image;

EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *filesys;
EFI_FILE_PROTOCOL *root_file;

void *malloc(UINTN size)
{
    void *buffer = nullptr;
    boot_services->AllocatePool(EfiLoaderData, size, &buffer);
    return buffer;
}

void free(void *buffer)
{
    boot_services->FreePool(buffer);
}

__attribute__((always_inline)) void clear_terminal()
{
    cout->ClearScreen(cout);
}

void _putchar(CHAR16 chr)
{
    CHAR16 buffer[2] = {chr, '\0'};
    cout->OutputString(cout, buffer);
}

__attribute__((always_inline)) void *locate_protocol(EFI_GUID protocol)
{
    void *interface;
    boot_services->LocateProtocol(&protocol, NULL, &interface);
    return interface;
}

__attribute__((always_inline)) void *open_protocol(EFI_HANDLE handle, EFI_GUID protocol, EFI_HANDLE ahandle, EFI_HANDLE chandle, UINT32 attr)
{
    void *interface;
    boot_services->OpenProtocol(handle, &protocol, &interface, ahandle, chandle, attr);
    return interface;
}

void init_efi_protocols(EFI_HANDLE emain_img_hnd, EFI_SYSTEM_TABLE *emain_systab)
{
    image_handle = emain_img_hnd;
    systab = emain_systab;
    cout = systab->ConOut;
    cin = systab->ConIn;
    boot_services = systab->BootServices;
    runtime_services = systab->RuntimeServices;
    efi_graphics_protocol = (EFI_GRAPHICS_OUTPUT_PROTOCOL *)locate_protocol(EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID);
    efi_loaded_image = (EFI_LOADED_IMAGE_PROTOCOL *)open_protocol(image_handle, EFI_LOADED_IMAGE_PROTOCOL_GUID, image_handle, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    filesys = (EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *)open_protocol(efi_loaded_image->DeviceHandle, EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, image_handle, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    filesys->OpenVolume(filesys, &root_file);
}

void *read_file(const CHAR16 *path, UINTN *size)
{
    EFI_GUID info_guid = EFI_FILE_INFO_ID;
    EFI_FILE_PROTOCOL *file;
    EFI_FILE_INFO info;
    UINTN info_size = sizeof(EFI_FILE_INFO);
    void *buffer;

    root_file->Open(root_file, &file, (CHAR16 *)path, EFI_FILE_MODE_READ, 0);
    file->GetInfo(file, &info_guid, &info_size, &info);
    boot_services->AllocatePages(AllocateAnyPages, EfiLoaderData, SIZE_TO_PAGES(info.FileSize), (EFI_PHYSICAL_ADDRESS *)&buffer);
    file->Read(file, &info.FileSize, buffer);

    if (size != nullptr)
    {
        *size = info.FileSize;
    }

    return buffer;
}

EFI_INPUT_KEY get_key()
{
    EFI_EVENT events[1] = {cin->WaitForKey};
    EFI_INPUT_KEY key = {0};
    UINTN index = 0;
    boot_services->WaitForEvent(1, events, &index);
    cin->ReadKeyStroke(cin, &key);
    return key;
}

MEMORY_MAP_INFO get_memory_map()
{
    MEMORY_MAP_INFO mmap_data;
    MEMORY_MAP_INFO *mmap = &mmap_data;
    memset(mmap, 0, sizeof(MEMORY_MAP_INFO));
    boot_services->GetMemoryMap(&mmap->size, (EFI_MEMORY_DESCRIPTOR *)mmap->map, &mmap->key, &mmap->desc_size, &mmap->desc_version);
    mmap->size += mmap->desc_size * 2;
    boot_services->AllocatePool(EfiLoaderData, mmap->size, (VOID **)&mmap->map);
    boot_services->GetMemoryMap(&mmap->size, (EFI_MEMORY_DESCRIPTOR *)mmap->map, &mmap->key, &mmap->desc_size, &mmap->desc_version);
    return mmap_data;
}

UINTN count_files_entries_in_dir(EFI_FILE_PROTOCOL *dir)
{
    dir->SetPosition(dir, 0);
    UINTN count = 0;
    EFI_FILE_INFO file_info;
    UINTN buf_size = sizeof(EFI_FILE_INFO);
    dir->Read(dir, &buf_size, &file_info);
    while (buf_size > 0)
    {
        count++;
        buf_size = sizeof(EFI_FILE_INFO);
        dir->Read(dir, &buf_size, &file_info);
    }
    dir->SetPosition(dir, 0);
    return count;
}

EFI_FILE_INFO get_file_entry_in_dir(EFI_FILE_PROTOCOL *dir, UINTN index)
{
    EFI_FILE_INFO file_info;
    dir->SetPosition(dir, 0);
    UINTN count = 0;
    UINTN buf_size = sizeof(EFI_FILE_INFO);
    dir->Read(dir, &buf_size, &file_info);
    while (buf_size > 0)
    {
        if (count == index)
        {
            return file_info;
        }
        count++;
        buf_size = sizeof(EFI_FILE_INFO);
        dir->Read(dir, &buf_size, &file_info);
    }
    dir->SetPosition(dir, 0);

    return file_info;
}

void delete_file(const CHAR16 *path)
{
    EFI_FILE_PROTOCOL *file;
    root_file->Open(root_file, &file, (CHAR16 *)path, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0);
    file->Delete(file);
}
