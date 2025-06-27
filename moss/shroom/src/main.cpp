#include <efi/efi.h>
#include <efi_globals.h>
#include <cstr.h>
#include <kernel.h>

extern "C" EFI_STATUS EFIAPI efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *systab)
{
    init_efi_services(systab, img_handle);

    kernel_handle_t kernel_handle;
    load_kernel(&kernel_handle,u"\\EFI\\BOOT\\kernel.elf");

    efi_cout_handle->ClearScreen(efi_cout_handle);

    while (true)
    {}
    
    

    return 0;
}