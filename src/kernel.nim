proc sysMain() {.
    codegenDecl: "__attribute__((section(\".main\"))) $# $#$#"
.} =
    let
        vesa_ptr = cast[ptr uint32](0x7B00)[]
        vesa = cast[ptr UncheckedArray[uint8]](vesa_ptr)

    for i in 0..<(640 * 480):
        vesa[i] = (i mod 256).uint8

    asm "hlt\njmp ."

sysMain()