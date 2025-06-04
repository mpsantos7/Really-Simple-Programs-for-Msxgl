// Gera um efeito ao apertar a barra de espaço
//  LibModules = [ "system", "bios", "vdp", "print", "input","psg" ];

#include "msxgl.h"
#include "psg.h"
#include "font/font_mgl_sample8.h"

void main()
{
    // Inicializa o vídeo
    VDP_SetMode(VDP_MODE_SCREEN1); 
    VDP_SetColor2(COLOR_BLACK, COLOR_WHITE); 
    VDP_ClearVRAM();

    // Exibe a mensagem na tela
    Print_SetPosition(8, 10);
	//Print_DrawFormat("%1x ", 8);
	Print_SetTextFont(g_Font_MGL_Sample8, 0);
    Print_DrawText("Aperte a barra de espaco!");

    while(1)
    {
        if(Keyboard_IsKeyPressed(KEY_SPACE)) // Verifica se a barra de espaço foi pressionada
        {
            PSG_SetTone(0, 0x400);  // Define o tom no primeiro canal
            PSG_SetNoise(0x10);     // Define o ruído no terceiro canal
            PSG_SetMixer(0b11110110); // Ativa tom no primeiro canal e ruído no terceiro canal
            PSG_SetVolume(0, 0xF);  // Volume máximo no primeiro canal
            PSG_SetVolume(2, 0xF);  // Volume máximo no terceiro canal
            PSG_Apply(); // Aplica a configuração
        }
        else
        {
            PSG_SetVolume(0, 0); // Silencia o primeiro canal
            PSG_SetVolume(2, 0); // Silencia o terceiro canal
            PSG_Apply(); // Aplica a configuração
        }
        
        Halt(); // Espera até o próximo ciclo
    }
}
