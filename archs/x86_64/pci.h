#pragma once

#include "mstdi.h"
#include "arch.h"
#include "cpu.h"
#include "globals.h"
#include "tty.h"

#define PCI_CONFIG_SPACE_SIZE 256
#define PCI_VENDOR_ID_OFFSET  0x00
#define PCI_DEVICE_ID_OFFSET  0x02
#define PCI_CLASS_CODE_OFFSET 0x08
#define PCI_BAR0_OFFSET       0x10

pci_entry_t get_pci_entry(UINT8 bus, UINT8 device, UINT8 function) {
    pci_entry_t entry;
    UINT64 config_address = ((uintptr_t)pci_base) + (bus << 20) + (device << 15) + (function << 12);
    
    entry.vendor_id = *(volatile UINT16*)(config_address + PCI_VENDOR_ID_OFFSET);
    entry.device_id = *(volatile UINT16*)(config_address + PCI_DEVICE_ID_OFFSET);

    UINT32 class_code_data = *(volatile UINT32*)(config_address + PCI_CLASS_CODE_OFFSET);
    entry.class_code = (class_code_data >> 24) & 0xFF;
    entry.subclass = (class_code_data >> 16) & 0xFF;
    entry.prog_if = (class_code_data >> 8) & 0xFF;
    entry.revision_id = class_code_data & 0xFF;

    for (UINTN i = 0; i < 6; i++) {
        entry.bar[i] = *(volatile UINT32*)(config_address + PCI_BAR0_OFFSET + (i * 4));
    }
    
    return entry;
}


void init_pci()
{
UINTN mcfg_entry_count=(mcfg->header.Length-sizeof(mcfg_t))/sizeof(mcfg_entry_t);
for (UINTN i=0;i<mcfg_entry_count;++i)
{
mcfg_entry_t*entry=(mcfg_entry_t*)(((UINT8*)mcfg)+sizeof(mcfg_t))+i;

pci_base=(void*)entry->base_address;

}

}