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
        __bss_start__ = .;       /* Start of the .bss section */
        *(.bss*);                /* All input .bss sections */
        *(COMMON);               /* Include common symbols */
        . = __bss_start__ + 0x2000; /* Explicitly set the size of .bss to 4 KB */
        __bss_end__ = .;         /* End of the .bss section */
    }
}