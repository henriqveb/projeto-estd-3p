#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>
#include "reserva.h"

// Nó da pilha
typedef struct NoPilha {
    Reserva dados;
    struct NoPilha* proximo;
} NoPilha;

// Estrutura da Pilha
typedef struct {
    NoPilha* topo;
} Pilha;

// Protótipos das funções da Pilha
Pilha* criar_pilha();
void empilhar(Pilha* p, Reserva dados);
void liberar_pilha(Pilha* p);

#endif