#include "efi_globals.h"

EFI_SYSTEM_TABLE *efi_systab_handle;

EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *efi_cout_handle;
EFI_SIMPLE_TEXT_INPUT_PROTOCOL *efi_cin_handle;

EFI_BOOT_SERVICES *efi_boot_services_handle;
EFI_RUNTIME_SERVICES *efi_runtime_services_handle;

EFI_LOADED_IMAGE_PROTOCOL* efi_loaded_image_protocol;
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *efi_fs_protocol_handle;
EFI_HANDLE efi_image_handle;


void *locate_efi_protocol(EFI_GUID guid)
{
    void *interface;
    efi_boot_services_handle->LocateProtocol(&guid, NULL, &interface);
    return interface;
}

void *locate_efi_protocols(EFI_GUID guid, UINTN *interface_count)
{
    void **interfaces;
    efi_boot_services_handle->LocateHandleBuffer(ByProtocol, &guid, NULL, interface_count, &interfaces);
    for (UINTN i=0;i<*interface_count;++i)
    {
        efi_boot_services_handle->OpenProtocol(interfaces[i],&guid,&interfaces[i],efi_image_handle,NULL,EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    }
    
    return interfaces;
}

void*open_protocol(EFI_HANDLE handle,EFI_GUID guid,UINT32 mode)
{
void*interface;
efi_boot_services_handle->OpenProtocol(handle,&guid,&interface,efi_image_handle,NULL,mode);
return interface;
}

void init_efi_services(EFI_SYSTEM_TABLE *systab, EFI_HANDLE img_handle)
{
    efi_systab_handle = systab;
    efi_image_handle = img_handle;

    efi_cout_handle = systab->ConOut;
    efi_cin_handle = systab->ConIn;

    efi_boot_services_handle = systab->BootServices;
    efi_runtime_services_handle = systab->RuntimeServices;

    efi_loaded_image_protocol=(EFI_LOADED_IMAGE_PROTOCOL*)open_protocol(img_handle,EFI_LOADED_IMAGE_PROTOCOL_GUID,EFI_OPEN_PROTOCOL_GET_PROTOCOL);

    efi_fs_protocol_handle=(EFI_SIMPLE_FILE_SYSTEM_PROTOCOL*)open_protocol(efi_loaded_image_protocol->DeviceHandle,EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID,EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    
}
