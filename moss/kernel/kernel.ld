ENTRY(kmain);

SECTIONS {
    . = 0xffffffff80000000;

    .text : {
        *(.text*);
    }
    .rodata : {
        *(.rodata*);
    }
    .data : {
        *(.data*);
    }
    .bss : {
        *(.bss*);
    }

    /DISCARD/ : {
        *(.comment)
        *(.note*)
        *(.eh_frame)
        *(.gcc_except_table)
        *(.debug*)
        *(.symtab)
        *(.strtab)
        *(.shstrtab)
    }
}
