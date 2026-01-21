#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* =========================
   DEFINES E STRUCTS
   ========================= */

#define MAX_NOME 30
#define MAX_TIPO 20
#define TAM_MOCHILA 10

typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

/* Nó da lista encadeada */
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

/* =========================
   CONTADORES GLOBAIS
   ========================= */

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

/* =========================
   PROTÓTIPOS - VETOR
   ========================= */

void inserirItemVetor(Item mochila[], int* qtd);
void removerItemVetor(Item mochila[], int* qtd);
void listarVetor(Item mochila[], int qtd);
void buscarSequencialVetor(Item mochila[], int qtd);
void ordenarVetor(Item mochila[], int qtd);
int  buscarBinariaVetor(Item mochila[], int qtd, char nome[]);

/* =========================
   PROTÓTIPOS - LISTA
   ========================= */

void inserirItemLista(No** inicio);
void removerItemLista(No** inicio);   // será explicada no PASSO 2
void listarLista(No* inicio);
void buscarLista(No* inicio);

/* =========================
   MENUS
   ========================= */

void menuVetor(Item mochila[], int* qtd);
void menuLista(No** inicio);

/* =========================
   MAIN
   ========================= */

int main() {
    Item mochilaVetor[TAM_MOCHILA];
    int qtdVetor = 0;

    No* mochilaLista = NULL;

    int opcao;

    do {
        printf("\n=== MOCHILA DE SOBREVIVENCIA ===\n");
        printf("1 - Mochila com Vetor\n");
        printf("2 - Mochila com Lista Encadeada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                menuVetor(mochilaVetor, &qtdVetor);
                break;
            case 2:
                menuLista(&mochilaLista);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

/* =========================
   MENU VETOR
   ========================= */

void menuVetor(Item mochila[], int* qtd) {
    int opcao;

    do {
        printf("\n--- MOCHILA (VETOR) ---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar (Sequencial)\n");
        printf("5 - Ordenar por nome\n");
        printf("6 - Buscar (Binaria)\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: inserirItemVetor(mochila, qtd); break;
            case 2: removerItemVetor(mochila, qtd); break;
            case 3: listarVetor(mochila, *qtd); break;
            case 4: buscarSequencialVetor(mochila, *qtd); break;
            case 5: ordenarVetor(mochila, *qtd); break;
            case 6: {
                char nome[MAX_NOME];
                printf("Nome do item: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                int pos = buscarBinariaVetor(mochila, *qtd, nome);
                if (pos != -1) {
                    printf("Item encontrado!\n");
                    printf("Comparacoes: %d\n", comparacoesBinaria);
                } else {
                    printf("Item nao encontrado.\n");
                    printf("Comparacoes: %d\n", comparacoesBinaria);
                }
                break;
            }
        }
    } while (opcao != 0);
}

/* =========================
   MENU LISTA
   ========================= */

void menuLista(No** inicio) {
    int opcao;

    do {
        printf("\n--- MOCHILA (LISTA) ---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar (Sequencial)\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: inserirItemLista(inicio); break;
            case 2: removerItemLista(inicio); break; // explicado no PASSO 2
            case 3: listarLista(*inicio); break;
            case 4: buscarLista(*inicio); break;
        }
    } while (opcao != 0);
}

/* =========================
   FUNÇÕES - VETOR
   ========================= */

void inserirItemVetor(Item mochila[], int* qtd) {
    if (*qtd >= TAM_MOCHILA) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;

    printf("Nome: ");
    fgets(novo.nome, MAX_NOME, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo.tipo, MAX_TIPO, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*qtd] = novo;
    (*qtd)++;
}

void removerItemVetor(Item mochila[], int* qtd) {
    char nome[MAX_NOME];

    printf("Nome do item: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *qtd - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*qtd)--;
            printf("Item removido.\n");
            return;
        }
    }

    printf("Item nao encontrado.\n");
}

void listarVetor(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        printf("\nNome: %s", mochila[i].nome);
        printf("\nTipo: %s", mochila[i].tipo);
        printf("\nQuantidade: %d\n", mochila[i].quantidade);
    }
}

void buscarSequencialVetor(Item mochila[], int qtd) {
    char nome[MAX_NOME];
    comparacoesSequencial = 0;

    printf("Nome do item: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < qtd; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Encontrado!\n");
            printf("Comparacoes: %d\n", comparacoesSequencial);
            return;
        }
    }

    printf("Nao encontrado.\n");
    printf("Comparacoes: %d\n", comparacoesSequencial);
}

void ordenarVetor(Item mochila[], int qtd) {
    Item aux;

    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                aux = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = aux;
            }
        }
    }
}

int buscarBinariaVetor(Item mochila[], int qtd, char nome[]) {
    int inicio = 0, fim = qtd - 1;
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(mochila[meio].nome, nome);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

/* =========================
   FUNÇÕES - LISTA
   ========================= */

void inserirItemLista(No** inicio) {
    No* novo = malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memória\n");
        return;
    }

    printf("Nome: ");
    fgets(novo->dados.nome, MAX_NOME, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo->dados.tipo, MAX_TIPO, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = *inicio;
    *inicio = novo;
}

void listarLista(No* inicio) {
    if (!inicio) {
        printf("Lista vazia.\n");
        return;
    }

    while (inicio) {
        printf("\nNome: %s", inicio->dados.nome);
        printf("\nTipo: %s", inicio->dados.tipo);
        printf("\nQuantidade: %d\n", inicio->dados.quantidade);
        inicio = inicio->proximo;
    }
}

void buscarLista(No* inicio) {
    char nome[MAX_NOME];
    int comparacoes = 0;

    printf("Nome do item: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    while (inicio) {
        comparacoes++;
        if (strcmp(inicio->dados.nome, nome) == 0) {
            printf("Encontrado!\n");
            printf("Comparacoes: %d\n", comparacoes);
            return;
        }
        inicio = inicio->proximo;
    }

    printf("Nao encontrado.\n");
    printf("Comparacoes: %d\n", comparacoes);
}

/* =========================
   REMOÇÃO NA LISTA
   ========================= */

void removerItemLista(No** inicio) {
    char nome[MAX_NOME];
    No* atual = *inicio;
    No* anterior = NULL;

    printf("Nome do item: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    while (atual) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                *inicio = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("Item removido.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item não encontrado.\n");
}