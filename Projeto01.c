#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

//numero threads (cada conta)
#define NT 100
sem_t sem[NT];

int saldo[NT] = {100,100}; //saldo das contas 0 e 1
int nt[100]; //inicialização das transferencias (threads)

void *transacao(void *t){
  int *i = t; //numero da thread que entra na funçao
  while(1){
    sleep(1);
    sem_wait(&sem[*i]);
    int random = rand()%2; //identifica qual conta sera from ou to
    if(random==0){ //conta 0 from
      if(saldo[0]>=nt[*i]){
        printf("\nCONTA FROM (1)");
        printf("\nCONTA TO (2)");
        saldo[0]-=nt[*i];
        saldo[1]+=nt[*i];
        printf("\nVALOR DA TRANSFERENCIA: %d", nt[*i]);
        printf("\nSALDO DA CONTA FROM (1) APOS TRANSFERENCIA: %d", saldo[0]);
        printf("\nSALDO DA CONTA TO (2) APOS TRANSFERENCIA: %d", saldo[1]);
        printf("\n\n\n");
      }
    }
    else{ //conta 1 from
      if(saldo[1]>=nt[*i]){
        printf("\nCONTA FROM (2)");
        printf("\nCONTA TO (1)");
        saldo[1]-=nt[*i];
        saldo[0]+=nt[*i];
        printf("\nVALOR DA TRANSFERENCIA: %d", nt[*i]);
        printf("\nSALDO DA CONTA FROM (2) APOS TRANSFERENCIA: %d", saldo[0]);
        printf("\nSALDO DA CONTA TO (1) APOS TRANSFERENCIA: %d", saldo[1]);
        printf("\n\n\n");
      }
    }
    sleep(1);
    sem_post(&sem[*i]);
  }
  pthread_exit(0);
}

int main(){
  srand(time(NULL));
  for(int i=0; i<NT; i++){ //rodando os numeros que as trheads irao retirar
    nt[i] = rand()%20;
  }
  int i;
  pthread_t ident_tr[NT]; //indentificando a thread
  for(i=0; i<NT; i++){
    sem_init(&sem[i],0,1); //semaphore para cada thread
  }
  for(i=0;i<NT;i++){
    pthread_create(&ident_tr[i], NULL, transacao, &nt[i]); //cria as threads necessarias
    printf("Thread %d esta criada, seu valor: %d.\n",i+1, nt[i]); //criacao de conta
  }
  printf("\n\n");
  for(i=0;i<NT;i++){
    pthread_join(ident_tr[i],NULL); //Junção das threads
  }
}
