#include "mstdi.h"
#include"helper.h"
#include"printf.h"


void load_kernel()
{
UINTN kernel_size;
UINTN kernel_pages;
void*kernel_buffer;
kernel_args_t args;
kernel_args_t*args_ptr=&args;
alloc_context=&args.alloc_context;

args.mmap=get_memory_map();

args.sgi.buffer=(UINT32*)gop->Mode->FrameBufferBase;
args.sgi.w=gop->Mode->Info->PixelsPerScanLine;
args.sgi.h=gop->Mode->Info->VerticalResolution;
args.alloc_context={nullptr,0,0,&args.mmap};

args.krs=*((KERN_RUNTIME_SERVICES*)ers);

xsdp_t*xsdp_ptr=(xsdp_t*)get_config_table_by_guid(EFI_ACPI_TABLE_GUID);

args.xsdp=xsdp_ptr;

{
EFI_FILE_PROTOCOL*root;
EFI_FILE_PROTOCOL*kernel_file;
EFI_GUID info_guid=EFI_FILE_INFO_ID;
EFI_FILE_INFO file_info;
UINTN file_info_size=sizeof(EFI_FILE_INFO);
fsp->OpenVolume(fsp,&root);
root->Open(root,&kernel_file,u"\\EFI\\BOOT\\kernel.bin",EFI_FILE_MODE_READ,0);
root->Close(root);
kernel_file->GetInfo(kernel_file,&info_guid,&file_info_size,&file_info);
kernel_size=file_info.FileSize;
kernel_pages=SIZE_TO_PAGES(file_info.FileSize);
ebs->AllocatePages(AllocateAnyPages,EfiLoaderCode,kernel_pages,(EFI_PHYSICAL_ADDRESS*)&kernel_buffer);
kernel_file->Read(kernel_file,&kernel_size,kernel_buffer);
kernel_file->Close(kernel_file);
}

ebs->ExitBootServices(img_handle,args.mmap.key);

pml4=(page_table_t*)mmap_allocate_pages(alloc_context,1);
memset(pml4,0,sizeof(page_table_t));

identity_map_efi_mmap(&args.mmap);
set_runtime_address_map(&args.mmap);

for(UINTN i=0;i<kernel_pages+1;++i)
{
map_page((UINTN)kernel_buffer+(i*PAGE_SIZE),KERNEL_START_ADDRESS+(i*PAGE_SIZE),&args.mmap,PAGE_PRESENT|PAGE_READWRITE|PAGE_USER);
}

for(UINTN i=0;i<(gop->Mode->FrameBufferSize+(PAGE_SIZE-1))/PAGE_SIZE;i++) 
{identity_map_page(gop->Mode->FrameBufferBase+(i*PAGE_SIZE),&args.mmap);}

const UINTN STACK_PAGES=16;  
void*kernel_stack=mmap_allocate_pages(alloc_context,STACK_PAGES);
memset(kernel_stack,0,STACK_PAGES*PAGE_SIZE);

for (UINTN i=0;i<STACK_PAGES;++i) 
{identity_map_page((UINTN)kernel_stack+(i*PAGE_SIZE),&args.mmap);}


tss_t tss={.io_map_base=sizeof(tss_t)};
UINTN tss_address=(UINTN)&tss;

gdt_t gdt;

gdt.null.value          =0x0000000000000000;
gdt.kernel_code_64.value=0x00AF9A000000FFFF;
gdt.kernel_data_64.value=0x00CF92000000FFFF;
gdt.user_code_64.value  =0x00AFFA000000FFFF;
gdt.user_data_64.value  =0x00CFF2000000FFFF;
gdt.kernel_code_32.value=0x00CF9A000000FFFF;
gdt.kernel_data_32.value=0x00CF92000000FFFF;
gdt.user_code_32.value  =0x00CFFA000000FFFF;
gdt.user_data_32.value  =0x00CFF2000000FFFF;


gdt.tss.base_63_32=(tss_address>>32)&0xFFFFFFFF;


gdt.tss.descriptor.limit_15_0=sizeof(tss_t)-1;
gdt.tss.descriptor.base_15_0=tss_address&0xFFFF;
gdt.tss.descriptor.base_23_16=(tss_address>>16)&0xFF;
gdt.tss.descriptor.type=9;
gdt.tss.descriptor.p=1;
gdt.tss.descriptor.base_31_24=(tss_address>>24)&0xFF;

desc_reg_t gdtr={.limit=sizeof gdt-1,.base=(UINT64)&gdt};

asm volatile
(
"cli\n"
"movq %[pml4],%%CR3\n"
"lgdt %[gdt]\n"
"ltr %[tss]\n"
"pushq $0x8\n"
"leaq 1f(%%RIP),%%RAX\n"
"pushq %%RAX\n"
"lretq\n"
"1:\n"
"movq $0x10,%%RAX\n"
"movq %%RAX,%%DS\n"
"movq %%RAX,%%ES\n"
"movq %%RAX,%%FS\n"
"movq %%RAX,%%GS\n"
"movq %%RAX,%%SS\n"
"movq %[stack],%%RSP\n"
"callq *%[entry]\n"
::  
[pml4]"r"(pml4),
[gdt]"m"(gdtr),
[tss]"r"((UINT16)0x48),
[stack]"gm"((UINTN)kernel_stack+(STACK_PAGES*PAGE_SIZE)),
[entry]"r"(KERNEL_START_ADDRESS),"c"(args_ptr)
:"rax","memory"
);
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

file->Read(file,&file_info.FileSize,&boot_config_data);
file->Close(file);
gop->SetMode(gop,boot_config_data.gop_mode);
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