#include "efi.h"
#include "efi_extra.h"
#include "std_driver.h"

#include "binc.h"

const CHAR16*menu_options[]=
{
u"boot         ",
u"delete kernel",
u"shutdown     ",
};

void boot()
{
kernel_handle_t handle;

UINTN kernel_pages=0;
void*kernel_buffer=read_file(u"\\EFI\\BOOT\\KERNEL.KRN",&kernel_pages,4);
kernel_pages=SIZE_TO_PAGES(kernel_pages)+4;


UINTN driver_count=0;
UINTN*driver_pages=nullptr;
void**driver_buffers=nullptr;

EFI_FILE_PROTOCOL*driver_dir;

EFI_STATUS status=root_file->Open(root_file,&driver_dir,u"\\DRIVER\\",EFI_FILE_MODE_READ,0);
if(status==0)
{
CHAR16 path[32]=u"\\DRIVER\\";

driver_count=count_files_entries_in_dir(driver_dir)-2;

driver_buffers=(void**)malloc(driver_count*sizeof(void*));
driver_pages=(UINTN*)malloc(driver_count*sizeof(UINTN));

for(UINTN i=0;i<driver_count;++i)
{
EFI_FILE_INFO info=get_file_entry_in_dir(driver_dir,i+2);

c16_strcpy(&path[8],info.FileName);

driver_buffers[i]=read_file(path,&driver_pages[i],2);
driver_pages[i]=SIZE_TO_PAGES(driver_pages[i]);
}
}

handle.arch.mmap=get_memory_map();
handle.kdata.kernel_buffer=kernel_buffer;
handle.kdata.kernel_size=kernel_pages;

handle.kdata.driver_count=driver_count;
handle.kdata.driver_buffers=driver_buffers;
handle.kdata.driver_pages_count=driver_pages;

handle.arch.runtime_services=(KRN_RUNTIME_SERVICES*)runtime_services;

handle.kdata.screen_handle.fb=(UINT32*)efi_graphics_protocol->Mode->FrameBufferBase;
handle.kdata.screen_handle.w =efi_graphics_protocol->Mode->Info->PixelsPerScanLine;
handle.kdata.screen_handle.h =efi_graphics_protocol->Mode->Info->VerticalResolution;

for(UINTN i=0;i<systab->NumberOfTableEntries;++i)
{
if(strcmp((const char*)(systab->ConfigurationTable[i].VendorTable),"RSD PTR ",8)==0)
{
rsdp_t*rsdp=(rsdp_t*)systab->ConfigurationTable[i].VendorTable;
if(rsdp->Revision>0)
{handle.arch.xsdp=(xsdp_t*)rsdp;}
}
}
if(handle.arch.xsdp==NULL)
{
printf(u"no XSDP found... ):");
no_interrupt_halt();
}



boot_services->ExitBootServices(image_handle,handle.arch.mmap.key);
arch_load_to_kernel(handle);


no_interrupt_halt();
}






extern "C" EFIAPI int emain(EFI_HANDLE emain_img_hnd,EFI_SYSTEM_TABLE*emain_systab)
{
init_efi_protocols(emain_img_hnd,emain_systab);

clear_terminal();

printf(u"SHROOM BOOT V0.5");

EFI_INPUT_KEY key={0,0};
INTN selected=0;
while(true)
{
cout->SetCursorPosition(cout,0,1);
for(UINTN i=0;i<ARRAY_SIZE(menu_options);++i)
{
if(i==selected)
{cout->SetAttribute(cout,0x1E);}
else
{cout->SetAttribute(cout,0x07);}
printf(u"* %s\r\n",menu_options[i]);
}

key=get_key();

if(key.ScanCode==1)       {selected=(selected-1)%ARRAY_SIZE(menu_options);}
if(key.ScanCode==2)       {selected=(selected+1)%ARRAY_SIZE(menu_options);}
if(key.UnicodeChar==u'\r')
{
switch (selected)
{
case 0:
boot();
break;

case 1:
delete_file(u"\\EFI\\BOOT\\KERN.BIN");
break;

case 2:
runtime_services->ResetSystem(EfiResetShutdown,0,0,nullptr);
break;

default:

break;
}
}
}



asm volatile("cli;hlt");

return 0;
}