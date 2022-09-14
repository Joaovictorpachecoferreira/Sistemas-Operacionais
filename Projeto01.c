//OOOOOOOOOOOOOOOO//
//INCLUDES E IDENTIFICADORES PARA AS FUNÇÕES//
//OOOOOOOOOOOOOOOO//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define numfilo 5 
//identificar quantos filosofos tem
#define pensando 0 
//identificar para pensando
#define faminto 1 
//identificar para faminto
#define comendo 2 
//identificar para comendo
#define dir (nfilo+1)%numfilo 
// pega o garfo da direita
#define esq (nfilo+4)%numfilo
// pega garfo da direita

sem_t sem[numfilo];//inicia semaforo
sem_t mutex;
int estado [numfilo];// estado em que os filosofos se encontram
int nfilo[numfilo]= {0,1,2,3,4};// inicialização dos filosofos

// identificadores das funções
void fil(void *n);
void getgarfo(int);
void soltagarfo(int);
void test(int);


//OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO//
//FUNÇÃO PRINCIPAL//
//OOOOOOOOOOOOOOOO000000000000000000000000000000000000000000//
int main(){
  int i;
  pthread_t ident_tr[numfilo];//identificador de thread
  sem_init(&mutex,0,1);
  for(i=0; i<numfilo; i++)
    sem_init(&sem[i],0,0);
  for(i=0;i<numfilo;i++){
    pthread_create(&ident_tr[i],NULL,fil,&nfilo[i]);//cria as threads necessarias
    printf("Filosofo %d esta pensando.\n",i+1);//printa filosofo a pensar
  }
  for(i=0;i<numfilo;i++){
    pthread_join(ident_tr[i],NULL);//Junção das threads
  }
  return(0);
}


//OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO//
//FUNÇÃO FIL//
//OOOOOOOOOOOOOOOO000000000000000000000000000000000000000000//
void fil(void *n){
  while(1){
    int *i = n;
    sleep(1);
    getgarfo(*i);
    sleep(1);
    soltagarfo(*i);
  }
}


//OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO//
//FUNÇÃO GETGARFO//
//OOOOOOOOOOOOOOOO000000000000000000000000000000000000000000//
void getgarfo(int n){
  sem_wait(&mutex);
  estado[n]= faminto;
  printf("Filosofo %d esta com fome \n",n+1);// Imprime apartir do 1
  test(n);
  sem_post(&mutex);
  sem_wait(&sem[n]);
  sleep(1);
}


//OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO//
//FUNÇÃO SOLTAGARFO//
//OOOOOOOOOOOOOOOO000000000000000000000000000000000000000000//
void soltagarfo(int n){
  sem_wait(&mutex);
  estado[n]= pensando;
  printf("Filosofo %d deixou os garfos %d e %d \n",n+1,*esq+1,n+1);
  printf("Filosofo %d esta pensando\n",n+1);
  test(*esq);
  test(*dir);
  sem_post(&mutex);
}


//OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO//
//FUNÇÃO TESTAR//
//OOOOOOOOOOOOOOOO000000000000000000000000000000000000000000//
void test(int n){
  if(estado[n]==faminto&& estado[*esq]!=comendo&& estado[*dir]!=comendo){
    estado[n]=comendo;
    sleep(1);
    printf("Filosofo %d pegou os garfos %d e %d \n",n+1,*esq+1,n+1);
    printf("Filosofo %d esta comendo \n",n+1);
    sem_post(&sem[n]);
  }
}
