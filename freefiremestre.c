#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
} Criterio;

int insertionSort(Item *m, int n, Criterio c) {
    int comparacoes = 0;

    for(int i = 1; i < n; i++) {
        Item chave = m[i];
        int j = i - 1;

        while(j >= 0) {
            comparacoes++;
            bool troca = false;

            if(c == ORDENAR_NOME)
                troca = strcmp(m[j].nome, chave.nome) > 0;
            else if(c == ORDENAR_TIPO)
                troca = strcmp(m[j].tipo, chave.tipo) > 0;
            else if(c == ORDENAR_PRIORIDADE)
                troca = m[j].prioridade > chave.prioridade;

            if(!troca) break;

            m[j+1] = m[j];
            j--;
        }
        m[j+1] = chave;
    }

    return comparacoes;
}

int buscaBinaria(Item *m, int n, const char *nomeBuscado) {
    int ini = 0, fim = n - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(nomeBuscado, m[meio].nome);

        if (cmp == 0) return meio;
        else if (cmp < 0) fim = meio - 1;
        else ini = meio + 1;
    }

    return -1;
}


int main() {
    Item mochila[MAX];
    int count = 0;
    Criterio ultimaOrdenacao = 0;

    int opcao;

    do {
        printf("\n=== MOCHILA MESTRE ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Listar itens\n");
        printf("3 - Ordenar itens\n");
        printf("4 - Buscar item (binaria)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {

        case 1: // Adicionar
            if(count >= MAX) { printf("Mochila cheia!\n"); break; }

            printf("Nome: ");
            fgets(mochila[count].nome, 30, stdin);
            mochila[count].nome[strcspn(mochila[count].nome, "\n")] = '\0';

            printf("Tipo: ");
            fgets(mochila[count].tipo, 20, stdin);
            mochila[count].tipo[strcspn(mochila[count].tipo, "\n")] = '\0';

            printf("Quantidade: ");
            scanf("%d", &mochila[count].quantidade);

            printf("Prioridade (1-5): ");
            scanf("%d", &mochila[count].prioridade);
            getchar();

            count++;
            ultimaOrdenacao = 0; // perdeu ordenação
            break;

        case 2: // Listar
            if(count == 0) printf("Mochila vazia.\n");
            else {
                printf("\n--- Itens ---\n");
                for(int i = 0; i < count; i++) {
                    printf("%d) %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
                           i+1,
                           mochila[i].nome,
                           mochila[i].tipo,
                           mochila[i].quantidade,
                           mochila[i].prioridade);
                }
            }
            break;

        case 3: { // Ordenar
            printf("Ordenar por:\n1 - Nome\n2 - Tipo\n3 - Prioridade\nEscolha: ");
            int criterio;
            scanf("%d", &criterio);

            int comp = insertionSort(mochila, count, criterio);

            ultimaOrdenacao = criterio;
            printf("Ordenado! Comparações: %d\n", comp);
            break;
        }

        case 4: { // Busca binária
            if(ultimaOrdenacao != ORDENAR_NOME) {
                printf("A lista precisa estar ordenada por NOME!\n");
                break;
            }

            char nomeBuscado[30];
            printf("Nome do item: ");
            fgets(nomeBuscado, 30, stdin);
            nomeBuscado[strcspn(nomeBuscado, "\n")] = '\0';

            int pos = buscaBinaria(mochila, count, nomeBuscado);

            if(pos == -1) printf("Item nao encontrado.\n");
            else {
                printf("\nItem encontrado:\n");
                printf("Nome: %s\nTipo: %s\nQtd: %d\nPrioridade: %d\n",
                       mochila[pos].nome,
                       mochila[pos].tipo,
                       mochila[pos].quantidade,
                       mochila[pos].prioridade);
            }
            break;
        }

        }

    } while(opcao != 0);

    return 0;
}
