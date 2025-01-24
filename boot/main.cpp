#include "efi.h"
#include "utils.h"

#include "x86_64/boot.h"

boot_data_t data;

extern "C" EFI_STATUS emain(EFI_HANDLE image_handle,EFI_SYSTEM_TABLE*system_table)
{
init_efi(image_handle,system_table);

EFI_FILE_PROTOCOL*kernel_file;
EFI_FILE_PROTOCOL*root=get_root_file();
root->Open(root,&kernel_file,u"\\EFI\\BOOT\\KERNEL.BIN",EFI_FILE_MODE_READ,0);
root->Close(root);

EFI_FILE_INFO info=get_file_info(kernel_file);

data.kernel_pages=SIZE_TO_PAGES(info.FileSize);

efi.boot_services->AllocatePages(AllocateAnyPages,EfiLoaderCode,data.kernel_pages,(EFI_PHYSICAL_ADDRESS*)&data.kernel_code);

arch_boot_and_exit(&efi,&data);


return 0;
}