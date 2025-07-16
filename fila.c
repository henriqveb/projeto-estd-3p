#include "fila.h"

// Cria e inicializa uma fila vazia
Fila *criar_fila()
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    if (f == NULL)
    {
        printf("Erro de alocacao de memoria para fila!\n");
        exit(1);
    }
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

// Adiciona uma reserva no final da fila
void enfileirar(Fila *f, Reserva dados)
{
    NoFila *novo_no = (NoFila *)malloc(sizeof(NoFila));
    if (novo_no == NULL)
    {
        printf("Erro de alocacao de memoria para no da fila!\n");
        return;
    }
    novo_no->dados = dados;
    novo_no->proximo = NULL;

    if (f->fim == NULL)
    { // Fila estava vazia
        f->inicio = novo_no;
        f->fim = novo_no;
    }
    else
    {
        f->fim->proximo = novo_no;
        f->fim = novo_no;
    }
}

// Exibe todas as reservas na fila
void visualizar_reservas(Fila *f)
{
    NoFila *atual = f->inicio;
    if (atual == NULL)
    {
        printf("\nNenhuma reserva ativa no momento.\n");
        return;
    }

    printf("\n--- LISTA DE RESERVAS ATIVAS ---\n");
    int i = 1;
    while (atual != NULL)
    {
        printf("Reserva %d:\n", i++);
        printf("  Nome: %s\n", atual->dados.nome);
        printf("  Data: %s\n", atual->dados.data);
        printf("  Hora: %s\n", atual->dados.hora);
        printf("  Hora fim: %s\n", atual->dados.hora_fim);
        printf("  Motivo: %s\n", atual->dados.motivo);
        printf("----------------------------------\n");
        atual = atual->proximo;
    }
}

// Converte uma string "hh:mm" para minutos
int hora_para_minutos(const char *hora)
{
    int h, m;
    sscanf(hora, "%d:%d", &h, &m);
    return h * 60 + m;
}

// Verifica se já existe uma reserva para a mesma data e intervalo de horário
int verificar_conflito(Fila *f, const char *data, const char *hora_inicio, const char *hora_fim)
{
    NoFila *atual = f->inicio;
    int novo_inicio = hora_para_minutos(hora_inicio);
    int novo_fim = hora_para_minutos(hora_fim);

    while (atual != NULL)
    {
        if (strcmp(atual->dados.data, data) == 0)
        {
            int reserva_inicio = hora_para_minutos(atual->dados.hora);
            int reserva_fim = hora_para_minutos(atual->dados.hora_fim);

            // Verifica se os intervalos se sobrepõem
            if (!(novo_fim <= reserva_inicio || novo_inicio >= reserva_fim))
            {
                return 1; // Conflito encontrado
            }
        }
        atual = atual->proximo;
    }
    return 0; // Sem conflito
}

// Remove uma reserva específica e a retorna
Reserva *remover_reserva(Fila *f, const char *nome, const char *data, const char *hora)
{
    NoFila *atual = f->inicio;
    NoFila *anterior = NULL;

    while (atual != NULL)
    {
        if (strcmp(atual->dados.nome, nome) == 0 && strcmp(atual->dados.data, data) == 0 && strcmp(atual->dados.hora, hora) == 0)
        {

            Reserva *dados_removidos = (Reserva *)malloc(sizeof(Reserva));
            if (dados_removidos == NULL)
                return NULL;

            *dados_removidos = atual->dados;

            if (anterior == NULL)
            { // Removendo o primeiro elemento
                f->inicio = atual->proximo;
            }
            else
            {
                anterior->proximo = atual->proximo;
            }

            if (f->fim == atual)
            { // Se o removido era o último
                f->fim = anterior;
            }

            free(atual);
            return dados_removidos;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return NULL; // Reserva não encontrada
}

// Libera toda a memória alocada para a fila
void liberar_fila(Fila *f)
{
    NoFila *atual = f->inicio;
    while (atual != NULL)
    {
        NoFila *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(f);
}

void cadastrar_reserva(Fila *fila_reservas, Reserva nova_reserva)
{
    if (verificar_conflito(fila_reservas, nova_reserva.data, nova_reserva.hora, nova_reserva.hora_fim))
    {
        printf("\nERRO: Ja existe uma reserva para este intervalo de horario!\n");
    }
    else
    {
        enfileirar(fila_reservas, nova_reserva);
        printf("\nReserva cadastrada com sucesso!\n");
    }
}