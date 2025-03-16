#include "boot.h"
#include "std_string.h"

void boot_to_kernel(kernel_args_t*boot_data)
{
gdt_t gdt;
tss_t tss;

gdtr_t gdtr;

gdt.null            =0x0000000000000000;
gdt.kernel_code_64  =0x00AF9A000000FFFF;
gdt.kernel_data_64  =0x00CF92000000FFFF;
gdt.user_code_64    =0x00AFFA000000FFFF;
gdt.user_data_64    =0x00CFF2000000FFFF;
gdt.kernel_code_32  =0x00CF9A000000FFFF;
gdt.kernel_data_32  =0x00CF92000000FFFF;
gdt.user_code_32    =0x00CFFA000000FFFF;
gdt.user_data_32    =0x00CFF2000000FFFF;

UINT64 tss_base=(UINT64)&tss;
UINT64 tss_limit=sizeof(tss) - 1;

*((UINT64*)&gdt.tss_segment)=0x0000890000000067;
gdt.tss_segment.base_15_0 =tss_base&0xFFFF, 
gdt.tss_segment.base_23_16=(tss_base>>16)&0xFF, 
gdt.tss_segment.base_31_24=(tss_base>>24)&0xFF,
gdt.tss_segment.base_63_32=(tss_base>>32)&0xFFFFFFFF,

gdtr.base=(UINT64)&gdt;
gdtr.limit=sizeof(gdt_t)-1;

tss.io_map_base=sizeof(tss_t);

asm volatile(
"cli;"
"lgdt %[gdt];"
"ltr %[tss];"

"pushq $0x8;"
"leaq 1f(%%RIP), %%RAX;"
"pushq %%RAX;"
"lretq;"

"1:;"
"movq $0x10, %%RAX;"
"movq %%RAX, %%DS;"
"movq %%RAX, %%ES;"
"movq %%RAX, %%FS;"
"movq %%RAX, %%GS;"
"movq %%RAX, %%SS;"

"movq %[kstack], %%RSP;"
"callq %[kernel_bin];"
::
[gdt]"m"(gdtr),
[tss]"r"(0x48),
[kstack]"gm"(boot_data->kernel_stack+(KERNEL_STACK_PAGES*PAGE_SIZE)),
[kernel_bin]"r"(boot_data->kernel_bin),"c"(boot_data)
: "rax", "memory"
);

asm volatile("cli;hlt");
}