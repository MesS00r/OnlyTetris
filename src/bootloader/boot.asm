[BITS 16]
[ORG 0x7C00]

_start:
; $=======================================$
; | STANDARD INIT                         |
; $=======================================$
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
    mov si, msg
    call print_msg

    mov si, (18 * 3)
    call sleep

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

; функция сна на n тиков
; 1 аргумент:
; si - время ожидания в тиках
sleep:
    mov ax, [0x046C]
    add si, ax
.wait:
    cmp [0x046C], si
    jne .wait
    ret

msg: db "Hello. Wait 3 seconds...", 10, 13, 0

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
; | 32 BIT PROTECTED MODE                 |
; $=======================================$
[BITS 32]
_32bit_start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x90000

    hlt
    jmp $

times 510-($-$$) db 0
dw 0xAA55