[BITS 16]

global _start

section .boot

_start:
; $=======================================$
; | STANDARD INIT                         |
; $=======================================$
    xor ax, ax
    mov ds, ax
    mov es, ax

    mov [boot_drive], dl

    cli
    mov ss, ax
    mov sp, 0x7C00
    sti

    mov si, ax
    mov di, ax
    cld

; $=======================================$
; | MAIN CODE                             |
; $=======================================$
    mov ah, 0x02
    mov al, 8
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [boot_drive]
    mov bx, KERNEL_MAIN
    int 0x13
    jc disk_err

    mov ah, 0
    mov al, 0x13
    int 0x10

    cli

; $=======================================$
; | TRANSITION TO PROTECTED MODE          |
; $=======================================$
    lgdt [gdt]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:_32bit_start

; $=======================================$
; | GDT                                   |
; $=======================================$
align 4
gdt_start:
    dd 0, 0
gtb_code:
    dw 0xFFFF, 0x0000
    db 0x00, 0b10011010, 0b11001111, 0x00
gdt_data:
    dw 0xFFFF, 0x0000
    db 0x00, 0b10010010, 0b11001111, 0x00
gdt_end:

gdt:
    dw gdt_end - gdt_start - 1
    dd gdt_start

; $=======================================$
; | DISK ERROR                            |
; $=======================================$
disk_err:
    mov si, err_msg
.loop:
    lodsb
    test al, al
    jz .done
    mov ah, 0x0E
    mov bh, 0
    int 0x10
    jmp .loop
.done:
    hlt
    jmp $

err_msg: db "Disk read error.", 10, 13, 0
boot_drive: db 0

; $=======================================$
; | 32 BIT PROTECTED MODE                 |
; $=======================================$
[BITS 32]
_32bit_start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x7C00

    jmp KERNEL_MAIN

KERNEL_MAIN equ 0x7E00