#include <stdio.h>
#include <stdlib.h>

typedef struct reg celula;
struct reg {
    int conteudo;
    celula *prox;
};

void insere(celula **inicio, int valor) {
    celula *nova = malloc(sizeof(celula));
    nova->conteudo = valor;
    nova->prox = *inicio;
    *inicio = nova;
}

void imprime(celula *inicio) {
    celula *p = inicio;
    while (p != NULL) {
        printf("%d ", p->conteudo);
        p = p->prox;
    }
    printf("\n");
}

int tamanho_celula() {
    celula *p = malloc(sizeof(celula));
    celula *q = malloc(sizeof(celula));
    int tamanho = (int) (q - p);
    free(p);
    free(q);
    return tamanho;
}

void remove_todos(celula **inicio) {
    celula *p = *inicio;
    while (p != NULL) {
        celula *q = p->prox;
        free(p);
        p = q;
    }
    *inicio = NULL;
}

void remove_valor(celula **inicio, int valor) {
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
            return;
        }
        ant = p;
        p = p->prox;
    }
}

int maximo_elementos() {
    int tamanho_cel = tamanho_celula();
    int tamanho_memoria = 1024 * 1024 * 1024; // 1 GB em bytes
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

int capacidade_disponivel() {
    int max_elem = maximo_elementos();
    celula *p = malloc(sizeof(celula));
    int count = 0;
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
        printf("4 - Remover valor\n");
        printf("5 - Espaço utilizado na memória\n");
        printf("6 - Capacidade disponível\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                insere(&inicio, valor);
                printf("Valor inserido com sucesso!\n");
                break;
                
            case 2:
                remove_todos(&inicio);
                printf("Todos os valores foram excluidos!\n");
                break;
                
            case 3:
                imprime(inicio);
                break;
            case 4:
                printf("Espaco utilizado na memoria: %d bytes\n", maximo_elementos() * tamanho_celula());
                printf("Capacidade disponivel: %d\n", maximo_elementos() - espaco_utilizado(inicio));
                break;
        
            case 5:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                celula *p = inicio;
                celula *anterior = NULL;
                while (p != NULL) {
                  if (p->conteudo == valor) {
                    if (anterior == NULL) {
                        inicio = p->prox;
                    } else {
                        anterior->prox = p->prox;
                    }
                    free(p);
                    printf("Valor removido com sucesso!\n");
                    break;
                }
                anterior = p;
                p = p->prox;
            }
            if (p == NULL) {
                printf("Valor nao encontrado!\n");
            }
            break;
        
        case 6:
            printf("Capacidade disponivel: %d\n", capacidade_disponivel());
            break;
        
        case 0:
            printf("Saindo...\n");
            break;
        
        default:
            printf("Opcao invalida!\n");
            break;
    }
    
} while (opcao != 0);

// Remove todos os elementos restantes na lista
remove_todos(&inicio);

return 0;
}
