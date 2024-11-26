#pragma once

#include"mstdi.h"
#include"globals.h"
#include"printf.h"

#define PCI_CONFIG_SPACE_SIZE 256
#define PCI_VENDOR_ID_OFFSET  0x00
#define PCI_DEVICE_ID_OFFSET  0x02
#define PCI_CLASS_CODE_OFFSET 0x08
#define PCI_BAR0_OFFSET       0x10

pci_entry_t get_pci_entry(UINT64 baseAddress,UINT8 bus,UINT8 device,UINT8 function) 
{
pci_entry_t entry;
UINT32 config_address=baseAddress+(bus<<20)+(device<<15)+(function<<12);
    
entry.vendor_id=*(volatile UINT16*)(config_address+PCI_VENDOR_ID_OFFSET);
entry.device_id=*(volatile UINT16*)(config_address+PCI_DEVICE_ID_OFFSET);

UINT32 class_code_data=*(volatile UINT32*)(config_address+PCI_CLASS_CODE_OFFSET);
entry.class_code=(class_code_data>>24)&0xFF;
entry.subclass=(class_code_data>>16)&0xFF;
entry.prog_if=(class_code_data>>8)&0xFF;
entry.revision_id=class_code_data&0xFF;         
for (UINTN i=0;i<6;i++) 
{entry.bar[i]=*(volatile UINT32*)(config_address+PCI_BAR0_OFFSET+(i*4));}
return entry;
}


void init_pcie()
{
UINT32 table_size=(mcfg->header.Length-44)/sizeof(mcfg_entry_t);
mcfg_entry_t*entries=(mcfg_entry_t*)(((UINT8*)mcfg)+44);

mcfg_entries=entries;
mcfg_entry_count=table_size;



}

void write_pcie_register(UINT32*bar_address,UINT32 offset,UINT32 value) 
{*(volatile UINT32*)(bar_address + offset) = value;}

void send_command_to_pcie(UINT64 baseAddress,UINT8 bus,UINT8 device,UINT8 function,UINT32 command) 
{
pci_entry_t entry=get_pci_entry(baseAddress,bus,device,function);
UINT32*bar0_base=(UINT32*)entry.bar[0];
write_pcie_register(bar0_base,0x10,command);
}

