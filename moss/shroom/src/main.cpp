#include <efi/efi.h>
#include <efi_globals.h>
#include <cstr.h>

extern "C" EFI_STATUS EFIAPI efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *systab)
{
    init_efi_services(systab, img_handle);
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL px={255,255,255,255};
    
    for(uint32_t i=0;i<efi_graphics_output_protocol_count;++i)
    {
    efi_graphics_output_protocol_handles[i]->Blt(efi_graphics_output_protocol_handles[i],&px,EfiBltVideoFill,0,0,0,0,32,32,0);
    }
    while (true)
    {}
    
    

    return 0;
}