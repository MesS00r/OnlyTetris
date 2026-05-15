ENTRY(_start);

SECTIONS {

    . = 0x7C00;

    .bootloader : {
        *(.boot)
        *(.text.boot)

        . = 510;

        SHORT(0xAA55);
    }

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