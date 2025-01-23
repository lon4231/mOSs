#pragma once

#include "efi.h"
#include "std_string.h"
#include "x86_64/arch.h"

struct efi_t
{
    EFI_HANDLE image_handle;
    EFI_SYSTEM_TABLE *system_table;
    EFI_BOOT_SERVICES *boot_services;
    EFI_RUNTIME_SERVICES *runtime_services;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *graphics_output_protocol;
    EFI_LOADED_IMAGE_PROTOCOL*loaded_image;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL*file_system;
};

efi_t efi;

void *locate_protocol(EFI_GUID protocol)
{
    void *interface;
    efi.boot_services->LocateProtocol(&protocol, NULL, &interface);
    return interface;
}

void*open_protocol(EFI_HANDLE handle,EFI_GUID protocol,EFI_HANDLE ahandle,EFI_HANDLE chandle,UINT32 attr)
{
void*interface;
efi.boot_services->OpenProtocol(handle,&protocol,&interface,ahandle,chandle,attr);
return interface;
}

void init_efi(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *systab)
{
    efi.system_table = systab;
    efi.boot_services = systab->BootServices;
    efi.runtime_services = systab->RuntimeServices;
    efi.image_handle = img_handle;
    efi.graphics_output_protocol = (EFI_GRAPHICS_OUTPUT_PROTOCOL *)locate_protocol(EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID);
    efi.loaded_image=(EFI_LOADED_IMAGE_PROTOCOL*)open_protocol(efi.image_handle,EFI_LOADED_IMAGE_PROTOCOL_GUID,efi.image_handle,NULL,EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    efi.file_system=(EFI_SIMPLE_FILE_SYSTEM_PROTOCOL*)open_protocol(efi.loaded_image->DeviceHandle,EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID,efi.image_handle,NULL,EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);

    efi.system_table->ConOut->ClearScreen(efi.system_table->ConOut);
    efi.system_table->ConOut->OutputString(efi.system_table->ConOut,u"SHROOM BOOT 1.0v");


}

EFI_FILE_PROTOCOL*get_root_file()
{
EFI_FILE_PROTOCOL*root;
efi.file_system->OpenVolume(efi.file_system,&root);
return root;
}

MEMORY_MAP_INFO get_memory_map()
{
MEMORY_MAP_INFO mmap_data;
MEMORY_MAP_INFO*mmap=&mmap_data;
memset(mmap,0,sizeof(MEMORY_MAP_INFO));
efi.boot_services->GetMemoryMap(&mmap->size,(EFI_MEMORY_DESCRIPTOR*)mmap->map,&mmap->key,&mmap->desc_size,&mmap->desc_version);
mmap->size+=mmap->desc_size*2;
efi.boot_services->AllocatePool(EfiLoaderData,mmap->size,(VOID**)&mmap->map);
efi.boot_services->GetMemoryMap(&mmap->size,(EFI_MEMORY_DESCRIPTOR*)mmap->map,&mmap->key,&mmap->desc_size,&mmap->desc_version);
return mmap_data;
}