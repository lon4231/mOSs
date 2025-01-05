#pragma once

struct cpu_status_t
{
UINT64 r15;
UINT64 r14;
UINT64 r13;
UINT64 r12;
UINT64 r11;
UINT64 r10;
UINT64 r9;
UINT64 r8;
UINT64 rdi;
UINT64 rsi;
UINT64 rbp;
UINT64 rdx;
UINT64 rcx;
UINT64 rbx;
UINT64 rax;

UINT64 interrupt_number;
UINT64 error_code;

UINT64 rip;
UINT64 cs;
UINT64 rflags;
UINT64 rsp;
UINT64 ss;
}__attribute__((__packed__));

enum CPUID_FEAT
{
CPUID_FEAT_ECX_SSE3         =1<<0,
CPUID_FEAT_ECX_PCLMUL       =1<<1,
CPUID_FEAT_ECX_DTES64       =1<<2,
CPUID_FEAT_ECX_MONITOR      =1<<3,
CPUID_FEAT_ECX_DS_CPL       =1<<4,
CPUID_FEAT_ECX_VMX          =1<<5,
CPUID_FEAT_ECX_SMX          =1<<6,
CPUID_FEAT_ECX_EST          =1<<7,
CPUID_FEAT_ECX_TM2          =1<<8,
CPUID_FEAT_ECX_SSSE3        =1<<9,
CPUID_FEAT_ECX_CID          =1<<10,
CPUID_FEAT_ECX_SDBG         =1<<11,
CPUID_FEAT_ECX_FMA          =1<<12,
CPUID_FEAT_ECX_CX16         =1<<13,
CPUID_FEAT_ECX_XTPR         =1<<14,
CPUID_FEAT_ECX_PDCM         =1<<15,
CPUID_FEAT_ECX_PCID         =1<<17,
CPUID_FEAT_ECX_DCA          =1<<18,
CPUID_FEAT_ECX_SSE4_1       =1<<19,
CPUID_FEAT_ECX_SSE4_2       =1<<20,
CPUID_FEAT_ECX_X2APIC       =1<<21,
CPUID_FEAT_ECX_MOVBE        =1<<22,
CPUID_FEAT_ECX_POPCNT       =1<<23,
CPUID_FEAT_ECX_TSC          =1<<24,
CPUID_FEAT_ECX_AES          =1<<25,
CPUID_FEAT_ECX_XSAVE        =1<<26,
CPUID_FEAT_ECX_OSXSAVE      =1<<27,
CPUID_FEAT_ECX_AVX          =1<<28,
CPUID_FEAT_ECX_F16C         =1<<29,
CPUID_FEAT_ECX_RDRAND       =1<<30,
CPUID_FEAT_ECX_HYPERVISOR   =1<<31,
CPUID_FEAT_EDX_FPU          =1<<0,
CPUID_FEAT_EDX_VME          =1<<1,
CPUID_FEAT_EDX_DE           =1<<2,
CPUID_FEAT_EDX_PSE          =1<<3,
CPUID_FEAT_EDX_TSC          =1<<4,
CPUID_FEAT_EDX_MSR          =1<<5,
CPUID_FEAT_EDX_PAE          =1<<6,
CPUID_FEAT_EDX_MCE          =1<<7,
CPUID_FEAT_EDX_CX8          =1<<8,
CPUID_FEAT_EDX_APIC         =1<<9,
CPUID_FEAT_EDX_SEP          =1<<11,
CPUID_FEAT_EDX_MTRR         =1<<12,
CPUID_FEAT_EDX_PGE          =1<<13,
CPUID_FEAT_EDX_MCA          =1<<14,
CPUID_FEAT_EDX_CMOV         =1<<15,
CPUID_FEAT_EDX_PAT          =1<<16,
CPUID_FEAT_EDX_PSE36        =1<<17,
CPUID_FEAT_EDX_PSN          =1<<18,
CPUID_FEAT_EDX_CLFLUSH      =1<<19,
CPUID_FEAT_EDX_DS           =1<<21,
CPUID_FEAT_EDX_ACPI         =1<<22,
CPUID_FEAT_EDX_MMX          =1<<23,
CPUID_FEAT_EDX_FXSR         =1<<24,
CPUID_FEAT_EDX_SSE          =1<<25,
CPUID_FEAT_EDX_SSE2         =1<<26,
CPUID_FEAT_EDX_SS           =1<<27,
CPUID_FEAT_EDX_HTT          =1<<28,
CPUID_FEAT_EDX_TM           =1<<29,
CPUID_FEAT_EDX_IA64         =1<<30,
CPUID_FEAT_EDX_PBE          =1<<31
};

