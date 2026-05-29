#!/bin/bash
set -e

rm -rf build/
mkdir -p build/os_image

nasm -f elf32 src/bootloader/boot.asm -o build/boot.o

nim cc --compileOnly:on --cpu:i386 --os:standalone --mm:arc --panics:on -d:danger --noMain --nimcache:build/nim_c_gen src/kernel.nim
rm -rf build/nim_c_gen/*.json

GCC="$HOME/cross_gcc13/bin/i686-elf-gcc"
NIMLIB="$HOME/.choosenim/toolchains/nim-2.2.10/lib"
$GCC -I$NIMLIB -Ibuild/nim_c -masm=intel -ffreestanding -nostdlib -Os -m32 -c build/nim_c_gen/*.c

mv *.o build/ 2>/dev/null || true

LD="$HOME/cross_gcc13/bin/i686-elf-ld"
$LD -T src/linker/linker.ld --oformat binary -nostdlib -m elf_i386 build/*.o -o build/os_image/os_image.img

TRUNCATE="/usr/bin/truncate"
$TRUNCATE -s 1440k build/os_image/os_image.img

echo "Is done."