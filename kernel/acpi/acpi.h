#pragma once

#include "mstdi.h"
#include "globals.h"
#include "kprintf.h"

void init_acpi()
{
xsdt_t*xsdt=(xsdt_t*)xsdp->XsdtAddress;

UINTN entry_count=(xsdt->header.Length-sizeof(acpi_header_t))/sizeof(UINT64);
UINT64*entries=(UINT64*)(((UINT64)xsdt)+sizeof(acpi_header_t));

for (UINTN i=0;i<entry_count;++i)
{
acpi_header_t*entry=(acpi_header_t*)entries[i];
printf(u"ACPI entry %d: %c%c%c%c\r\n",i,entry->Signature[0],entry->Signature[1],entry->Signature[2],entry->Signature[3]);
}



}