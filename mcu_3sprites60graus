#include "msxgl.h"  // Inclui a biblioteca principal MSXgl

// defines
#define Width 256
#define Height 192
#define TABLE_SIZE 31 // Tamanho da tabela ajustado para 31 valores
#define MIN_RADIUS 16 // Raio mínimo
#define MAX_RADIUS 84 // Raio máximo

// Tabelas de seno e cosseno
const i8 SIN_TABLE[TABLE_SIZE] = {
     0,  23,  45,  67,  87, 105, 120, 126, 127, 126, 120, 105,  87,  67,  45,  23,
     0, -23, -45, -67, -87,-105,-120,-126,-127,-126,-120,-105, -87, -67, -45
};

const i8 COS_TABLE[TABLE_SIZE] = {
   127, 126, 120, 105,  87,  67,  45,  23,   0, -23, -45, -67, -87,-105,-120,-126,
  -127,-126,-120,-105, -87, -67, -45, -23,   0,  23,  45,  67,  87, 105, 120
};

// Dados dos sprites
const u8 g_SpriteData[] = {
    0x3C, 0x42, 0xA9, 0x85, 0xA9, 0x91, 0x42, 0x3C  // Smiley
};
const u8 g_SpriteDataNeg[] = {
    0xC3, 0xBD, 0x56, 0x7A, 0x56, 0x6E, 0xBD, 0xC3  // Negativo do Smiley
};
const u8 g_SpriteDataCruz[] = {
    0b00011000,
    0b00011000,
    0b00011000,
    0b11111111,
    0b11111111,
    0b00011000,
    0b00011000,
    0b00011000
};

// Função principal
void main()
{
    // Ângulos iniciais dos sprites
    u8 angle_sprite1 = 0;    // Smiley no ângulo 0
    u8 angle_sprite2 = 10;   // Negativo no ângulo 1/3
    u8 angle_sprite3 = 20;   // Cruz no ângulo 2/3

    u8 radius = MAX_RADIUS;  // Raio inicial
    i8 radius_direction = -1; // Controle do raio (-1 = diminuindo, +1 = aumentando)

    // Inicializa SCREEN 2
    VDP_SetMode(VDP_MODE_GRAPHIC2);
    VDP_ClearVRAM();

    // Configura padrões dos sprites
    VDP_SetSpriteFlag(VDP_SPRITE_SIZE_8);
    VDP_LoadSpritePattern(g_SpriteData, 0, 1);       // Smiley no índice 0
    VDP_LoadSpritePattern(g_SpriteDataNeg, 1, 1);    // Negativo no índice 1
    VDP_LoadSpritePattern(g_SpriteDataCruz, 2, 1);   // Cruz no índice 2

    while (1)
    {
        Halt(); // Aguarda próxima interrupção vertical (VBLANK)
		// Calcula posições dos sprites
        u8 sprite1_x = Width / 2 + (radius * COS_TABLE[angle_sprite1]) / 128;
        u8 sprite1_y = Height / 2 + (radius * SIN_TABLE[angle_sprite1]) / 128;

        u8 sprite2_x = Width / 2 + (radius * COS_TABLE[angle_sprite2]) / 128;
        u8 sprite2_y = Height / 2 + (radius * SIN_TABLE[angle_sprite2]) / 128;

        u8 sprite3_x = Width / 2 + (radius * COS_TABLE[angle_sprite3]) / 128;
        u8 sprite3_y = Height / 2 + (radius * SIN_TABLE[angle_sprite3]) / 128;

        // Atualiza posição dos sprites
        VDP_SetSpriteSM1(0, sprite1_x, sprite1_y, 0, 15);  // Smiley
        VDP_SetSpriteSM1(1, sprite2_x, sprite2_y, 1, 11);  // Negativo
        VDP_SetSpriteSM1(2, sprite3_x, sprite3_y, 2, 7);   // Cruz

        // Incrementa ângulos
        angle_sprite1 = (angle_sprite1 + 1) % TABLE_SIZE;
        angle_sprite2 = (angle_sprite2 + 1) % TABLE_SIZE;
        angle_sprite3 = (angle_sprite3 + 1) % TABLE_SIZE;

        // Atualiza o raio
        radius += radius_direction;
        if (radius <= MIN_RADIUS || radius >= MAX_RADIUS)
        {
            radius_direction *= -1; // Inverte direção do raio
        }

        Halt(); // Aguarda próxima interrupção vertical (VBLANK)
    }
}
