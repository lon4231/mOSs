#pragma once

#include "efi.h"
#include "mstdi.h"
#include "printf.h"

EFI_SYSTEM_TABLE*est;
EFI_BOOT_SERVICES*ebs;
EFI_RUNTIME_SERVICES*ers;
EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*top;
EFI_SIMPLE_TEXT_INPUT_PROTOCOL*tip;
EFI_GRAPHICS_OUTPUT_PROTOCOL*gop;
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL*fsp;
EFI_LOADED_IMAGE_PROTOCOL*lip;
EFI_HANDLE img_handle;
boot_config_t*boot_config_data;
page_table_t*   pml4;
alloc_context_t*alloc_context;


extern "C" void _putchar(CHAR16 character)
{
static CHAR16 str[2]={0,0};
str[0]=character;
top->OutputString(top,str);
}

EFI_INPUT_KEY get_key() 
{
EFI_EVENT events[1] = { tip->WaitForKey };
EFI_INPUT_KEY key = {0};
UINTN index = 0;
ebs->WaitForEvent(1,events,&index);
tip->ReadKeyStroke(tip,&key);
return key;
}

void*locate_protocol(EFI_GUID protocol)
{
void*interface;
ebs->LocateProtocol(&protocol,NULL,&interface);
return interface;
}

void*open_protocol(EFI_HANDLE handle,EFI_GUID protocol,EFI_HANDLE ahandle,EFI_HANDLE chandle,UINT32 attr)
{
void*interface;
ebs->OpenProtocol(handle,&protocol,&interface,ahandle,chandle,attr);
return interface;
}

INTN compare_guid(const EFI_GUID*guid0,const EFI_GUID*guid1)
{
INT32*g1,*g2,r;
g1=(INT32*)guid0;
g2=(INT32*)guid1;
r=g1[0]-g2[0];
r|=g1[1]-g2[1];
r|=g1[2]-g2[2];
r|=g1[3]-g2[3];
return r;
}


MEMORY_MAP_INFO get_memory_map()
{
MEMORY_MAP_INFO mmap_data;
MEMORY_MAP_INFO*mmap=&mmap_data;
memset(mmap,0,sizeof(MEMORY_MAP_INFO));
ebs->GetMemoryMap(&mmap->size,(EFI_MEMORY_DESCRIPTOR*)mmap->map,&mmap->key,&mmap->desc_size,&mmap->desc_version);
mmap->size+=mmap->desc_size*2;
ebs->AllocatePool(EfiLoaderData,mmap->size,(VOID**)&mmap->map);
ebs->GetMemoryMap(&mmap->size,(EFI_MEMORY_DESCRIPTOR*)mmap->map,&mmap->key,&mmap->desc_size,&mmap->desc_version);
return mmap_data;
}


void gop_config(boot_config_t*config,UINTN default_attrib)
{
UINTN available_modes_count=0;
EFI_GRAPHICS_OUTPUT_MODE_INFORMATION*mode_info=NULL;
UINTN mode_info_size=sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION);

UINT32*available_modes;

{
for(UINTN i=0;i<gop->Mode->MaxMode;++i)
{
gop->QueryMode(gop,i,&mode_info_size,&mode_info);
if(mode_info->PixelFormat==PixelBltOnly||mode_info->PixelFormat==PixelBitMask){continue;}
available_modes_count++;
}
ebs->AllocatePool(EFI_MEMORY_TYPE::EfiLoaderData,available_modes_count*sizeof(UINT32),(void**)&available_modes);
UINTN array_ptr=0;
for(UINTN i=0;i<gop->Mode->MaxMode;++i)
{
gop->QueryMode(gop,i,&mode_info_size,&mode_info);
if(mode_info->PixelFormat==PixelBltOnly||mode_info->PixelFormat==PixelBitMask){continue;}
available_modes[array_ptr]=i;array_ptr++;
}
}

top->ClearScreen(top);

