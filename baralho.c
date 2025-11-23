#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "utils.h"
#include "structs.h"

int calcular_efeito(int custo) {
    // Custo 0: efeito entre 1 e 5
    if (custo == 0) return 1 + (rand() % 5);
    
    // Custo 1: efeito entre 5 e 10
    if (custo == 1) return 5 + (rand() % 6); 
    
    // Custo 2: efeito entre 10 e 15
    if (custo == 2) return 10 + (rand() % 6);
    
    // Custo 3: efeito entre 15 e 30
    if (custo == 3) return 15 + (rand() % 16);
    
    return 0; 
}

void inicializa_baralho(GameState* gs){  // Inicializa o baralho
    int i = 0;
    int id_counter = 0;
    int custos_atk_fixos[] = {0, 1, 1, 1, 2, 3}; // Custos de Ataque Obrigatórios
    int custos_def_fixos[] = {0, 1, 1, 1, 2, 3}; // Custos de Defesa Obrigatórios

    // ATAQUE FIXAS
    for (int k = 0; k < 6; k++) {
        gs->baralho[i].tipo = ATAQUE;   // Seta o tipo da carta para ataque
        gs->baralho[i].custo = custos_atk_fixos[k];    // Seta o custo igualando ao vetor dos fixos
        gs->baralho[i].valor = calcular_efeito(custos_atk_fixos[k]); // Calcula o dano baseado nos custos
        gs->baralho[i].id = id_counter++;    // Identifica a carta
        i++; 
    }

    // ATAQUE ALEATÓRIAS
    for (int k = 0; k < 4; k++) {
        int custo_sorteado = rand() % 4; // Rand de 0 a 3
        
        gs->baralho[i].tipo = ATAQUE;   // Seta o tipo da carta para ataque
        gs->baralho[i].custo = custo_sorteado;   // Seta o custo aleatório da carta
        gs->baralho[i].valor = calcular_efeito(custo_sorteado); // Calcula o dano baseado no custo aleatório
        gs->baralho[i].id = id_counter++;    // Identifica a carta
        i++;
    }

    // DEFESA FIXAS
    for (int k = 0; k < 6; k++) {
        gs->baralho[i].tipo = DEFESA; // Seta o tipo da carta para defesa
        gs->baralho[i].custo = custos_def_fixos[k]; // Seta o custo igualando ao vetor dos fixos
        gs->baralho[i].valor = calcular_efeito(custos_def_fixos[k]); // Calcula o escudo baseado no custo
        gs->baralho[i].id = id_counter++;  // Identifica a carta
        i++;
    }

    // DEFESA ALEATÓRIAS
    for (int k = 0; k < 2; k++) {
        int custo_sorteado = rand() % 3; // Rand de 0 a 2
        
        gs->baralho[i].tipo = DEFESA; // Seta o tipo da carta para defesa
        gs->baralho[i].custo = custo_sorteado; // Sorteia o custo aleatório da carta
        gs->baralho[i].valor = calcular_efeito(custo_sorteado); // Calcula o escudo baseado no custo aleatório
        gs->baralho[i].id = id_counter++; // Identifica a carta
        i++;
    }

    // CARTAS ESPECIAIS
    for (int k = 0; k < 2; k++) {
        gs->baralho[i].tipo = ESPECIAL; // Seta o tipo da carta para especial
        gs->baralho[i].custo = 0; // Custo fixo em 0
        gs->baralho[i].valor = 0; // Especial não tem valor numérico
        gs->baralho[i].id = id_counter++;
        i++;
    }

    gs->qtd_baralho = 20; 
}

void embaralhar_compra(GameState* gs) { // Forma a pilha de cartas
    for (int i = gs->qtd_compra - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carta temp = gs->compra[i];
        gs->compra[i] = gs->compra[j];
        gs->compra[j] = temp;
    }
}

void comprar_cartas(GameState* gs, int qtd) {
    for (int i = 0; i < qtd; i++) {
        // 1. Verifica limite da mão (Máximo 10 cartas)
        if (gs->qtd_mao >= 20) {
            printf("Mao cheia! Nao e possivel comprar mais cartas.\n");
            break;
        }

        // 2. Verifica se o baralho de compra acabou
        if (gs->qtd_compra == 0) {
            if (gs->qtd_descarte == 0) {
                printf("Sem cartas para comprar e sem descarte para reciclar!\n");
                break;
            }
            
            // Recicla o descarte: Move tudo do descarte para compra
            printf("Reciclando descarte para pilha de compras...\n");
            for (int j = 0; j < gs->qtd_descarte; j++) {
                gs->compra[j] = gs->descarte[j];
            }
            gs->qtd_compra = gs->qtd_descarte; // Atualiza quantidade
            gs->qtd_descarte = 0;              // Zera o descarte
            
            embaralhar_compra(gs); // Embaralha a nova pilha
        }

        // 3. Efetua a compra (Pega do final do array 'compra' e põe no final de 'mao')
        gs->mao[gs->qtd_mao] = gs->compra[gs->qtd_compra - 1];
        gs->qtd_mao++;
        gs->qtd_compra--;
    }
}