import my_libs/libs_nim/vga_color

{.compile: src/kernel.c.}

proc `_kernel`() {.importc: "_kernel".}

proc `_main`()
{.
exportc: "_main",
codegenDecl: "__attribute__((section(\".main\"))) $# $#$#"
.} =
    `_kernel`()
    asm "hlt\njmp ."