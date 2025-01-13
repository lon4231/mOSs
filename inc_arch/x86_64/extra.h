#pragma once

#include "std_types.h"
#include "types.h"

void inline __attribute__((always_inline)) no_interrupt_halt()
{
    asm volatile("cli;hlt");
}

UINT8 inline __attribute__((always_inline)) inb(UINT16 port)
{
    UINT8 ret;
    asm volatile("inb %w1,%b0" : "=a"(ret) : "Nd"(port) : "memory");
    return ret;
}

UINT16 inline __attribute__((always_inline)) inw(UINT16 port)
{
    UINT16 ret;
    asm volatile("inw %w1,%b0" : "=a"(ret) : "Nd"(port) : "memory");
    return ret;
}

UINT32 inline __attribute__((always_inline)) inl(UINT16 port)
{
    UINT32 ret;
    asm volatile("inl %w1,%b0" : "=a"(ret) : "Nd"(port) : "memory");
    return ret;
}

void inline __attribute__((always_inline)) outb(UINT16 port, UINT8 val)
{
    asm volatile("outb %b0,%w1" ::"a"(val), "Nd"(port) : "memory");
}

void inline __attribute__((always_inline)) outw(UINT16 port, UINT16 val)
{
    asm volatile("outw %w0,%w1" ::"a"(val), "Nd"(port) : "memory");
}

void inline __attribute__((always_inline)) outl(UINT16 port, UINT32 val)
{
    asm volatile("outl %0,%w1" ::"a"(val), "Nd"(port) : "memory");
}

UINT64 inline __attribute__((always_inline)) rdmsr(uint32_t address)
{
    uint32_t low = 0, high = 0;
    asm volatile(
        "movl %2,%%ecx;"
        "rdmsr;"
        : "=a"(low), "=d"(high)
        : "g"(address));
    return (UINT64)low | ((UINT64)high << 32);
}

void inline __attribute__((always_inline)) wrmsr(uint32_t address, UINT64 value)
{
    asm volatile(
        "wrmsr" ::"a"((uint32_t)value), "d"(value >> 32), "c"(address));
}
