#include "msxgl.h"
#include "bios.h"
#include "vdp.h"
#include "core.h" // Para Halt()

// Endereços de VRAM para duas áreas de SCREEN 1
#define PNT_SCREEN1 0x1800
#define PNT_SCREEN2 0x1980
#define CT_ADDR     0x2000
#define PGT_ADDR    0x0000
#define SAT_ADDR    0x1B00
#define SGT_ADDR    0x0800

void wait(u8 t) {
    for (u8 i = 0; i < t; i++)
        Halt();
}

// Função para alternar a exibição dos caracteres
void alternarCaracteres(i8 toggle) {
    char c1 = (toggle == 1) ? '#' : '*';
    char c2 = (toggle == 1) ? '*' : '#';

    VDP_FillVRAM_16K(c1, PNT_SCREEN1, 32 * 6);
    VDP_FillVRAM_16K(c2, PNT_SCREEN1 + 0xC0, 32 * 6);
    VDP_FillVRAM_16K(c1, PNT_SCREEN2, 32 * 6);
    VDP_FillVRAM_16K(c2, PNT_SCREEN2 + 0xC0, 32 * 6);
}

void main() {
    i8 toggleState = 1;
    Bios_InitScreen1Ex(PNT_SCREEN1, CT_ADDR, PGT_ADDR, SAT_ADDR, SGT_ADDR, 15, 1, 1);

    while (1) {
        wait(30);
        alternarCaracteres(toggleState);
        toggleState = -toggleState; // Alterna o estado
    }
}
