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
        __bss_start__ = .;
        *(.bss*);
        *(COMMON);
        . = __bss_start__ + 0x4000;
        __bss_end__ = .;
    }
}