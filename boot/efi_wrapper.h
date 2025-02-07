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

efi_t efi;

void _putchar(CHAR16 chr)
{
CHAR16 buf[2]={chr,0};
efi.cout->OutputString(efi.cout,buf);
}

void*locate_protocol(EFI_GUID protocol)
{
void*interface;
efi.bs->LocateProtocol(&protocol,NULL,&interface);
return interface;
}

void*open_protocol(EFI_HANDLE handle,EFI_GUID protocol,EFI_HANDLE ahandle,EFI_HANDLE chandle,UINT32 attr)
{
void*interface;
efi.bs->OpenProtocol(handle,&protocol,&interface,ahandle,chandle,attr);
return interface;
}

void*alloc_pages(UINTN pages,EFI_MEMORY_TYPE mt)
{
void*allocated;
efi.bs->AllocatePages(AllocateAnyPages,mt,pages,(EFI_PHYSICAL_ADDRESS*)&allocated);
return allocated;
}


EFI_FILE_PROTOCOL*get_root_file()
{
EFI_FILE_PROTOCOL*root;
efi.filesys->OpenVolume(efi.filesys,&root);
return root;
}

EFI_FILE_PROTOCOL*open_file(const CHAR16*path,UINT64 open,UINT64 attr)
{
EFI_FILE_PROTOCOL*root=get_root_file();
EFI_FILE_PROTOCOL*file=nullptr;
root->Open(root,&file,(CHAR16*)path,open,attr);
root->Close(root);
return file;
}


EFI_FILE_INFO get_file_info(EFI_FILE_PROTOCOL*file)
{
EFI_GUID guid=EFI_FILE_INFO_ID;
EFI_FILE_INFO file_info;
UINTN file_info_size=sizeof(EFI_FILE_INFO);
file->GetInfo(file,&guid,&file_info_size,&file_info);
return file_info;
}



void get_mmap(mmap_t*mmap)
{
memset(mmap,0,sizeof(mmap));

efi.bs->GetMemoryMap(&mmap->size,
(EFI_MEMORY_DESCRIPTOR*)mmap->map,
&mmap->key,
&mmap->desc_size,
&mmap->desc_ver);
mmap->size += mmap->desc_size * 2;  
efi.bs->AllocatePool(EfiLoaderData, mmap->size,(VOID **)&mmap->map);
efi.bs->GetMemoryMap(&mmap->size,
(EFI_MEMORY_DESCRIPTOR*)mmap->map,
&mmap->key,
&mmap->desc_size,
&mmap->desc_ver);

}