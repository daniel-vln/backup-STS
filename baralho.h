#ifndef BARALHO_H
#define BARALHO_H

#include "structs.h"

// Inicializa as cartas base do jogo
void inicializa_baralho(GameState* gs);

// Embaralha as cartas que estão atualmente na pilha de compras
void embaralhar_compra(GameState* gs);

// Compra 'qtd' cartas. Se o baralho acabar, recicla o descarte.
void comprar_cartas(GameState* gs, int qtd);

int calcular_efeito(int custo);

#endif