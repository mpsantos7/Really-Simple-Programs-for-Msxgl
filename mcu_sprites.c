#include "msxgl.h"  // Inclui a biblioteca principal MSXgl

// defines
#define Width 256
#define Height 192
#define TABLE_SIZE 31 // Tamanho da tabela reduzido para 128 valores

// Tabelas de seno e cosseno (valores multiplicados por 256 para maior precisão)
const i8 SIN_TABLE[31] = {
     0,  23,  45,  67,  87, 105, 120, 126, 127, 126, 120, 105,  87,  67,  45,  23,
     0, -23, -45, -67, -87,-105,-120,-126,-127,-126,-120,-105, -87, -67, -45
};

const i8 COS_TABLE[31] = {
   127, 126, 120, 105,  87,  67,  45,  23,   0, -23, -45, -67, -87,-105,-120,-126,
  -127,-126,-120,-105, -87, -67, -45, -23,   0,  23,  45,  67,  87, 105, 120
};


// Dados do sprite (8x8 pixels em formato hexadecimal)

const u8 g_SpriteData[] = {
    0x3C, //   00111100   (canto superior arredondado)
    0x42, //   01000010   (olhos nos pontos 2 e 7)
    0xA9, //   10101001   (bochechas e olhos definidos)
    0x85, //   10000101   (espaço entre olhos)
    0xA9, //   10101001   (bochechas destacadas novamente)
    0x91, //   10010001   (contorno do sorriso)
    0x42, //   01000010   (sorriso completo)
    0x3C  //   00111100   (canto inferior arredondado)
};

const u8 g_SpriteDataNeg[] = {
    0xC3, //   11000011
    0xBD, //   10111101
    0x56, //   01010110
    0x7A, //   01111010
    0x56, //   01010110
    0x6E, //   01101110
    0xBD, //   10111101
    0xC3  //   11000011
};

// Função principal
void main()
{
    // Ângulos iniciais dos sprites
    u8 angle_sprite1 = 0;
    u8 angle_sprite2 = 15; // Diametralmente oposto (64 em 128 posições)
	u8 RADIUS =84;

    // Inicializa SCREEN 2
	
    VDP_SetMode(VDP_MODE_GRAPHIC2);
    VDP_ClearVRAM();

    // Configura sprites
    VDP_SetSpriteFlag(VDP_SPRITE_SIZE_8);
    VDP_LoadSpritePattern(g_SpriteData, 0, 1); // Padrão no índice 0
    VDP_LoadSpritePattern(g_SpriteDataNeg, 1, 1); // Padrão no índice 1

    while (1)
    {
        Halt(); // Espera próxima VBLANK
		// Calcula posições dos sprites com tabelas reduzidas
        i16 sprite1_x = Width / 2 + RADIUS * COS_TABLE[angle_sprite1] / 256;
        i16 sprite1_y = Height / 2 + RADIUS * SIN_TABLE[angle_sprite1] / 256;

        i16 sprite2_x = Width / 2 + RADIUS * COS_TABLE[angle_sprite2] / 256;
        i16 sprite2_y = Height / 2 + RADIUS * SIN_TABLE[angle_sprite2] / 256;

        // Atualiza posição
        VDP_SetSpriteSM1(0, sprite1_x, sprite1_y, 0, 15);
        VDP_SetSpriteSM1(1, sprite2_x, sprite2_y, 1, 11);

        // Incrementa ângulo
        angle_sprite1 = (angle_sprite1 + 2) % TABLE_SIZE;
        angle_sprite2 = (angle_sprite2 + 2) % TABLE_SIZE;
        Halt(); // Espera próxima VBLANK
		
    }
}
