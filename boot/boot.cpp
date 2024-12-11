#include "mstdi.h"
#include"helper.h"
#include"printf.cpp"

#include "x86_64/boot.h"


void load_kernel()
{
UINTN kernel_size;
UINTN kernel_pages;
void* kernel_buffer;


load_file(u"\\EFI\\BOOT\\kernel.bin",&kernel_buffer,&kernel_size,&kernel_pages);

MEMORY_MAP_INFO mmap=get_memory_map();


ebs->ExitBootServices(img_handle,mmap.key);

arch_setup_and_jump_to_kernel(&mmap,kernel_buffer,kernel_pages);
}

extern "C" EFI_STATUS emain(EFI_HANDLE img_hnd,EFI_SYSTEM_TABLE*systab)
{
est=systab;
top=systab->ConOut;
tip=systab->ConIn;
ebs=systab->BootServices;
ers=systab->RuntimeServices;
img_handle=img_hnd;
gop=(EFI_GRAPHICS_OUTPUT_PROTOCOL*)locate_protocol(EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID);
lip=(EFI_LOADED_IMAGE_PROTOCOL*)open_protocol(img_hnd,EFI_LOADED_IMAGE_PROTOCOL_GUID,img_hnd,NULL,EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
fsp=(EFI_SIMPLE_FILE_SYSTEM_PROTOCOL*)open_protocol(lip->DeviceHandle,EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID,img_hnd,NULL,EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);

{
EFI_FILE_PROTOCOL*root;
EFI_FILE_PROTOCOL*file;
EFI_GUID info_guid=EFI_FILE_INFO_ID;
EFI_FILE_INFO file_info;
UINTN file_info_size=sizeof(EFI_FILE_INFO);
fsp->OpenVolume(fsp,&root);
root->Open(root,&file,u"\\EFI\\BOOT\\config.bc",EFI_FILE_MODE_READ,0);
root->Close(root);
file->GetInfo(file,&info_guid,&file_info_size,&file_info);
ebs->AllocatePool(EfiLoaderData,file_info.FileSize,(void**)&boot_config_data);
file->Read(file,&file_info.FileSize,&boot_config_data);
boot_config_data->entries=(driver_entry_t*)(((CHAR8*)boot_config_data)+(sizeof(UINT32)*2));
file->Close(file);
gop->SetMode(gop,boot_config_data->gop_mode);
top->Reset(top,true);
set_max_top_mode();
}

top->ClearScreen(top);
top->EnableCursor(top,false);

const CHAR16*boot_options[]=
{
u"boot moss         ",
u"change boot config",
u"shutdown          ",
};

UINTN default_attrib=top->Mode->Attribute;
INT32 selected=0;
while (true)
{
top->SetCursorPosition(top,0,0);
top->SetAttribute(top,default_attrib);
printf(u"SHROOMBOOT 0.1V\r\n");
for (UINTN i=0;i<ARRAY_SIZE(boot_options);++i)
{
if(selected==i)
{top->SetAttribute(top,0x1E);}
else
{top->SetAttribute(top,default_attrib);}
printf(u"%s\r\n",boot_options[i]);
}
EFI_INPUT_KEY key=get_key();
if(key.ScanCode==0x1)
{selected--;}
if(key.ScanCode==0x2)
{selected++;}
if(selected>=ARRAY_SIZE(boot_options)){selected=0;}
if(key.UnicodeChar==0xD)
{
top->ClearScreen(top);
switch(selected)
{
case 0:load_kernel();break;
case 1:boot_config(default_attrib);break;
case 2:ers->ResetSystem(EfiResetShutdown,0,0,nullptr);break;
default:break;
}
}
}
halt_machine();
return 0;
}