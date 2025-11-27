#include <stdio.h>
#include <string.h>

#define MAX 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

int main() {
    Item mochila[MAX];
    int count = 0; // quantidade atual de itens
    int opcao;

    do {
        printf("\n=== MOCHILA DA ILHA ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar \n

        switch(opcao) {

        case 1: // Adicionar
            if(count >= MAX) {
                printf("Mochila cheia!\n");
                break;
            }
            printf("Nome do item: ");
            fgets(mochila[count].nome, 30, stdin);
            mochila[count].nome[strcspn(mochila[count].nome, "\n")] = '\0';

            printf("Tipo do item: ");
            fgets(mochila[count].tipo, 20, stdin);
            mochila[count].tipo[strcspn(mochila[count].tipo, "\n")] = '\0';

            printf("Quantidade: ");
            scanf("%d", &mochila[count].quantidade);
            getchar();

            count++;
            printf("Item adicionado!\n");
            break;

        case 2: { // Remover item
            char nomeBuscado[30];
            int encontrado = -1;

            printf("Nome do item para remover: ");
            fgets(nomeBuscado, 30, stdin);
            nomeBuscado[strcspn(nomeBuscado, "\n")] = '\0';

            for(int i = 0; i < count; i++) {
                if(strcmp(mochila[i].nome, nomeBuscado) == 0) {
                    encontrado = i;
                    break;
                }
            }

            if(encontrado == -1) {
                printf("Item nao encontrado.\n");
            } else {
                for(int i = encontrado; i < count - 1; i++) {
                    mochila[i] = mochila[i+1];
                }
                count--;
                printf("Item removido!\n");
            }
            break;
        }

        case 3: // Listar
            if(count == 0) {
                printf("Mochila vazia.\n");
            } else {
                printf("\n--- Itens na Mochila ---\n");
                for(int i = 0; i < count; i++) {
                    printf("%d) %s | Tipo: %s | Qtd: %d\n",
                           i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
                }
            }
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}
