#pragma once

#include "mstdi.h"
#include "arch.h"
#include "cpu.h"

static madt_t*madt;
static fadt_t*fadt;
static srat_t*srat;

void init_acpi(xsdt_t*xsdt)
{
UINTN table_lenght=(xsdt->header.Length-sizeof(acpi_header_t))/sizeof(UINT64);

for(UINTN i=0;i<table_lenght;++i)
{
acpi_header_t*entry=(acpi_header_t*)((UINT64*)(((UINT8*)xsdt)+sizeof(acpi_header_t)))[i];

if(strcmp(entry->Signature,"APIC",4)==0)
{madt=(madt_t*)entry;}

if(strcmp(entry->Signature,"FACP",4)==0)
{fadt=(fadt_t*)entry;}
  
if(strcmp(entry->Signature,"SRAT",4)==0)
{srat=(srat_t*)entry;}
}


}