#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NOME 30
#define MAX_NOME_TIPO 20
#define ITEM_MOCHILA 10

typedef struct {
    int quantidade;
    char nome[MAX_NOME];
    char tipo[MAX_NOME_TIPO];
} Item;

//FUNÇÕES 
void cadastroDeItens(Item mochila[], int *qnt);
void remocaoDeItem(Item mochila[], int *qnt);
void listaDosItens(Item mochila[], int qnt);
void buscaItem(Item mochila[], int qnt);

//
int main() {
    Item mochila[ITEM_MOCHILA];
    int qntmochila = 0;
    int opcao;

    do {
       printf("=== MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA ===\n");
       printf("\nItem na Mochila: %d/10\n\n",qntmochila);
       printf("1 - Adicionar Item (Loot)\n");
       printf("2 - Remover Item\n");
       printf("3 - Listar Itens\n");
       printf("4 - Buscar Item\n");
       printf("0 - Sair\n");

       scanf("%d", &opcao);
       getchar();

       switch (opcao) {
       case 1: cadastroDeItens(mochila, &qntmochila); break;
       case 2: remocaoDeItem(mochila, &qntmochila); break;
       case 3: listaDosItens(mochila, qntmochila); break;
       case 4: buscaItem(mochila, qntmochila); break;
       case 0: printf("Saindo..."); break;
       default: printf("Opção inválida!"); break;
       }
    } while (opcao != 0);
    
return 0;
}

void cadastroDeItens(Item mochila[], int *qnt) {
    if (*qnt >= ITEM_MOCHILA) {
        printf("Mochila cheia");
        return;
    }

    Item novo;

    printf("Nome do item: ");
    fgets(novo.nome, MAX_NOME, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do item: ");
    fgets(novo.tipo, MAX_NOME_TIPO, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*qnt] = novo;
    (*qnt)++;

    printf("Item adicionado com sucesso!\n");
}

void listaDosItens(Item mochila[], int qnt) {
    if (qnt == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    for (int i = 0; i < qnt; i++) {
        printf("\nItem %d\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

void remocaoDeItem(Item mochila[], int *qnt) {
    char nomeBusca[MAX_NOME];

    printf("Digite o nome do item para remover: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < *qnt; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {

            for (int j = i; j < *qnt - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            (*qnt)--;
            printf("Item removido com sucesso!\n ");
            
        }
    }
}

void buscaItem(Item mochila[], int qnt) {
    char nomeBusca[MAX_NOME];

    printf("Digite o nome do item para buscar: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for(int i = 0; i < qnt; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("Item não encontrado.\n");
}
// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.


// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
