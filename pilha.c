#include "pilha.h"

// Cria e inicializa uma pilha vazia
Pilha* criar_pilha() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro de alocacao de memoria para pilha!\n");
        exit(1);
    }
    p->topo = NULL;
    return p;
}

// Adiciona uma reserva no topo da pilha (empilha)
void empilhar(Pilha* p, Reserva dados) {
    NoPilha* novo_no = (NoPilha*) malloc(sizeof(NoPilha));
    if (novo_no == NULL) {
        printf("Erro de alocacao de memoria para no da pilha!\n");
        return;
    }
    novo_no->dados = dados;
    novo_no->proximo = p->topo;
    p->topo = novo_no;
}

// Libera toda a memória alocada para a pilha
void liberar_pilha(Pilha* p) {
    NoPilha* atual = p->topo;
    while (atual != NULL) {
        NoPilha* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(p);
}