cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(onl_tetris VERSION 0.1.0 LANGUAGES C ASM_NASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_link_options(-nostdlib -m32 "-Wl,-m" "elf_i386" -Wl,-T,${CMAKE_CURRENT_SOURCE_DIR}/src/linker/linker.ld)

set(ASM_SOURCES "src/bootloader/boot.asm")

file(GLOB_RECURSE C_SOURCES
    "src/kernel.c"
    "src/libs/*.c"
)

set_source_files_properties(${C_SOURCES} PROPERTIES 
    COMPILE_FLAGS "-masm=att -ffreestanding -nostdlib -Os -m32"
)

set_source_files_properties(${ASM_SOURCES} PROPERTIES 
    COMPILE_FLAGS "-f elf32"
)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -f elf32 -o <OBJECT> <SOURCE>")

add_executable(onl_tetris ${ASM_SOURCES} ${C_SOURCES})
target_include_directories(onl_tetris PRIVATE src)

set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/os_image")
set(BIN_FILE   "${OUTPUT_DIR}/onl_tetris.bin")
set(IMG_FILE   "${OUTPUT_DIR}/onl_tetris.img")

add_custom_command(
    TARGET onl_tetris
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
    COMMAND objcopy -O binary $<TARGET_FILE:onl_tetris> ${BIN_FILE}
    COMMAND dd if=/dev/zero of=${IMG_FILE} bs=512 count=2880
    COMMAND dd if=${BIN_FILE} of=${IMG_FILE} conv=notrunc
    COMMENT "Generating 1.44MB floppy disk image: ${IMG_FILE}"
)
