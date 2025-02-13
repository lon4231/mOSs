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
        . += 0x1000;  /* Manually reserving 4KB of space */
        __bss_end = .;
    }
}