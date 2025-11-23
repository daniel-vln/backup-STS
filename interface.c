#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include "structs.h"

// Define cores para facilitar (R, G, B)
#define COR_FUNDO al_map_rgb(255, 255, 255)      // Branco
#define COR_CARTA al_map_rgb(240, 240, 240)      // Cinza claro
#define COR_BORDA al_map_rgb(0, 0, 0)            // Preto
#define COR_ATAQUE al_map_rgb(200, 50, 50)       // Vermelho
#define COR_DEFESA al_map_rgb(50, 50, 200)       // Azul
#define COR_VIDA_FUNDO al_map_rgb(100, 100, 100) // Cinza escuro
#define COR_VIDA_CHEIA al_map_rgb(50, 200, 50)   // Verde

const char* GetNomeTipo(TipoCarta tipo) {
    switch(tipo) {
        case ATAQUE: return "ATK";
        case DEFESA: return "DEF";
        case ESPECIAL: return "ESP";
        default: return "?";
    }
}

void DesenharHUD(GameState* gs, ALLEGRO_FONT* fonte) {
    int screenHeight = 600; // Altura padrão assumida
    int screenWidth = 800;  // Largura padrão assumida
    
    // --- 1. JOGADOR ---
    int xPlayer = 50;
    int yPlayer = screenHeight - 150;
    
    // Avatar quadrado
    al_draw_filled_rectangle(xPlayer, yPlayer, xPlayer + 50, yPlayer + 50, al_map_rgb(0, 0, 255));
    al_draw_text(fonte, COR_BORDA, xPlayer, yPlayer - 20, 0, "HEROI");
    
    // Barra de Vida
    float pctVida = (float)gs->hp_jogador / 100.0f;
    // Fundo da barra
    al_draw_filled_rectangle(xPlayer + 60, yPlayer, xPlayer + 260, yPlayer + 20, COR_VIDA_FUNDO);
    // Vida atual
    al_draw_filled_rectangle(xPlayer + 60, yPlayer, xPlayer + 60 + (200 * pctVida), yPlayer + 20, COR_VIDA_CHEIA);
    // Borda da barra
    al_draw_rectangle(xPlayer + 60, yPlayer, xPlayer + 260, yPlayer + 20, COR_BORDA, 2);
    
    // Texto Vida
    char textoVida[20];
    sprintf(textoVida, "%d/100", gs->hp_jogador);
    al_draw_text(fonte, al_map_rgb(255,255,255), xPlayer + 120, yPlayer + 2, 0, textoVida);

    // Energia
    al_draw_filled_circle(xPlayer + 30, yPlayer + 80, 20, al_map_rgb(255, 215, 0)); // Dourado
    char textoEnergia[5];
    sprintf(textoEnergia, "%d", gs->energia_jogador);
    al_draw_text(fonte, COR_BORDA, xPlayer + 25, yPlayer + 70, 0, textoEnergia);

    // --- 2. INIMIGOS ---
    for(int i = 0; i < 2; i++) {
        if(gs->inimigos[i].vivo) {
            int xEnemy = screenWidth - 150 - (i * 150);
            int yEnemy = screenHeight - 200;
            
            // Avatar Inimigo
            ALLEGRO_COLOR corIni = (gs->inimigos[i].tipo == 2) ? al_map_rgb(150,0,0) : al_map_rgb(255,100,0);
            al_draw_filled_rectangle(xEnemy, yEnemy, xEnemy + 50, yEnemy + 80, corIni);
            
            // Texto HP Inimigo
            char txtHpIni[10];
            sprintf(txtHpIni, "HP: %d", gs->inimigos[i].hp_atual);
            al_draw_text(fonte, COR_BORDA, xEnemy, yEnemy - 20, 0, txtHpIni);
        }
    }
}

void DesenharCartas(GameState* gs, ALLEGRO_FONT* fonte) {
    int startX = 200; 
    int startY = 450;
    int espacamento = 110;

    for (int i = 0; i < gs->qtd_mao; i++) {
        int posX = startX + (i * espacamento);
        int posY = startY;
        
        // Fundo da Carta
        al_draw_filled_rectangle(posX, posY, posX + 100, posY + 140, COR_CARTA);
        al_draw_rectangle(posX, posY, posX + 100, posY + 140, COR_BORDA, 2);
        
        // Nome/Tipo
        al_draw_text(fonte, COR_BORDA, posX + 10, posY + 10, 0, GetNomeTipo(gs->mao[i].tipo));
        
        // Custo (Bolinha azul no canto)
        al_draw_filled_circle(posX + 15, posY + 15, 10, al_map_rgb(100, 100, 255));
        char txtCusto[5];
        sprintf(txtCusto, "%d", gs->mao[i].custo);
        al_draw_text(fonte, al_map_rgb(255,255,255), posX + 12, posY + 8, 0, txtCusto);
        
        // Valor (Grande no meio)
        if(gs->mao[i].valor > 0) {
            char txtValor[5];
            sprintf(txtValor, "%d", gs->mao[i].valor);
            ALLEGRO_COLOR corVal = (gs->mao[i].tipo == ATAQUE) ? COR_ATAQUE : COR_DEFESA;
            al_draw_text(fonte, corVal, posX + 40, posY + 60, 0, txtValor);
        }
    }
}