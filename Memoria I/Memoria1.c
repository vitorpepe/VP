#include <stdio.h>
#include <stdlib.h>

typedef struct reg celula;
struct reg {
    int conteudo;
    celula *prox;
};

void inserir(celula **inicio, int valor) {
    celula *nova = malloc(sizeof(celula));
    nova->conteudo = valor;
    nova->prox = *inicio;
    *inicio = nova;
}

void imprimir(celula *inicio) {
    celula *p = inicio;
    while (p != NULL) {
        printf("%d ", p->conteudo);
        p = p->prox;
    }
    printf("\n");
}

size_t tamanho_celula() {
    celula *p = malloc(sizeof(celula));
    celula *q = malloc(sizeof(celula));
    size_t tamanho = (char*)q - (char*)p;
    free(p);
    free(q);
    return tamanho;
}

void excluir_todos(celula **inicio) {
    celula *p = *inicio;
    while (p != NULL) {
        celula *q = p->prox;
        free(p);
        p = q;
    }
    *inicio = NULL;
}

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

size_t maximo_elementos() {
    size_t tamanho_cel = tamanho_celula();
    size_t tamanho_memoria = 1024 * 1024 * 1024; // 1 GB em bytes
    return tamanho_memoria / tamanho_cel;
}

int espaco_utilizado(celula *inicio) {
    int count = 0;
    celula *p = inicio;
    while (p != NULL) {
        count++;
        p = p->prox;
    }
    return count;
}

size_t capacidade_disponivel() {
    size_t max_elem = maximo_elementos();
    celula *p = malloc(sizeof(celula));
    size_t count = 0;
    while (count < max_elem && p != NULL) {
        p = p->prox;
        count++;
    }
    free(p);
    return max_elem - count;
}

int main() {
    celula *inicio = NULL;
    
    int opcao, valor;
    do {
        printf("\nMENU:\n");
        printf("1 - Inserir valor\n");
        printf("2 - Excluir todos os valores\n");
        printf("3 - Imprimir valores\n");
        printf("4 - Espaco utilizado na memoria\n");
        printf("5 - Remover valor\n");
        printf("6 - Capacidade disponivel\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                inserir(&inicio, valor);
                break;

            case 2:
                excluir_todos(&inicio);
                printf("Todos os valores foram excluidos.\n");
                break;
      
            case 3:
                imprimir(inicio);
                break;
    
            case 4:
                printf("O espaco utilizado na memoria e de %d bytes.\n", espaco_utilizado(inicio) * sizeof(celula));
                break;
    
            case 5:
                printf("Digite o valor que deseja remover: ");
                scanf("%d", &valor);
                remove_valor(&inicio, valor);
                break;
    
            case 6:
                printf("A capacidade disponivel e de %zu.\n", capacidade_disponivel());
                break;
    
            case 0:
                excluir_todos(&inicio);
                break;
    
            default:
                printf("Opcao invalida.\n");
    }
} while (opcao != 0);

return 0;
}
