// Example Hardware Sprites Collision
// Using Sprites 16x16 at Screen 1
// only working in MSX2
// MSXGL

#include "msxgl.h"  // Inclui a biblioteca principal MSXgl
#include "print.h"


// Fonts data
#include "font/font_mgl_sample8.h"

// defines
//#define Width 256
//#define Height 192

// Dados do sprite (16x16 pixels formato binario)

const u8 g_SpriteC[] = {
0xFF,0xFF,0xFF,0xE0,0xE0,0xE0,0xE0,0xE0,
0xE0,0xE0,0xE0,0xE0,0xE0,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF
};

const u8 g_SpriteCI[] = {
0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0x07,0x07,0x07,0x07,0x07,
0x07,0x07,0x07,0x07,0x07,0xFF,0xFF,0xFF
};

// const u8 g_Bola[] = {
// 0x00,0x07,0x1F,0x3F,0x7F,0x7F,0xFF,0xFF,
// 0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x1F,0x07,
// 0x00,0xC0,0xF0,0xF8,0xFC,0xFC,0xFE,0xFE,
// 0xFE,0xFE,0xFE,0xFC,0xFC,0xF8,0xF0,0xC0
// };

void main()
{
	u8 x1=140,y1=80; //pos inicial SpriteCI
	c8 k1; // leitura joystick/cursores
	bool collision;
    // Inicializa SCREEN 1
 	VDP_SetMode(VDP_MODE_SCREEN1);
	VDP_EnableVBlank(TRUE);
	Bios_SetKeyClick(FALSE);
	VDP_ClearVRAM();
	Bios_ChangeColor(15,0,0);
    // Configura sprites
    VDP_SetSpriteFlag(VDP_SPRITE_SIZE_16);   //addr, index, count
    VDP_LoadSpritePattern(g_SpriteC, 0, 4);  //    , only multiple of 4, 16x16 mode use 4     
    VDP_LoadSpritePattern(g_SpriteCI, 4, 4); 
    //VDP_LoadSpritePattern(g_Bola, 8, 4);
    VDP_SetSpriteSM1(0, 80, 80, 0, 15); //index,x,y,shape,cor	
 	Bios_Beep();
	Print_SetTextFont(g_Font_MGL_Sample8, 1); // Upload font tile-set from index 1
	Print_SetPosition(1, 0);              
	Print_DrawText("Teste de Colisao");
    while (1)
    {
		Halt(); // Espera próxima VBLANK
		k1 = Bios_GetJoystickDirection(0);
		if (k1==1) y1--; if (k1==3) x1++; 
		if (k1==5) y1++; if (k1==7) x1--;
		VDP_SetSpriteSM1(4, x1, y1, 4, 11);
		collision = Bios_IsSpriteCollision();
		Print_SetPosition(5, 14);
 		if (collision) {
			Print_DrawText("Colisao detectada");
		} else { Print_DrawText("                 ");}
				
    }	
}
