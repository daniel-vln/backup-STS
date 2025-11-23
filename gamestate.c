#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "baralho.h"

void inicializa_inimigos(GameState* gs) { // Inicializa os inimigos fracos e fortes
    // Inimigo 1 (Fraco)
    gs->inimigos[0].id = 0; // Identifica o inimigo
    gs->inimigos[0].tipo = 1; // Tipo dele (Fraco)
    gs->inimigos[0].hp_max = 10 + (rand() % 21); // HP entre 10 e 30
    gs->inimigos[0].hp_atual = gs->inimigos[0].hp_max;
    gs->inimigos[0].escudo = 0;
    gs->inimigos[0].vivo = 1;
    gs->inimigos[0].proxima_acao = 0;

    // Inimigo 2 (Forte)
    gs->inimigos[1].id = 1; // Identifica o Inimigo
    gs->inimigos[1].tipo = 2; // Tipo dele (Forte)
    gs->inimigos[1].hp_max = 40 + (rand() % 61); // HP entre 40 e 100
    gs->inimigos[1].hp_atual = gs->inimigos[1].hp_max;
    gs->inimigos[1].escudo = 0;
    gs->inimigos[1].vivo = 1;
    gs->inimigos[1].proxima_acao = 0;
}

void inicializa_jogador(GameState* gs) {
    gs->hp_jogador = 100;      // Vida padrão
    gs->energia_jogador = 3;  // Energia padrão por turno
    gs->escudo_jogador = 0;
    
    // Zerar contadores de pilhas
    gs->qtd_mao = 0;
    gs->qtd_descarte = 0;
    gs->qtd_compra = 0;
}

void setup_inicial(GameState* gs) {
    // 1. Cria as cartas no array 'baralho' (sua função existente)
    inicializa_baralho(gs);
    
    // 2. Define status do jogador
    inicializa_jogador(gs);
    
    // 3. Configura os inimigos
    inicializa_inimigos(gs);

    // 4. PREPARAÇÃO DO BARALHO DE COMPRA
    // No início, todas as cartas geradas vão para a pilha de compra
    for(int i = 0; i < gs->qtd_baralho; i++) {
        gs->compra[i] = gs->baralho[i];
    }
    gs->qtd_compra = gs->qtd_baralho;
}