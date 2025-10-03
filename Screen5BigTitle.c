// mytitle_s5.c
// Example: draws "Meu jogo de MSX2" centered in SCREEN 5 using MSXgl
// Requirements (see notes below): add the "print" module and include the font header.

#include "msxgl.h"                 // includes types and modules (or specifically include print.h / vdp.h)
#include "font/font_mgl_sample8.h" // sample font (used in many MSXgl samples)

void main(void)
{
    const c8 title[] = "Meu jogo de MSX2";

    // --- Graphics mode initialization (Screen 5 = MSX2 bitmap) ---
    VDP_ClearVRAM();
    VDP_SetMode(VDP_MODE_SCREEN5);

    // --- Initialize bitmap font (example: g_Font_MGL_Sample8 is part of the project fonts) ---
    Print_SetBitmapFont(g_Font_MGL_Sample8);

    // --- Visual effect: enable outline to make letters look "bigger/stronger" ---
    Print_SetOutline(TRUE, COLOR_GRAY);

    // --- Horizontal centering: calculate approximate width in pixels ---
    // Note: font_mgl_sample8 usually has 8 px width per character; adjust if using another font.
    u8 len = 0;
    const c8 *p = title;
    while(*p++) len++;

    const u8 CHAR_W = 8;             // character width in pixels for the chosen font (adjust if needed)
    u16 textWidth = (u16)len * CHAR_W;
    u16 x = (256 - textWidth) / 2;   // Screen5: width = 256 pixels
    u16 y = 40;                      // vertical position (in pixels) - adjust as desired

    // --- Set position (in pixels for bitmap modes) and draw text ---
    Print_SetPosition(x, y);
    Print_DrawText(title);

    // --- Simple infinite loop (the program keeps the title on screen) ---
    while(1)
    {
        // You may use HALT() or other VBlank waits if preferred.
    }
}
