/*
 Sistemas Operacionais
 Prof. Eduardo Ferreira
 Projeto 1 - Jantar dos Filosofos
 Nome: Vitor Pepe
 TIA: 31852963
*/

#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

// variaveis do problema
#define N 5
#define PENSAR 0
#define FOME 1
#define COMER 2

// funcao para pegar garfo a direita
#define DIREITA (nfilosofo + 1)%N
// funcao para pegar garfo a esquerda
#define ESQUERDA (nfilosofo + 4)%N

void *filosofo(void *num);
void pegarGarfo(int);
void deixarGarfo(int);
void verifique(int);

// semáforo
sem_t mutex;

// iniciando do semáforo
sem_t S[N];

// seta o estado e filosofos
int estado[N];
int nfilosofo[N]={0, 1, 2, 3, 4};

// funcao dos filosofos
void *filosofo(void *num)
{
   while(1)
   {
      // alterna entre pegar/deixar garfos
      int *i = num;
      sleep(1);
      pegarGarfo(*i);
      sleep(1);
      deixarGarfo(*i);
   }
}

// funcao para pegar os garfos
void pegarGarfo(int nfilosofo)
{
   // trava o semáforo
   sem_wait(&mutex);
   // seta o estado do filosofo n para: com fome
   estado[nfilosofo] = FOME;
   printf("Filosofo %d esta com fome.\n", nfilosofo + 1);
   // verifica se algum filosofo ao lado esta comendo
   verifique(nfilosofo);
   // desbloqueia o semáforo
   sem_post(&mutex);
   // trava os outros filosofos
   sem_wait(&S[nfilosofo]);
   sleep(1);
}

// funcao para deixar os garfos
void deixarGarfo(int nfilosofo)
{
   // trava o semáforo
   sem_wait(&mutex);
   // seta o estado do filosofo n para: pensando
   estado[nfilosofo] = PENSAR;
   printf("Filosofo %d deixou os garfos %d e %d.\n", nfilosofo + 1, ESQUERDA + 1, nfilosofo + 1);
   printf("Filosofo %d esta pensando.\n", nfilosofo + 1);
   // testa se o filosofo a direita e a esquerda esta comendo
   verifique(ESQUERDA);
   verifique(DIREITA);
   // desbloqueia o semáforo
   sem_post(&mutex);
}

// verifica os estados dos filosofos ao lado
void verifique(int nfilosofo)
{
   if(estado[nfilosofo] == FOME && estado[ESQUERDA] != COMER && estado[DIREITA] != COMER)
   {
      // seta o estado do filosofo N para: com fome
      estado[nfilosofo] = COMER;
      sleep(2);
      printf("Filosofo %d pegou os garfos %d e %d.\n", nfilosofo + 1, ESQUERDA + 1, nfilosofo + 1);
      printf("Filosofo %d esta comendo.\n", nfilosofo + 1);
      // desbloqueia os filosofos
      sem_post(&S[nfilosofo]);
   }
}

// funcao principal
int main() {
   int i;
   // identificadores das threads
   pthread_t thread_id[N];
   // inicializa o semaforo sincronizado e compartilhado entre threads
   sem_init(&mutex, 0, 1);
   for(i = 0; i < N; i++)
      sem_init(&S[i], 0, 0); // inicializa o semaforo S sincronizado e compartilhado entre threads
   for(i = 0; i < N; i++)
   {
      // criacao das threads
      pthread_create(&thread_id[i], NULL, filosofo, &nfilosofo[i]);
      printf("Filosofo %d esta pensando.\n", i + 1);
   }
   // juncao das threads
   for(i = 0; i < N; i++)
   pthread_join(thread_id[i], NULL);

   return(0);
}
