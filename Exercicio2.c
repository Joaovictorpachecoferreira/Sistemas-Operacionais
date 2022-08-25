#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int numero;
char str[20];
char str3[20];
const char* str2 = ".txt";
int erro;

void copiartexto(FILE *arq1,FILE *arq2){
  char leitor [1000];//le os caracteres do arquivo
  while(fgets(leitor,1000,arq1)!=NULL){//copia os dados do arquivo até ir no NULL
    fputs(leitor,arq2);// joga para o arquivo 2 os dados copiados do arquivo 1
  }
}

int main (void){
  do{
    printf("Digite 1 caso queira copiar o texto\n");
    printf("Digite 0 caso queira fechar o aplicativo\n");
    scanf("%d",&numero);

    if(numero==1){
      do{
        erro=0;
        printf("Qual arquivo de entrada?\n");
        scanf("%s", str);
        strcat(strcpy(str, str), str2);
        void copiartexto(FILE *arq1,FILE *arq2);            
        FILE *arq1=fopen(str,"r");
        if (arq1 == NULL){ // Se houve erro na abertura
          printf("Problemas na abertura do arquivo\n");
          erro=1;
        }
        if(erro==0){
          printf("Qual arquivo de saida?\n");
          scanf("%s", str3);
          strcat(strcpy(str3, str3), str2);
          FILE *arq2=fopen(str3,"w");
          copiartexto(arq1,arq2);//copia dos arquivos 
          fclose(arq1);//fecha arquivo 1
          fclose(arq2);//fecha arquivo 2 
          printf("texto copiado com sucesso!\n");
        }
      }while(erro==1);
    }
  }while(numero==1);
  return 0;
}
