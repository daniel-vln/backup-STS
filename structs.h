#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum { ATAQUE, DEFESA, ESPECIAL } TipoCarta;

typedef struct {
    TipoCarta tipo;
    int custo;
    int valor;
    int id;
} Carta;

typedef struct {
    int hp_atual;
    int hp_max;
    int escudo;
    int tipo; // 1 = Fraco, 2 = Forte
    int id; 
    
    Carta acoes[5]; 
    int qtd_acoes;      // Quantas ações ele tem no ciclo
    int proxima_acao;   // Índice da próxima ação 
    
    int vivo; // 1 = Sim, 0 = Não 
} Inimigo;

typedef struct {
    // Jogador
    Carta baralho[50];
    Carta mao[20];
    Carta compra[50];
    Carta descarte[50];

    int qtd_baralho;
    int qtd_mao;
    int qtd_compra;
    int qtd_descarte;
    
    int hp_jogador;     // Vida do jogador
    int energia_jogador;// Energia do jogador
    int escudo_jogador; // Escudo do jogador

    Inimigo inimigos[2]; 
    
} GameState;

#endif