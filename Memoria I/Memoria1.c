#include <stdio.h>
#include <stdlib.h>

typedef struct reg celula;
struct reg {
    int conteudo;
    celula *prox;
};
// Função que insere um valor novo no início da lista encadeada
void inserir(celula **inicio, int valor) {
    celula *nova = malloc(sizeof(celula));
    nova->conteudo = valor;
    nova->prox = *inicio;
    *inicio = nova;
}
// Função que imprime os valores da lista
void imprimir(celula *inicio) {
    celula *p = inicio;
    while (p != NULL) {
        printf("%d ", p->conteudo);
        p = p->prox;
    }
    printf("\n");
}
// Função que retorna o tamanho de uma célula em bytes
size_t tamanho_celula() {
    celula *p = malloc(sizeof(celula));
    celula *q = malloc(sizeof(celula));
    size_t tamanho = (char*)q - (char*)p;
    free(p);
    free(q);
    return tamanho;
}
// Função que remove todos os valores da lista encadeada
void excluir_todos(celula **inicio) {
    celula *p = *inicio;
    while (p != NULL) {
        celula *q = p->prox;
        free(p);
        p = q;
    }
    *inicio = NULL;
}
// Função que remove um valor específico da lista
int remove_valor(celula **inicio, int valor) {
    celula *p = *inicio;
    celula *ant = NULL;
    while (p != NULL) {
        if (p->conteudo == valor) {
            if (ant == NULL) {
                *inicio = p->prox;
            } else {
                ant->prox = p->prox;
            }
            free(p);
            return 1;
        }
        ant = p;
        p = p->prox;
    }
    return 0;
}
// Função que calcula o espaço utilizado pela lista
int espaco_utilizado(celula *inicio) {
    int count = 0;
    celula *p = inicio;
    while (p != NULL) {
        count++;
        p = p->prox;
    }
    return count;
}

int main() {
    celula *inicio = NULL;
  
// Declaração das variáveis que serão utilizadas no menu  
    int opcao, valor;
    do {
        printf("\nMENU:\n");
        printf("1 - Inserir valor\n");
        printf("2 - Imprimir valores\n");
        printf("3 - Remover valor\n");
        printf("4 - Remover todos os valores\n");
        printf("5 - Espaço utilizado na memoria\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
      
// Execução sa opção escolhida pelo usuário       
        switch (opcao) {
            case 1:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                inserir(&inicio, valor);
                break;

            case 2:
                imprimir(inicio);
                break;
      
            case 3:
                printf("Digite o valor que deseja remover: ");
                scanf("%d", &valor);
                remove_valor(&inicio, valor);
                break;
    
            case 4:
                excluir_todos(&inicio);
                printf("Todos os valores foram excluidos.\n");
                break;
    
            case 5:
                printf("O espaco utilizado na memoria é de %d bytes.\n", espaco_utilizado(inicio) * sizeof(celula));
                break;
          
            case 0:
                excluir_todos(&inicio);
                break;
    
            default:
                printf("Opcão inválida.\n");
    }
} while (opcao != 0);

return 0;
}
