[BITS 16]

extern _main

global _start

section .boot
_start:
; $=======================================$
; | STANDARD INIT                         |
; $=======================================$
    push dx

    xor ax, ax
    mov ds, ax
    mov es, ax

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
    pop dx
    
    mov si, _main
    call disk_read

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
; | SYS FOO                               |
; $=======================================$
; базовая функция вывода в консоль
; 1 аргумент:
; si - адрес строки для вывода
print_msg:
.loop:
    lodsb
    test al, al
    jz .done
    mov ah, 0x0E
    mov bh, 0
    int 0x10
    jmp .loop
.done:
    ret

; функция чтения с диска
; 1 аргумент:
; si - адрес для чтения
disk_read:
    mov ah, 0x02
    mov al, 4
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov bx, si
    int 0x13
    jc .err
    ret
.err:
    mov si, err_msg
    call print_msg

    hlt
    jmp $

err_msg: db "Disk read error.", 10, 13, 0

; $=======================================$
; | 32 BIT PROTECTED MODE                 |
; $=======================================$
[BITS 32]
_32bit_start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x7C00

    jmp _main