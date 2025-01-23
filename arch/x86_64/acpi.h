#pragma once

#include "std_dtypes.h"

struct xsdp_t
{
CHAR8    Signature[8];
UINT8    Checksum;
CHAR8    OEMID[6];
UINT8    Revision;
UINT32   RsdtAddress;
UINT32   Length;
UINT64   XsdtAddress;
UINT8    ExtendedChecksum;
UINT8    reserved[3];
}__attribute__((packed));

