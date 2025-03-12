#pragma once

#include "efi.h"
#include "std_string.h"
#include "mmap.h"
#include "printf.h"

struct efi_t
{
EFI_SYSTEM_TABLE*               sys;
EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*cout;
EFI_BOOT_SERVICES*              bs;
EFI_RUNTIME_SERVICES*           rs;
EFI_LOADED_IMAGE_PROTOCOL*      loaded_image;
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL*filesys;
EFI_HANDLE                      img_handle;
};

efi_t*get_efi_context();

void _putchar(CHAR16 chr);
void*locate_protocol(EFI_GUID protocol);
void*open_protocol(EFI_HANDLE handle,EFI_GUID protocol,EFI_HANDLE ahandle,EFI_HANDLE chandle,UINT32 attr);
void*alloc_pages(UINTN pages,EFI_MEMORY_TYPE mt);
EFI_FILE_PROTOCOL*get_root_file();
EFI_FILE_PROTOCOL*open_file(const CHAR16*path,UINT64 open,UINT64 attr);
EFI_FILE_INFO get_file_info(EFI_FILE_PROTOCOL*file);
void get_mmap(mmap_t*mmap);
