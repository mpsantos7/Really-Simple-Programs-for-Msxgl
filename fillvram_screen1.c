// FillVram Initialization screen 1 example

#include "msxgl.h"
#include "bios.h"
#include "vdp.h"
#include "core.h" // Para Halt()

// Endereços de VRAM para duas áreas de SCREEN 1
#define PNT_SCREEN1 0x1800
#define PNT_SCREEN2 0x3800
#define CT_ADDR     0x2000
#define PGT_ADDR    0x0000
#define SAT_ADDR    0x1B00
#define SGT_ADDR    0x0800

void wait(u8 t){
	       for(u8 i = 0; i < t; i++)
            Halt();
}

void main()
{
    u8 currentScreen = 0;
	Bios_InitScreen1Ex(PNT_SCREEN1, CT_ADDR, PGT_ADDR, SAT_ADDR, SGT_ADDR, 15, 1, 1);
    // Preenche duas áreas diferentes com caracteres diferentes

    while(1)
    {
       wait(60);
	   VDP_FillVRAM_16K('*', PNT_SCREEN1, 32 * 24); // ASCII 42 = '*'
	   wait(60);
	   VDP_FillVRAM_16K('#', PNT_SCREEN1, 32 * 24); // ASCII 35 = '#'
    }
}

