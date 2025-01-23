#include "efi.h"
#include "utils.h"

#include "x86_64/boot.h"

extern "C" EFI_STATUS emain(EFI_HANDLE image_handle,EFI_SYSTEM_TABLE*system_table)
{
init_efi(image_handle,system_table);

arch_boot_and_exit(&efi);


return 0;
}