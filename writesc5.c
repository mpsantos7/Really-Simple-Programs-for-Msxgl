// Write messages on screen 5 with two 
// different bitmap fonts
//
#include "msxgl.h"
#include "print.h"
#include "ascii.h"
// Fonts data
#include "font/font_bios_latin_br.h"
#include "font/font_mgl_big1.h"

c8 g_StringBuffer[64];
c8 g_NameBuffer[64];
// From vatt.c Aineko https://github.com/aoineko-fr/VATT/blob/master/vatt.c
//-----------------------------------------------------------------------------
// Get next character from user
c8 GetCharacter()
{
	__asm
		push	ix
		ld		ix, #R_CHGET
		ld		iy, #0x0000
		call	R_CALSLT
		pop		ix
	__endasm;
}

//-----------------------------------------------------------------------------
// Test a given screen mode with a given test function
const c8* GetStringAt(u8 x, u8 y)
{
	Print_SetPosition(x, y);
	c8* ptr = g_NameBuffer;
	c8 chr = 0;
	while(chr != ASCII_RETURN)
	{
		chr = GetCharacter();
		if((chr == ASCII_BS) && (ptr > g_NameBuffer))
		{
			Print_Backspace(1);
			ptr--;
		}

		if((chr == ASCII_SPACE) && (ptr == g_NameBuffer))
			continue;

		if((chr >= ASCII_SPACE) && (chr <= '~'))
		{
			Print_DrawChar(chr);
			*ptr = chr;
			ptr++;
		}
	}
	*ptr = 0;
	return g_NameBuffer;
}

void main()
{
	u8 name_len;
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
	GetStringAt(5,70);
    // Mensagem 2 - Como vai ? com BIG
    Print_SetBitmapFont(g_Font_MGL_Big1);
	Print_SetColor(COLOR_WHITE, COLOR_BLACK);
    Print_SetPosition(5, 80); // Linha abaixo
    Print_DrawText("Como vai ");
	Print_SetPosition(72, 80);
	name_len=String_Length(g_NameBuffer);
	Print_DrawText(g_NameBuffer);
	Print_SetPosition(72+name_len*8, 80);
	Print_DrawText(" ?");

	
    while(1); // Loop infinito
}
