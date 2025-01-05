#pragma once

#include "mstdi.h"
#include "arch.h"
#include "cpu.h"
#include "globals.h"
#include "tty.h"
#include "apic.h"

void keyboard_handler()
{
UINT8 key=inb(0x60);
kprintf(u"%x\r\n",key);
}