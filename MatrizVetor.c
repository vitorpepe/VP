/*
 Sistemas Operacionais
 Prof. Eduardo Ferreira
Multiplicação Matriz-Vetor
 Nome: Vitor Pepe
 TIA: 31852963
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *Pth_mat_vect(void *rank);

// Variáveis globais
int m, n, thread_count;
double **A, *x, *y;

int main() {
    long thread;
    pthread_t *thread_handles;  
    // Entrada dados da dimensão da matriz e do vetor
    printf("Digite a dimensão da matriz (m x n): ");
    scanf("%d %d", &m, &n);    
    // Aloca espaço para a matriz A
    A = (double**) malloc(m * sizeof(double*));
    for (int i = 0; i < m; i++) {
        A[i] = (double*) malloc(n * sizeof(double));
    } 
    // Recebe os valores da Matriz A
    printf("Digite os valores da Matriz A (%d x %d):\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }   
    // Aloca espaço para o vetor x e y
    x = (double*) malloc(n * sizeof(double));
    y = (double*) malloc(m * sizeof(double));    
    // Recebe os valores do vetor x
    printf("Digite os valores do Vetor X (%d x 1):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &x[i]);
    } 
    // Nnúmero de threads a serem utilizadas
    printf("Digite o número de threads: ");
    scanf("%d", &thread_count);
    // Alocando espaço para as threads
    thread_handles = (pthread_t*) malloc(thread_count * sizeof(pthread_t));  
    // Criando as threads
    for (thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void*) thread);
    } 
    // Espera as threads terminarem
    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }
    // Imprime o Vetor Resultante
    printf("O Vetor Resultante é:\n");
    for (int i = 0; i < m; i++) {
        printf("%lf\n", y[i]);
    }
    
    // Liberando memória
    for (int i = 0; i < m; i++) {
        free(A[i]);
    }
    free(A);
    free(x);
    free(y);
    free(thread_handles);
    
    return 0;
}


void *Pth_mat_vect(void *rank) {
    long my_rank = (long) rank;
    int i, j;
    int local_m = m / thread_count;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank + 1) * local_m - 1;
    
    for (i = my_first_row; i <= my_last_row; i++) {
        y[i] = 0.0;
        for (j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    
    return NULL;
}
