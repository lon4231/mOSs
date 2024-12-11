#pragma once

#define PIC1_COMMAND	0x20
#define PIC1_DATA	    0x21
#define PIC2_COMMAND	0xA0
#define PIC2_DATA	    0xA1

#define ICW4_8086	    0x01	
#define ICW4_AUTO	    0x02	
#define ICW4_BUF_SLAVE	0x08
#define ICW4_BUF_MASTER	0x0C
#define ICW4_SFNM	    0x10	

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

#define save_context() asm volatile("push %%rax\n\tpush %%rbx\n\tpush %%rcx\n\tpush %%rdx\n\tpush %%rbp\n\tpush %%rsi\n\tpush %%rdi\n\tpush %%r8\n\tpush %%r9\n\tpush %%r10\n\tpush %%r11\n\tpush %%r12\n\tpush %%r13\n\tpush %%r14\n\tpush %%r15\n\t":::"memory")

#define restore_context() asm volatile("pop %%r15\n\tpop %%r14\n\tpop %%r13\n\tpop %%r12\n\tpop %%r11\n\tpop %%r10\n\tpop %%r9\n\tpop %%r8\n\tpop %%rdi\n\tpop %%rsi\n\tpop %%rbp\n\tpop %%rdx\n\tpop %%rcx\n\tpop %%rbx\n\tpop %%rax\n\t":::"memory")

void outb(UINT16 port,UINT8  val){asm volatile("outb %b0,%w1"::"a"(val),"Nd"(port):"memory");}
void outw(UINT16 port,UINT16 val){asm volatile("outw %w0,%w1"::"a"(val),"Nd"(port):"memory");}
void outl(UINT16 port,UINT32 val){asm volatile("outl %0,%w1" ::"a"(val),"Nd"(port):"memory");}

UINT8  inb(UINT16 port){UINT8  ret;asm volatile("inb %w1, %b0":"=a"(ret):"Nd"(port):"memory");return ret;}
UINT16 inw(UINT16 port){UINT16 ret;asm volatile("inw %w1, %w0":"=a"(ret):"Nd"(port):"memory");return ret;}
UINT32 inl(UINT16 port){UINT32 ret;asm volatile("inl %w1, %0" :"=a"(ret):"Nd"(port):"memory");return ret;}

bool check_sse() 
{
UINT32 eax=0x1,ebx=0,ecx=0,edx=0;
cpuid(1,&eax,&ebx,&ecx,&edx);
return (edx>>25)&1;
}


void enable_sse()
{
if(!check_sse())
{return;}

asm volatile("mov %%cr0, %%rax;and $0xFFFB, %%ax;or  $2, %%eax;mov %%rax, %%cr0;mov %%cr4, %%rax;or  $0b11000000000, %%rax;mov %%rax, %%cr4;":::"rax");
asm volatile("fninit;mov %%cr0, %%rax;or $0b100000, %%rax;mov %%rax, %%cr0;":::"rax");
}
