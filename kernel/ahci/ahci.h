#pragma once

#include "mstdi.h"
#include "pci/pcie.h"
#include "ahci_devices.h"

struct hba_port_t 
{
uint32_t clb;
uint32_t clbu;
uint32_t fb;
uint32_t fbu;
uint32_t is;
uint32_t ie;
uint32_t cmd;
uint32_t rsv0;
uint32_t tfd;
uint32_t sig;
uint32_t ssts;
uint32_t sctl;
uint32_t serr;
uint32_t sact;
uint32_t ci;
uint32_t sntf; 
uint32_t fbs;
uint32_t rsv1[11];
uint32_t vendor[4];
};

struct hba_mem_t 
{
uint32_t    cap;
uint32_t    ghc;
uint32_t    is;
uint32_t    pi;
uint32_t    vs;
uint32_t    ccc_ctl;
uint32_t    ccc_pts;
uint32_t    em_loc;
uint32_t    em_ctl;
uint32_t    cap2;
uint32_t    bohc;
uint8_t     rsv[0xA0-0x2C];
uint8_t     vendor[0x100-0xA0];
hba_port_t  ports[32];
};



void ahci_read(UINTN device,UINT64 lba,UINT8 count,void*address)
{}

void ahci_write(UINTN device,UINT64 lba,UINT8 count,void*address)
{}
