//   Em projec_config.js, modules:
//  "arkos/akg_player", "compress/pletter"
//

#include "msxgl.h"
#include "arkos/akg_player.h"
#include "compress/pletter.h"
#include "teste1pos.h"
#include "font/font_mgl_sample8.h"
#define MUSIC_ADDRESS 0xE000


// This char animation is from aineko
const u8 g_ChrAnim[] = { '|', '\\', '-', '/' };
bool g_VBlank = FALSE;

// VBlank Hook para sincronização
void VBlankHook()
{
	g_VBlank = TRUE;
}

void WaitVBlank()
{
	while (!g_VBlank) {}
	g_VBlank = FALSE;
}

void main()
{
	// Inicializa a tela (SCREEN 1 / modo texto)
	VDP_SetMode(VDP_MODE_SCREEN1);
	VDP_ClearVRAM();
	VDP_EnableVBlank(TRUE);
	VDP_SetColor(0xF4);

	//Print_Initialize();
	Print_SetMode(PRINT_MODE_TEXT);
	Print_SetTextFont(g_Font_MGL_Sample8, 1);

	// Mostra mensagem
	Print_DrawTextAt(1, 2, "Tocando:");
	Print_DrawTextAt(1, 3, "Minha musica");

	// Instala o hook para sincronização com VBlank
	Bios_SetHookCallback(H_TIMI, VBlankHook);
    Pletter_UnpackToRAM((const void *)g_Music, (void *)MUSIC_ADDRESS);
	// Inicia a música (sem mapper, a música já está acessível diretamente)
	AKG_Init((const void *)MUSIC_ADDRESS, 0);

	u8 frame = 0;
	while (1)
	{
		WaitVBlank();

		// Atualiza a música
		AKG_Decode();

		// Anima sinal de vida
		Print_DrawCharAt(39, 0, g_ChrAnim[frame++ & 0x03]);
	}
}

/*
But this is not the right way to have a music in your 32 KB ROM.
The right way is:
Create a music in Arkos Tracker 2 (or 3), or import an existing Arkos music (there is several samples include with the tracker),
Export the music in AKG format, choosing binary data option and an address where the music will be place when replayer; let say 0xE000 (an address in RAM),
With a script, compress the AKG with Pletter (to make it small in your 32 KB ROM), then convert binary file to header file using MSXbin (see command line bellow),
Now you can add Pletter module to your project configuration (project_config.js) then include the music file header in your program,
To play it, you just need to : unpack the music in the header to address 0xE000, then use AKG_Init at this same address,
And voila! You have a way to add great PSG music with a small size and performance cost.,

The command line to convert your music:
%Tools%\compress\Pletter\pletter datasrc\my_music.akg  datasrc\my_music.pl5
%MSXtk%\MSXbin datasrc\my_music.pl5 -ad -t g_MyMusic -o content\my_music.h
 
To unpack and play your music, use:
#define MUSIC_ADDRESS 0xE000
Pletter_UnpackToRAM((const void *)g_MyMusic, (void *)MUSIC_ADDRESS);
AKG_Init((const void *)MUSIC_ADDRESS, 0);
*/
