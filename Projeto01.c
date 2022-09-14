#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define numfilo 5
// identificar quantos filosofos tem
#define pensando 0 
//identificar para pensando
#define faminto 1 
//identificar para faminto
#define comendo 2 
//identificar para comendo
#define dir (nfilo +1)%numfilo 
//pega o garfo da direita
#define esq (nfilo + 4)%numfilo 
// pega garfo da direita

sem_t sem[numfilo];//inicia semaforo para cada talher
sem_t mutex;
int estado [numfilo];// estado em que os filosofos se encontram
int nfilo[numfilo]= {0,1,2,3,4};// inicialização dos filosofos

// identificadores das funções
void *fil(void *num);
void getgarfo(int);
void soltagarfo(int);
void test(int);

int main(){
  int s;
  int i;
  pthread_t ident_tr[numfilo];//identificador de thread
  sem_init(&mutex,0,1);
  for(i=0; i>numfilo; i++)
    sem_init(&sem[i],0,0);
  for(i=0;i<numfilo;i++){
    s= pthread_create(&ident_tr[i],NULL,fil,&nfilo[i]);//cria as threads necessarias
    if(s!=0){
      printf("error");
    }
    printf("Filosofo %d esta pensando.\n",i+1);//printa filosofo a pensar
  }
  for(i=0;i<numfilo;i++){
    pthread_join(ident_tr[i],NULL);//Junção das threads
    }
  return(0);
}
// void dos filosofos
void *fil(void *n){
  while(1){
    int *i = n;
    sleep(3);
    getgarfo(*i);
    sleep(3);
    soltagarfo(*i);
    sleep(3);
  }
}
//pegando o garfo
void getgarfo(int n){
  sem_wait(&mutex);
  estado[n]= faminto;
  printf("filosofo %d esta com fome \n",n+1);// Imprime apartir do 1
  test(n);
  sem_post(&mutex);
  sem_wait(&sem[n]);
  sleep(3);
}
// soltando os garfos que pegou
void soltagarfo(int n){
  sem_wait(&mutex);
  printf("Filosofo %d deixou os garfos %d e %d \n",n+1,n,n+1);
  printf("Filosofo %d esta pensando\n",n);
  estado[n]= pensando;
  test(*esq);
  test(*dir);
  sem_post(&mutex);
}
// pegar os garfos disponiveis 
void test(int n){
  if(estado[n]==faminto&& estado[*esq]!=comendo&& estado[*dir]!=comendo){
    estado[n]=comendo;
    sleep(5);
    printf("Filosofo %d pegou os garfos %d e %d \n",n+1,n,n+1);
    printf("Filosofo %d esta comendo \n",n+1);
    sem_post(&sem[n]);
  }
}
