#ifndef RESERVA_H
#define RESERVA_H

// Estrutura que armazena os dados de uma única reserva
typedef struct {
    char nome[50];
    char data[11]; // Formato "dd/mm/aaaa"
    char hora[6];  // Formato "hh:mm" (início)
    char hora_fim[6]; // Formato "hh:mm" (fim)
    char motivo[100];
} Reserva;

#endif