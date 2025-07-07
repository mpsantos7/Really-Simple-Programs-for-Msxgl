// Write messages on screen 5 with two 
// different bitmap fonts
//
#include "msxgl.h"
#include "print.h"

// Fonts data
#include "font/font_bios_latin_br.h"
#include "font/font_mgl_big1.h"

void main()
{
	// Configura a SCREEN 5
	VDP_SetMode(VDP_MODE_SCREEN5);
	VDP_SetColor(COLOR_BLACK);
	VDP_EnableVBlank(TRUE);
	VDP_ClearVRAM();
    // Mensagem 1 - Alô Marcelo com fonte bios BR
 	Print_SetBitmapFont(g_Font_BIOS_BR);
	Print_SetColor(COLOR_WHITE, COLOR_BLACK);
	Print_SetPosition(5, 50);
	Print_DrawText("Al\x93 mundo !");
	Print_SetPosition(5, 60);
	Print_DrawText("Qual o seu nome ?");
    // Mensagem 2 - Como vai ? com BIG
    Print_SetBitmapFont(g_Font_MGL_Big1);
	Print_SetColor(COLOR_WHITE, COLOR_BLACK);
    Print_SetPosition(5, 80); // Linha abaixo
    Print_DrawText("Como vai ?");

    while(1); // Loop infinito
}
