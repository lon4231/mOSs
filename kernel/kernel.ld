ENTRY(kmain);
SECTIONS {    
    .text : {
        KEEP(*(.kernel*));
        *(.text*);
    }
    .data : {
        *(.data*);
    }
    .rodata : {
        *(.rodata*);
    }
    .bss : {
        __bss_start = .;
        *(.bss)
        *(COMMON)
        . += 0x4000;
        __bss_end = .;
    }
}