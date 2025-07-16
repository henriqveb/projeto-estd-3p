#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "pilha.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibir_menu() {
    printf("\n*** Sistema de Reserva da Quadra - IFAL Arapiraca ***\n");
    printf("1. Fazer nova reserva\n");
    printf("2. Visualizar todas as reservas\n");
    printf("3. Excluir uma reserva\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Fila* fila_reservas = criar_fila();
    Pilha* pilha_excluidas = criar_pilha();
    int opcao;

    while (1) {
        exibir_menu();
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1: {
                Reserva nova_reserva;
                printf("\n--- NOVA RESERVA ---\n");
                printf("Nome do responsavel: ");
                fgets(nova_reserva.nome, 50, stdin);
                nova_reserva.nome[strcspn(nova_reserva.nome, "\n")] = 0; // Remove a nova linha

                printf("Data da reserva (dd/mm/aaaa): ");
                fgets(nova_reserva.data, 11, stdin);
                nova_reserva.data[strcspn(nova_reserva.data, "\n")] = 0;
                limpar_buffer();

                printf("Hora da reserva (hh:mm): ");
                fgets(nova_reserva.hora, 6, stdin);
                nova_reserva.hora[strcspn(nova_reserva.hora, "\n")] = 0;
                limpar_buffer();

                printf("Hora de finalizacao da reserva (hh:mm): ");
                fgets(nova_reserva.hora_fim, 6, stdin);
                nova_reserva.hora_fim[strcspn(nova_reserva.hora_fim, "\n")] = 0;
                limpar_buffer();

                // Validação do tempo máximo de 2 horas
                int hora_inicio, min_inicio, hora_fim, min_fim;
                sscanf(nova_reserva.hora, "%d:%d", &hora_inicio, &min_inicio);
                sscanf(nova_reserva.hora_fim, "%d:%d", &hora_fim, &min_fim);
                int minutos_inicio = hora_inicio * 60 + min_inicio;
                int minutos_fim = hora_fim * 60 + min_fim;
                if (minutos_fim - minutos_inicio > 120 || minutos_fim - minutos_inicio <= 0) {
                    printf("\nERRO: O tempo de reserva deve ser de no máximo 2 horas e a hora final deve ser maior que a inicial!\n");
                    break;
                }

                if (verificar_conflito(fila_reservas, nova_reserva.data, nova_reserva.hora, nova_reserva.hora_fim)) {
                    printf("\nERRO: Ja existe uma reserva para este intervalo de horario!\n");
                } else {
                    printf("Motivo da reserva: ");
                    fgets(nova_reserva.motivo, 100, stdin);
                    nova_reserva.motivo[strcspn(nova_reserva.motivo, "\n")] = 0;
                    
                    enfileirar(fila_reservas, nova_reserva);
                    printf("\nSUCESSO: Reserva realizada!\n");
                }
                break;
            }
            case 2: {
                visualizar_reservas(fila_reservas);
                break;
            }
            case 3: {
                char nome_excluir[50], data_excluir[11], hora_excluir[6];
                printf("\n--- EXCLUIR RESERVA ---\n");
                printf("Nome do responsavel pela reserva a excluir: ");
                fgets(nome_excluir, 50, stdin);
                nome_excluir[strcspn(nome_excluir, "\n")] = 0;
                
                printf("Data da reserva a excluir (dd/mm/aaaa): ");
                fgets(data_excluir, 11, stdin);
                data_excluir[strcspn(data_excluir, "\n")] = 0;
                limpar_buffer();

                printf("Hora da reserva a excluir (hh:mm): ");
                fgets(hora_excluir, 6, stdin);
                hora_excluir[strcspn(hora_excluir, "\n")] = 0;
                limpar_buffer();
                
                Reserva* removida = remover_reserva(fila_reservas, nome_excluir, data_excluir, hora_excluir);

                if (removida != NULL) {
                    empilhar(pilha_excluidas, *removida);
                    printf("\nSUCESSO: Reserva excluida e movida para o historico de cancelamentos.\n");
                    free(removida);
                } else {
                    printf("\nERRO: Reserva nao encontrada com os dados informados.\n");
                }
                break;
            }
            case 4: {
                printf("\nSaindo do sistema. Obrigado!\n");
                liberar_fila(fila_reservas);
                liberar_pilha(pilha_excluidas);
                return 0;
            }
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}