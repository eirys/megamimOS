OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)
ENTRY(megamimOS_entrypoint)

SECTIONS {
    . = 1M;

    .text : {
        KEEP(*(.megamimOS_handle))
        *(.text .text.*)
    }

    . += CONSTANT(MAXPAGESIZE);

    .rodata : {
        *(.rodata .rodata.*)
    }

    . += CONSTANT(MAXPAGESIZE);

    .data : {
        *(.data .data.*)
    }

    .bss : {
        *(COMMON)
        *(.bss .bss.*)
    }

    /DISCARD/ : {
        *(.eh_frame)
        *(.note .note.*)
    }
}