import std/macros

# STD COLORS
type VGA_STD_COLORS* = enum
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GREY,
    DARK_GREY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    WHITE

# GREY COLORS
type VGA_GREY_COLORS* = enum
    GREY_BLACK,
    GREY_BBBBBB,
    GREY_BBBBB,
    GREY_BBBB,
    GREY_BBB,
    GREY_BB,
    GREY_B,
    GREY_N,
    GREY_L,
    GREY_LL,
    GREY_LLL,
    GREY_LLLL,
    GREY_LLLLL,
    GREY_LLLLLL,
    GREY_LLLLLLL,
    GREY_WHITE

# OTHER_COLORS
macro const_test(r, g, b : static[uint8]) = discard
    
proc vga_color_rgb*(r, g, b : uint8) : uint8
{.exportc: "vga_color_rgb", dynlib.} =
    let r6 : uint8 = ((r.uint16 * 6) shr 8).uint8
    let g6 : uint8 = ((g.uint16 * 6) shr 8).uint8
    let b6 : uint8 = ((b.uint16 * 6) shr 8).uint8
    32 + r6*36 + g6*6 + b6

template _vga_precalcul*{ vga_color_rgb(r, g, b) }(r, g, b : uint8): uint8 =
    when compiles(const_test(r, g, b)):
        block:
            const clacul = vga_color_rgb(r, g, b)
            clacul
    else:
        vga_color_rgb(r, g, b)