#pragma once

#include "mstdi.h"
#include "arch.h"
#include "cpu.h"
#include "globals.h"
#include "acpi.h"

uint64_t get_apic_base() {
    uint32_t eax, edx;
    // CPUID leaf for APIC base address is 0x01
    __asm__ volatile (
        "movl $0x01, %%eax\n\t"   // Request CPUID leaf 1
        "cpuid\n\t"
        : "=d"(edx), "=a"(eax)    // edx and eax store parts of the result
        :
        : "ebx", "ecx"            // Preserve ebx and ecx
    );

    // Extract the APIC base from edx (bits 24-31) or MSR (see next point).
    return (edx & 0xFF000000);
}


void _init_apic1x(){}
void _init_apic2x(){}

void init_apic()
{




}