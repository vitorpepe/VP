/*
 Sistemas Operacionais
 Prof. Eduardo Ferreira
Calculo de Pi - Com Mutex
 Nome: Vitor Pepe
 TIA: 31852963
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long thread_count;
long long n;
double *sum;
pthread_mutex_t mutex;

void* Thread_sum(void* rank) {
  long my_rank = (long) rank;
  double factor;
  long long i;
  long long my_n = n/thread_count;
  long long my_first_i = my_n * my_rank;
  long long my_last_i =  my_first_i + my_n;

  if (my_first_i % 2 == 0) /* my-first is even */
    factor = 1.0; 
  else /* my_first_i is odd" */
    factor = -1.0;

  for (i = my_first_i ; i < my_last_i ; i++ , factor = -factor) {
    pthread_mutex_lock(&mutex);
    sum[my_rank] += factor /(2 * i+1);
    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}

int main(int argc, char* argv[]) {
  long thread;
  pthread_t* thread_handles;

  printf("Digite o numero de threads utilizadas no cálculo:\n");
  scanf("%ld", &thread_count);

  n = 1000000; /* Valor padrão de N */
  printf("Calculando Pi utilizando %lld iteraçoes\n", n);
  
// aloca memória para os vetores
  thread_handles = malloc(thread_count*sizeof(pthread_t));
  sum = malloc(thread_count*sizeof(double));
  
// inicializa o mutex
  pthread_mutex_init(&mutex, NULL);
  for (thread = 0; thread < thread_count; thread++)
    sum[thread] = 0.0;
  
// cria as threads
  for (thread = 0; thread < thread_count; thread++)
    pthread_create(&thread_handles[thread], NULL, Thread_sum, (void*) thread);
  
// espera as threads terminarem
  for (thread = 0; thread < thread_count; thread++)
    pthread_join(thread_handles[thread], NULL);
  
// calcula o valor de pi a partir das somas parciais
  double pi = 0.0;
  for (thread = 0; thread < thread_count; thread++)
    pi += sum[thread];

  pi = 4.0*pi;
  
// imprime o valor de pi
  printf("pi = %.15f\n", pi);
  
// libera a memória alocada e destrói o mutex
  pthread_mutex_destroy(&mutex);
  free(thread_handles);
  free(sum);

  return 0;
}
