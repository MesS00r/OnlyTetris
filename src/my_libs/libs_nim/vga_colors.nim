import std/macros

macro constTest(r, g, b : static[uint8]) = discard

proc vgaColorRgb*(r, g, b : uint8) : uint8
{.exportc: "vga_color_rgb".} =
    let r6 = ((r.uint16 * 6) shr 8).uint8
    let g6 = ((g.uint16 * 6) shr 8).uint8
    let b6 = ((b.uint16 * 6) shr 8).uint8
    32 + r6*36 + g6*6 + b6

template `_vgaPrecalcul`*{ vgaColorRgb(r, g, b) }(r, g, b : uint8): uint8 =
    when compiles(constTest(r, g, b)):
        block:
            const clacul = vgaColorRgb(r, g, b)
            clacul
    else:
        vgaColorRgb(r, g, b)