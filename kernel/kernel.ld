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
    .bss (NOLOAD) : ALIGN(4)
    {
        __bss_start = .;
        *(.bss)
        . += 0x1000;  /* Manually reserving 4KB of space */
        __bss_end = .;
    }
}