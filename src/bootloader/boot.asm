[BITS 16]

global _start

section .boot

_start:
; $=======================================$
; | STANDARD INIT                         |
; $=======================================$
    xor ax, ax ; очистить ax
    mov ds, ax ; очистить ds
    mov es, ax ; очистить es

    mov [boot_drive], dl ; сохранить dl в boot_drive

    cli            ; запретить прерывания
    mov ss, ax     ; очистить ss
    mov sp, 0x7C00 ; установить стек на 0x7C00
    sti            ; разрешить прерывания

    mov si, ax ; очистить si
    mov di, ax ; очистить di
    cld        ; сброс DF (флага направления)

; $=======================================$
; | MAIN CODE                             |
; $=======================================$
    mov ah, 0x02         ; 0x02 - функция чтения с диска
    mov al, 8            ; 8 секторов для чтения
    mov ch, 0            ; 0 - номер цилиндра
    mov cl, 2            ; 2 - номер сектора
    mov dh, 0            ; 0 - номер головки
    mov dl, [boot_drive] ; загружаем сохр. dl (boot_drive) (номер диска)
    mov bx, KERNEL_MAIN  ; записываем адрес буфера памяти в bx
    int 0x13             ; BIOS прерывание 0x13
    jc disk_err          ; переходим в disk_err, если произошла ошибка

; $=======================================$
; | VGA INIT                              |
; $=======================================$
    ; mov ah, 0x00 ; 0x00 - функция "установить видеорежим"
    ; mov al, 0x12 ; 0x12 - установить режим: 640x480, 16 color, VGA
    ; int 0x10     ; BIOS прерывание 0x10

    mov ax, 0x4F01
    mov cx, 0x101
    mov di, VESA_ADDR
    int 0x10
    cmp ax, 0x004F
    jne vesa_err

    mov eax, [VESA_ADDR + 0x28]
    mov [VESA_BUF], eax

    mov ax, 0x4F02
    mov bx, 0x4101
    int 0x10

    cli ; запретить прерывания
; $=======================================$
; | TRANSITION TO PROTECTED MODE          |
; $=======================================$
    lgdt [gdt] ; загрузить таблицу дескрипторов

    mov eax, cr0 ; загрузить cr0 в eax
    or eax, 1    ; установить 0-й бит на 1
    mov cr0, eax ; загрузить eax в cr0

    jmp 0x08:_32bit_start ; дальний переход в _32bit_start

; $=======================================$
; | GDT                                   |
; $=======================================$
align 4 ; выравнивание на 4
; далее идут таблицы дескрипторов
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
    mov si, err_disk_msg ; загрузить адрес err_disk_msg в si
.loop:
    lodsb           ; загрузить символ из si (err_msg) в al
    test al, al     ; проверить al
    jz .done        ; переход в .done, если ZF = 1
    mov ah, 0x0E    ; 0x0E - функция печати символа без атрибутов
    mov bh, 0       ; 0 - номер страницы
    int 0x10        ; BIOS прерывание 0x10
    jmp .loop       ; переход в .loop (цикл)
.done:
    hlt             ; остановить процессор
    jmp $           ; бесконечный цикл, если hlt не сработал

err_disk_msg: db "Disk read error.", 10, 13, 0
boot_drive: db 0

; $=======================================$
; | VESA ERROR                            |
; $=======================================$
vesa_err:
    mov si, err_vesa_msg ; загрузить адрес err_msg в si
.loop:
    lodsb           ; загрузить символ из si (err_msg) в al
    test al, al     ; проверить al
    jz .done        ; переход в .done, если ZF = 1
    mov ah, 0x0E    ; 0x0E - функция печати символа без атрибутов
    mov bh, 0       ; 0 - номер страницы
    int 0x10        ; BIOS прерывание 0x10
    jmp .loop       ; переход в .loop (цикл)
.done:
    hlt             ; остановить процессор
    jmp $           ; бесконечный цикл, если hlt не сработал

err_vesa_msg: db "VESA init error.", 10, 13, 0
VESA_ADDR equ 0x9000
VESA_BUF equ 0x7B00

; $=======================================$
; | 32 BIT PROTECTED MODE                 |
; $=======================================$
[BITS 32]
_32bit_start:
    mov ax, 0x10     ; загрузить 0x10 в ax
    mov ds, ax       ; загрузить ax в ds
    mov es, ax       ; загрузить ax в es
    mov fs, ax       ; загрузить ax в fs
    mov gs, ax       ; загрузить ax в gs
    mov ss, ax       ; загрузить ax в ss
    mov esp, 0x90000 ; установить стек на 0x90000

    jmp KERNEL_MAIN ; переход в KERNEL_MAIN (0x7E00)
    ; запуск ядра ОС (В 1 конец)

KERNEL_MAIN equ 0x7E00