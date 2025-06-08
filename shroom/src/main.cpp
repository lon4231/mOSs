#include <efi/efi.h>

extern "C" EFI_STATUS EFIAPI efi_main(EFI_HANDLE img_handle,EFI_SYSTEM_TABLE*systab)
{
    systab->ConOut->ClearScreen(systab->ConOut);
    while (true)
    {
    }
    


    return 0;
}