UINTN selected=0;
while(true)
{
top->SetCursorPosition(top,0,0);
for (UINTN i=0;i<available_modes_count;++i)
{
if(selected==i)
{top->SetAttribute(top,0x1E);}
else
{top->SetAttribute(top,default_attrib);}

gop->QueryMode(gop,available_modes[i],&mode_info_size,&mode_info);

printf(u"%dx%d\r\n",mode_info->PixelsPerScanLine,mode_info->VerticalResolution);
}

EFI_INPUT_KEY key=get_key();

if(key.ScanCode==0x1)
{selected--;}
if(key.ScanCode==0x2)
{selected++;}
if(selected>=available_modes_count){selected=0;}
if(key.UnicodeChar==0xD)
{
config->gop_mode=available_modes[selected];
gop->SetMode(gop,config->gop_mode);
break;
}
}

ebs->FreePool(available_modes);
}

void boot_config(UINTN default_attrib)
{
const CHAR16*config_options[]=
{
u"gop config ",
u"save config",
u"exit       ",
};

top->ClearScreen(top);

INT32 selected=0;
while (true)
{
top->SetCursorPosition(top,0,0);
for (UINTN i=0;i<ARRAY_SIZE(config_options);++i)
{
if(selected==i)
{top->SetAttribute(top,0x1E);}
else
{top->SetAttribute(top,default_attrib);}
printf(u"%s\r\n",config_options[i]);
}


EFI_INPUT_KEY key=get_key();

if(key.ScanCode==0x1)
{selected--;}
if(key.ScanCode==0x2)
{selected++;}
if(selected>=ARRAY_SIZE(config_options)){selected=0;}
if(key.UnicodeChar==0xD)
{
switch (selected)
{
case 0:
gop_config(boot_config_data,default_attrib);
break;

case 1:
{
EFI_FILE_PROTOCOL*root;
EFI_FILE_PROTOCOL*file;
EFI_GUID info_guid=EFI_FILE_INFO_ID;
EFI_FILE_INFO file_info;
UINTN file_info_size=sizeof(EFI_FILE_INFO);
fsp->OpenVolume(fsp,&root);
root->Open(root,&file,u"\\EFI\\BOOT\\config.bc",EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE,0);
root->Close(root);
UINTN config_size=sizeof(boot_config_t);
file->Write(file,&config_size,&boot_config_data);
file->Close(file);
}
break;

case 2:return;

default:break;
}
}
}



}

void set_max_top_mode()
{
UINTN best_mode=0;
UINTN best_size=0;
for (UINTN i=0;i<top->Mode->MaxMode;++i)
{
UINTN rows,columns;
top->QueryMode(top,i,&columns,&rows);
if((rows*columns)>best_size)
{best_mode=i;best_size=(rows*columns);}
}
top->SetMode(top,best_mode);
}

void load_file(const CHAR16*path,void**buffer,UINTN*size,UINTN*pages)
{
EFI_FILE_PROTOCOL*root;
EFI_FILE_PROTOCOL*file;
EFI_GUID info_guid=EFI_FILE_INFO_ID;
EFI_FILE_INFO file_info;
UINTN file_info_size=sizeof(EFI_FILE_INFO);
fsp->OpenVolume(fsp,&root);
root->Open(root,&file,(CHAR16*)path,EFI_FILE_MODE_READ,0);
root->Close(root);
file->GetInfo(file,&info_guid,&file_info_size,&file_info);
if(size!=nullptr){*size=file_info.FileSize;}
if(pages!=nullptr){*pages=SIZE_TO_PAGES(file_info.FileSize);}
ebs->AllocatePages(AllocateAnyPages,EfiLoaderCode,*pages,(EFI_PHYSICAL_ADDRESS*)buffer);
file->Read(file,size,*buffer);
file->Close(file);
}

/*post EFI stuff*/


VOID*get_config_table_by_guid(EFI_GUID guid)
{
for(UINTN i=0;i<est->NumberOfTableEntries;++i)
{
EFI_GUID vendor_guid=est->ConfigurationTable[i].VendorGuid;

if(!memcmp(&vendor_guid,&guid,sizeof(guid)))
{return est->ConfigurationTable[i].VendorTable;}
}
return nullptr;
}

