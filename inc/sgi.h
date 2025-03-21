#pragma once

#include "std_types.h"

typedef UINT32 sgi_pixel_t;

struct sgi_t
{
sgi_pixel_t*buffer;
UINTN width;
UINTN height;
};