#define halt_machine() asm volatile("cli;hlt");

#define cpuid(in,a,b,c,d) asm volatile("cpuid":"=a"(*a),"=b"(*b),"=c"(*c),"=d"(*d):"a"(in));

__attribute__((always_inline)) void save_context() 
{
asm volatile
(
"pushq %rax;"
"pushq %rbx;"
"pushq %rcx;"
"pushq %rdx;"
"pushq %rbp;"
"pushq %rsi;"
"pushq %rdi;"
"pushq %r8;"
"pushq %r9;"
"pushq %r10;"
"pushq %r11;"
"pushq %r12;"
"pushq %r13;"
"pushq %r14;"
"pushq %r15;"
);
}

__attribute__((always_inline)) void restore_context() 
{
asm volatile
(
"popq %r15;"
"popq %r14;"
"popq %r13;"
"popq %r12;"
"popq %r11;"
"popq %r10;"
"popq %r9;"
"popq %r8;"
"popq %rdi;"
"popq %rsi;"
"popq %rbp;"
"popq %rdx;"
"popq %rcx;"
"popq %rbx;"
"popq %rax;"
);
}


void __attribute__((always_inline)) outb(UINT16 port,UINT8  val){asm volatile("outb %b0,%w1"::"a"(val),"Nd"(port):"memory");}
void __attribute__((always_inline)) outw(UINT16 port,UINT16 val){asm volatile("outw %w0,%w1"::"a"(val),"Nd"(port):"memory");}
void __attribute__((always_inline)) outl(UINT16 port,UINT32 val){asm volatile("outl %0,%w1" ::"a"(val),"Nd"(port):"memory");}

UINT8  __attribute__((always_inline)) inb(UINT16 port){UINT8  ret;asm volatile("inb %w1, %b0":"=a"(ret):"Nd"(port):"memory");return ret;}
UINT16 __attribute__((always_inline)) inw(UINT16 port){UINT16 ret;asm volatile("inw %w1, %w0":"=a"(ret):"Nd"(port):"memory");return ret;}
UINT32 __attribute__((always_inline)) inl(UINT16 port){UINT32 ret;asm volatile("inl %w1, %0" :"=a"(ret):"Nd"(port):"memory");return ret;}

UINT64 __attribute__((always_inline)) rdmsr(uint32_t address){
    uint32_t low=0, high=0;
    asm("movl %2, %%ecx;" 
        "rdmsr;"
        : "=a" (low), "=d" (high)
        : "g" (address)
    );

    return (UINT64) low | ((UINT64)high << 32);
}

void __attribute__((always_inline)) wrmsr(uint32_t address, UINT64 value)
{
    asm("wrmsr"
    :
    : "a" ((uint32_t)value), "d"(value >> 32), "c"(address)
    );
}

void enable_sse()
{
{
UINT32 eax=0x1,ebx=0,ecx=0,edx=0;
cpuid(1,&eax,&ebx,&ecx,&edx);
if(!((edx>>25)&1)){return;}
}

{
UINT32 eax=0x1,ebx=0,ecx=0,edx=0;
cpuid(1,&eax,&ebx,&ecx,&edx);
if(!((edx>>24)&1)){return;}
}

asm volatile
(
"mov %%cr0,%%rax;"
"and $0xFFFB,%%ax;"
"or $2,%%eax;"
"mov %%rax,%%cr0;"
"mov %%cr4,%%rax;"
"or $0b11000000000,%%rax;"
"mov %%rax,%%cr4;":::"rax"
);
asm volatile
(
"fninit;"
"mov %%cr0,%%rax;"
"or $0b100000,%%rax;"
"mov %%rax,%%cr0;":::"rax"
);
}
