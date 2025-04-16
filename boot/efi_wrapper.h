#pragma once

#include "efi.h"
#include "std_string.h"
#include "printf.h"

#define SIZE_TO_PAGES(x) (((x) + (PAGE_SIZE) - 1) / (PAGE_SIZE))

struct mmap_mem_desc_t
{
    UINT32 Type;
    UINT64 PhysicalStart;
    UINT64 VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
};

struct mmap_t
{
    UINTN size;
    mmap_mem_desc_t *map;
    UINTN key;
    UINTN desc_size;
    UINT32 desc_ver;
};



struct efi_t
{
    EFI_SYSTEM_TABLE *sys;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *cout;
    EFI_BOOT_SERVICES *bs;
    EFI_RUNTIME_SERVICES *rs;
    EFI_LOADED_IMAGE_PROTOCOL *loaded_image;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *filesys;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
    EFI_HANDLE img_handle;
};

struct xsdp_t 
{
char Signature[8];
uint8_t Checksum;
char OEMID[6];
uint8_t Revision;
uint32_t RsdtAddress;   
uint32_t Length;
uint64_t XsdtAddress;
uint8_t ExtendedChecksum;
uint8_t reserved[3];
}__attribute__ ((packed));

efi_t *get_efi_context();

void _putchar(CHAR16 chr);
void *locate_protocol(EFI_GUID protocol);
void *open_protocol(EFI_HANDLE handle, EFI_GUID protocol, EFI_HANDLE ahandle, EFI_HANDLE chandle, UINT32 attr);
void *alloc_pages(UINTN pages, EFI_MEMORY_TYPE mt);
EFI_FILE_PROTOCOL *get_root_file();
EFI_FILE_PROTOCOL *open_file(const CHAR16 *path, UINT64 open, UINT64 attr);
EFI_FILE_INFO get_file_info(EFI_FILE_PROTOCOL *file);
void get_mmap(mmap_t *mmap);
