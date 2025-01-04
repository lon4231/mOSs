#pragma once

#include "mstdi.h"
#include "arch.h"
#include "cpu.h"
#include "globals.h"
#include "tty.h"

void init_acpi()
{
UINTN table_lenght=(xsdt->header.Length-sizeof(acpi_header_t))/sizeof(UINT64);

for(UINTN i=0;i<table_lenght;++i)
{
acpi_header_t*entry=(acpi_header_t*)((UINT64*)(((UINT8*)xsdt)+sizeof(acpi_header_t)))[i];

kprintf(u"[ACPI ENTRY]: %c%c%c%c\r\n",entry->Signature[0],entry->Signature[1],entry->Signature[2],entry->Signature[3]);

if(strcmp(entry->Signature,"APIC",4)==0)
{madt=(madt_t*)entry;}

if(strcmp(entry->Signature,"FACP",4)==0)
{fadt=(fadt_t*)entry;}
  
if(strcmp(entry->Signature,"SRAT",4)==0)
{srat=(srat_t*)entry;}

if(strcmp(entry->Signature,"MCFG",4)==0)
{mcfg=(mcfg_t*)entry;}
}


}


madt_entry_t get_madt_entry(UINTN index)
{
if(madt==NULL)
{return{MADT_INVALID_ENTRY,NULL};}
UINT8*madt_start=(UINT8*)madt+sizeof(madt_t);
UINT8*madt_end=(UINT8*)madt+madt->header.Length;
UINTN current_index=0;
while (madt_start<madt_end)
{
madt_entry_header_t*entry_header=(madt_entry_header_t*)madt_start;
if(current_index==index)
{return{entry_header->type,(void*)madt_start};}
madt_start+=entry_header->length;
++current_index;
}
return{MADT_INVALID_ENTRY,NULL};
}

UINTN get_madt_size()
{
UINTN size=0;
while(get_madt_entry(size).type!=MADT_INVALID_ENTRY)
{
size++;
}
return size;
}

