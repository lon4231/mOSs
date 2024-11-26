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
page_table_t*pml4;
alloc_context_t*alloc_context;
boot_config_t boot_config_data;


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
gop_config(&boot_config_data,default_attrib);
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
{
best_mode=i;
best_size=(rows*columns);
}
}
top->SetMode(top,best_mode);
}

/*post EFI stuff*/

void*mmap_allocate_pages(alloc_context_t*alloc_context,UINTN pages)
{
if (alloc_context->remaining_pages<pages)
{
UINTN i=alloc_context->current_descriptor+1;
for (;i<alloc_context->mmap->size/alloc_context->mmap->desc_size;++i)
{
EFI_MEMORY_DESCRIPTOR*desc=(EFI_MEMORY_DESCRIPTOR*)((UINT8*)alloc_context->mmap->map+(i*alloc_context->mmap->desc_size));

if (desc->Type==EfiConventionalMemory&&desc->NumberOfPages>=pages)
{
alloc_context->current_descriptor=i;
alloc_context->remaining_pages=desc->NumberOfPages-pages;
alloc_context->next_page_address=(void*)(desc->PhysicalStart+(pages*PAGE_SIZE));
return (void*)desc->PhysicalStart;
}
}

if (i>=alloc_context->mmap->size/alloc_context->mmap->desc_size)
{return nullptr;}
}

alloc_context->remaining_pages-=pages;
void*page=alloc_context->next_page_address;
alloc_context->next_page_address=(void*)((UINT8*)page+(pages*PAGE_SIZE));
return page;
}


void map_page(UINTN physical_address,UINTN virtual_address,MEMORY_MAP_INFO*mmap,int flags)
{

UINTN pml4_index=((virtual_address)>>39)&0x1FF;
UINTN pdpt_index=((virtual_address)>>30)&0x1FF;
UINTN pdt_index =((virtual_address)>>21)&0x1FF;
UINTN pt_index  =((virtual_address)>>12)&0x1FF;

if (!(pml4->entries[pml4_index]&PAGE_PRESENT))
{
void*pdpt_address=mmap_allocate_pages(alloc_context,1);
memset(pdpt_address,0,sizeof(page_table_t));
pml4->entries[pml4_index]=(UINTN)pdpt_address|flags;
}

page_table_t*pdpt=(page_table_t*)(pml4->entries[pml4_index]&PHYS_PAGE_ADDR_MASK);
if (!(pdpt->entries[pdpt_index]&PAGE_PRESENT))
{
void*pdt_address=mmap_allocate_pages(alloc_context,1);
memset(pdt_address,0,sizeof(page_table_t));
pdpt->entries[pdpt_index]=(UINTN)pdt_address|flags;
}

page_table_t*pdt=(page_table_t*)(pdpt->entries[pdpt_index]&PHYS_PAGE_ADDR_MASK);

if (!(pdt->entries[pdt_index]&PAGE_PRESENT))
{
void*pt_address=mmap_allocate_pages(alloc_context,1);
memset(pt_address,0,sizeof(page_table_t));
pdt->entries[pdt_index]=(UINTN)pt_address|flags;
}

page_table_t*pt=(page_table_t*)(pdt->entries[pdt_index]&PHYS_PAGE_ADDR_MASK);
if (!(pt->entries[pt_index]&PAGE_PRESENT))
pt->entries[pt_index]=(physical_address&PHYS_PAGE_ADDR_MASK)|flags;
}

void identity_map_page(UINTN address,MEMORY_MAP_INFO*mmap)
{
map_page(address,address,mmap,PAGE_PRESENT|PAGE_READWRITE|PAGE_USER);
}

void identity_map_efi_mmap(MEMORY_MAP_INFO*mmap)
{
for (UINTN i=0;i<mmap->size/mmap->desc_size;i++)
{
EFI_MEMORY_DESCRIPTOR*desc=(EFI_MEMORY_DESCRIPTOR*)((UINT8*)mmap->map+(i*mmap->desc_size));
for (UINTN j=0;j<desc->NumberOfPages;j++)
{identity_map_page(desc->PhysicalStart+(j*PAGE_SIZE),mmap);}
}
}

void set_runtime_address_map(MEMORY_MAP_INFO*mmap)
{
UINTN runtime_descriptors=0;
for (UINTN i=0; i < mmap->size / mmap->desc_size; i++)
{
EFI_MEMORY_DESCRIPTOR*desc=(EFI_MEMORY_DESCRIPTOR*)((UINT8*)mmap->map+(i*mmap->desc_size));
if (desc->Attribute & EFI_MEMORY_RUNTIME)
runtime_descriptors++;
}

UINTN runtime_mmap_pages=(runtime_descriptors*mmap->desc_size)+((PAGE_SIZE-1)/ PAGE_SIZE);
EFI_MEMORY_DESCRIPTOR*runtime_mmap =(EFI_MEMORY_DESCRIPTOR*)mmap_allocate_pages(alloc_context,runtime_mmap_pages);
if (!runtime_mmap)
{
return;
}

UINTN runtime_mmap_size=runtime_mmap_pages*PAGE_SIZE; 
memset(runtime_mmap,0,runtime_mmap_size);

UINTN curr_runtime_desc=0;
for (UINTN i=0; i < mmap->size / mmap->desc_size; i++)
{
EFI_MEMORY_DESCRIPTOR*desc=(EFI_MEMORY_DESCRIPTOR*)((UINT8*)mmap->map+(i*mmap->desc_size));
if (desc->Attribute & EFI_MEMORY_RUNTIME)
{
EFI_MEMORY_DESCRIPTOR*runtime_desc=(EFI_MEMORY_DESCRIPTOR*)((UINT8*)runtime_mmap+(curr_runtime_desc*mmap->desc_size));

memcpy(runtime_desc,desc,mmap->desc_size);
runtime_desc->VirtualStart=runtime_desc->PhysicalStart;
curr_runtime_desc++;
}
}

ers->SetVirtualAddressMap(runtime_mmap_size,mmap->desc_size,mmap->desc_version,runtime_mmap);
}

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

