import std/os
import std/strformat

switch("cpu", "i386")
switch("os", "standalone")
switch("cc", "gcc")

switch("mm", "arc")
switch("panics", "on")
switch("define", "useMalloc")

switch("gcc.exe", "i686-elf-gcc")
switch("gcc.linkerexe", "i686-elf-gcc")

switch("threads", "off")
switch("exceptions", "quirky")
switch("stackTrace", "off")
switch("lineTrace", "off")

switch("path", ".")

const
    currentDir = currentSourcePath().parentDir()
    buildDir = "build" / "os_image"

    linkerPath = currentDir / "src" / "linker" / "linker.ld"

    nasmBuildPath = currentDir / "build" / ""
    nasmSrcPath = currentDir / "src" / "bootloader" / "boot.asm"
    nasmObjPath = currentDir / "build" / "boot.o"

    nimImgPath = currentDir / "build" / "os_image" / "os_image.img"
    nimSrcPath = currentDir / "src" / "main.nim"

switch("passC", "-masm=intel -ffreestanding -nostdlib -Os -m32")
switch("passL", &"-T {linkerPath} -nostdlib -m32 {nasmObjPath}")

task(build, "Build an OS image"):
    mkdir(currentDir / buildDir)

    try:
        exec(&"nasm -I {nasmBuildPath} -f elf32 {nasmSrcPath} -o {nasmObjPath}")
        echo("The bootloader was built successfully.")

        exec(&"nim c --noMain -o:{nimImgPath} {nimSrcPath}")
        echo("The kernel was built successfully.")
    except OSError as err:
        echo("Build failed with error: ", err.msg)
        quit(1)