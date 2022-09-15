//************************************************************//
//INCLUDES E IDENTIFICADORES PARA AS FUNÇÕES//
//************************************************************//
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
void *fil(void *n);
void getgarfo(int);
void soltagarfo(int);
void test(int);


//************************************************************//
//FUNÇÃO FIL//
//************************************************************//
void *fil(void *n){
  while(1){
    int *i = n;
    sleep(1);
    getgarfo(*i);
    sleep(1);
    soltagarfo(*i);
  }
}


//************************************************************//
//FUNÇÃO GETGARFO//
//************************************************************//
void getgarfo(int nfilo){
  sem_wait(&mutex);
  estado[nfilo]= faminto;
  printf("Filosofo %d esta com fome \n\n",nfilo+1);// Imprime apartir do 1
  test(nfilo);
  sem_post(&mutex);
  sem_wait(&sem[nfilo]);
  sleep(1);
}


//************************************************************//
//FUNÇÃO SOLTAGARFO//
//************************************************************//
void soltagarfo(int nfilo){
  sem_wait(&mutex);
  estado[nfilo]= pensando;
  printf("Filosofo %d terminou de comer e deixou os garfos %d e %d \n",nfilo+1,esq+1,nfilo+1);
  printf("Filosofo %d agora esta pensando\n\n",nfilo+1);
  test(esq);
  test(dir);
  sem_post(&mutex);
}


//************************************************************//
//FUNÇÃO TESTAR//
//************************************************************//
void test(int nfilo){
  if(estado[nfilo]==faminto&& estado[esq]!=comendo&& estado[dir]!=comendo){
    estado[nfilo]=comendo;
    sleep(1);
    printf("Filosofo %d pegou os garfos %d e %d \n",nfilo+1,esq+1,nfilo+1);
    printf("Filosofo %d esta comendo \n\n\n",nfilo+1);
    sem_post(&sem[nfilo]);
  }
}


//************************************************************//
//FUNÇÃO PRINCIPAL//
//************************************************************//
int main(){
  int i;
  pthread_t ident_tr[numfilo];//identificador de thread
  sem_init(&mutex,0,1);
  for(i=0; i<numfilo; i++)
    sem_init(&sem[i],0,0);
  for(i=0;i<numfilo;i++){
    pthread_create(&ident_tr[i], NULL, fil, &nfilo[i]);//cria as threads necessarias
    printf("Filosofo %d esta pensando.\n",i+1);//printa filosofo a pensar
  }
  printf("\n\n");
  for(i=0;i<numfilo;i++){
    pthread_join(ident_tr[i],NULL);//Junção das threads
  }
  return(0);
}
