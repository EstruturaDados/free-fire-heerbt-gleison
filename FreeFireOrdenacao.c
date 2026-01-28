#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_COMP 20
#define MAX_NOME 30
#define MAX_TIPO 20

// Flag de controle: indica se o vetor está ordenado por nome
int ordenadoPorNome = 0;

// Estrutura que representa um componente da torre
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int prioridade;
} Componente;

// === Protótipos das funções ===
void bubbleSortNome(Componente v[], int n, int *comparacoes);
void insertionSortTipo(Componente v[], int n, int *comparacoes);
void selectionSortPrioridade(Componente v[], int n, int *comparacoes);
void mostrarComponentes(Componente v[], int n);
int buscaBinariaPorNome(Componente v[], int n, char chave[], int *comparacoes);

int main(void) {
    Componente componentes[MAX_COMP];
    int quantidade;

    printf("Quantos componentes deseja cadastrar (max %d)? ", MAX_COMP);
    scanf("%d", &quantidade);
    getchar();

    if (quantidade > MAX_COMP) {
        quantidade = MAX_COMP;
    }

    // Cadastro dos componentes
    for (int i = 0; i < quantidade; i++) {
        printf("\nComponente %d\n", i + 1);

        printf("Nome: ");
        fgets(componentes[i].nome, MAX_NOME, stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(componentes[i].tipo, MAX_TIPO, stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        scanf("%d", &componentes[i].prioridade);
        getchar();
    }

    int opcao;
    do {
        printf("\n=== MENU DE ORDENAÇÃO DE COMPONENTES ===\n");
        printf("1 - Ordenação por nome (Bubble Sort)\n");
        printf("2 - Ordenação por tipo (Insertion Sort)\n");
        printf("3 - Ordenação por prioridade (Selection Sort)\n");
        printf("4 - Busca binária por nome\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
        case 1: {
            int comparacoes;
            clock_t inicio = clock();

            bubbleSortNome(componentes, quantidade, &comparacoes);

            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

            printf("Comparações: %d\n", comparacoes);
            printf("Tempo: %.6f segundos\n", tempo);
            mostrarComponentes(componentes, quantidade);
            break;
        }

        case 2: {
            int comparacoes;
            clock_t inicio = clock();

            insertionSortTipo(componentes, quantidade, &comparacoes);

            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

            printf("Comparações: %d\n", comparacoes);
            printf("Tempo: %.6f segundos\n", tempo);
            mostrarComponentes(componentes, quantidade);
            break;
        }

        case 3: {
            int comparacoes;
            clock_t inicio = clock();

            selectionSortPrioridade(componentes, quantidade, &comparacoes);

            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

            printf("Comparações: %d\n", comparacoes);
            printf("Tempo: %.6f segundos\n", tempo);
            mostrarComponentes(componentes, quantidade);
            break;
        }

        case 4:
            if (!ordenadoPorNome) {
                printf("\nERRO: a busca binária só pode ser feita após ordenação por nome.\n");
            } else {
                char chave[MAX_NOME];
                int comparacoes;

                printf("Digite o nome do componente: ");
                fgets(chave, MAX_NOME, stdin);
                chave[strcspn(chave, "\n")] = '\0';

                clock_t inicio = clock();
                int pos = buscaBinariaPorNome(componentes, quantidade, chave, &comparacoes);
                clock_t fim = clock();

                double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

                if (pos != -1) {
                    printf("\nComponente encontrado!\n");
                    printf("Nome: %s\n", componentes[pos].nome);
                    printf("Tipo: %s\n", componentes[pos].tipo);
                    printf("Prioridade: %d\n", componentes[pos].prioridade);
                } else {
                    printf("\nComponente NÃO encontrado.\n");
                }

                printf("Comparações: %d\n", comparacoes);
                printf("Tempo: %.6f segundos\n", tempo);
            }
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}

// === Implementações ===

// Bubble Sort por nome
void bubbleSortNome(Componente v[], int n, int *comparacoes) {
    *comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            (*comparacoes)++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
    ordenadoPorNome = 1;
}

// Insertion Sort por tipo
void insertionSortTipo(Componente v[], int n, int *comparacoes) {
    *comparacoes = 0;

    for (int i = 1; i < n; i++) {
        Componente temp = v[i];
        int j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, temp.tipo) > 0) {
            (*comparacoes)++;
            v[j + 1] = v[j];
            j--;
        }

        if (j >= 0) (*comparacoes)++;
        v[j + 1] = temp;
    }
    ordenadoPorNome = 0;
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente v[], int n, int *comparacoes) {
    *comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j].prioridade < v[menor].prioridade) {
                menor = j;
            }
        }

        if (menor != i) {
            Componente temp = v[i];
            v[i] = v[menor];
            v[menor] = temp;
        }
    }
    ordenadoPorNome = 0;
}

// Exibição dos componentes
void mostrarComponentes(Componente v[], int n) {
    printf("\n--- LISTA DE COMPONENTES ---\n");
    for (int i = 0; i < n; i++) {
        printf("Componente %d\n", i + 1);
        printf("Nome: %s\n", v[i].nome);
        printf("Tipo: %s\n", v[i].tipo);
        printf("Prioridade: %d\n\n", v[i].prioridade);
    }
}

// Busca binária por nome
int buscaBinariaPorNome(Componente v[], int n, char chave[], int *comparacoes) {
    int inicio = 0, fim = n - 1;
    *comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;

        int cmp = strcmp(v[meio].nome, chave);

        if (cmp == 0) return meio;
        else if (cmp > 0) fim = meio - 1;
        else inicio = meio + 1;
    }

    return -1;
}
