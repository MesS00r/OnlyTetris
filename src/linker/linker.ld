ENTRY(_main);

SECTIONS {

    . = 0x7E00;

    .text : AT(ADDR(.text)) {
        *(.main)
        *(.text)
    }

    .rodata : AT(ADDR(.rodata)) {
        *(.rodata)
    }

    .data : AT(ADDR(.data)) {
        *(.data)
    }

    .bss : AT(ADDR(.bss)) {
        *(.bss)
    }

    /DISCARD/ : {
        *(.comment)
        *(.eh_frame)
    }
}