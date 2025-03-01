#include "efi.h"
#include "efi_wrapper.h"
#include "pmm.h"

struct boot_handle_t
{
void*kernel_bin;
UINTN kernel_bin_pages;
};

boot_handle_t setup_boot_handle()
{
boot_handle_t boot_handle;

EFI_FILE_PROTOCOL*kernel_file=open_file(u"\\EFI\\BOOT\\kernel.bin",EFI_FILE_MODE_READ,0);
EFI_FILE_INFO kernel_file_info=get_file_info(kernel_file);

boot_handle.kernel_bin_pages=SIZE_TO_PAGES(kernel_file_info.FileSize)+4;
boot_handle.kernel_bin=alloc_pages(boot_handle.kernel_bin_pages,EfiLoaderData);
memset(boot_handle.kernel_bin,0,boot_handle.kernel_bin_pages*PAGE_SIZE);

kernel_file->Read(kernel_file,&kernel_file_info.FileSize,boot_handle.kernel_bin);
kernel_file->Close(kernel_file);

return boot_handle;
}

void exit_bootloader(boot_handle_t*handle)
{
mmap_t mmap;
pmm_t pmm;
UINTN usable_memory=0;
UINTN total_pages=0;

get_mmap(&mmap);

for(UINTN i=0;i<(mmap.size/mmap.desc_size);++i)
{
mmap_mem_desc_t*desc=(mmap_mem_desc_t*)(((UINT8*)mmap.map)+(i*mmap.desc_size));
if(desc->Type==EfiConventionalMemory)
{usable_memory+=(desc->NumberOfPages*PAGE_SIZE)/(1024*1024);total_pages+=desc->NumberOfPages;}
}

printf(u"usable memory: %u MiB",usable_memory);

init_pmm(&pmm,&mmap);



}