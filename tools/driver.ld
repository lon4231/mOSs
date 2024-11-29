ENTRY(driver_init);
SECTIONS {    
    .text : {
        KEEP(*(.driver*));
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
        . = __bss_start__ + 0x1000;
        __bss_end__ = .;
    }
}