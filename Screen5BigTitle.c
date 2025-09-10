// mytitle_s5.c
// Exemplo: desenha "Meu jogo de MSX2" centralizado em SCREEN 5 usando MSXgl
// Requisitos (ver notas abaixo): adicionar o módulo "print" e incluir o font header.

#include "msxgl.h"               // inclui tipos e módulos (ou inclua especificamente print.h / vdp.h)
#include "font/font_mgl_sample8.h" // font sample (usado em muitos samples do MSXgl)

void main(void)
{
    const c8 title[] = "Meu jogo de MSX2";

    // --- Inicialização do modo gráfico (Screen 5 = bitmap MSX2) ---
	VDP_ClearVRAM();
    VDP_SetMode(VDP_MODE_SCREEN5);

    // --- Inicializa font bitmap (exemplo: g_Font_MGL_Sample8 está nos fonts do projeto) ---
    Print_SetBitmapFont(g_Font_MGL_Sample8);

    // --- Efeito visual: ativa outline (contorno) para deixar as letras "maiores/mais fortes") ---
    Print_SetOutline(TRUE, COLOR_GRAY);

    // --- Centraliza horizontalmente: calcula largura aproximada em pixels ---
    // Observação: font_mgl_sample8 costuma ter 8 px de largura por caracter; ajuste se usar outra font.
    u8 len = 0;
    const c8 *p = title;
    while(*p++) len++;

    const u8 CHAR_W = 8;             // largura em pixels da font escolhida (ajuste se necessário)
    u16 textWidth = (u16)len * CHAR_W;
    u16 x = (256 - textWidth) / 2;   // Screen5: largura = 256 pixels
    u16 y = 40;                      // posição vertical (em pixels) - ajustar conforme desejar

    // --- Define posição (em pixels para modos bitmap) e desenha o texto ---
    Print_SetPosition(x, y);
    Print_DrawText(title);

    // --- Loop infinito simples (o programa permanece com o título na tela) ---
    while(1)
    {
        // Pode usar HALT() ou outras esperas de VBlank se preferir.
    }
}
