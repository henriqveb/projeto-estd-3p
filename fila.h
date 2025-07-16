#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reserva.h"

// Nó da fila
typedef struct NoFila {
    Reserva dados;
    struct NoFila* proximo;
} NoFila;

// Estrutura da Fila
typedef struct {
    NoFila* inicio;
    NoFila* fim;
} Fila;

// Protótipos das funções da Fila
Fila* criar_fila();
void enfileirar(Fila* f, Reserva dados);
void visualizar_reservas(Fila* f);
int verificar_conflito(Fila* f, const char* data, const char* hora_inicio, const char* hora_fim);
Reserva* remover_reserva(Fila* f, const char* nome, const char* data, const char* hora);
void liberar_fila(Fila* f);

#endif