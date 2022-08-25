#include <stdio.h>
int numero;
int main(void)
{
  FILE *arquivo;
  char Linha[100];
  char *result;
  int i;
  // Abre um arquivo txt para leitura
  arquivo = fopen("dados.txt", "rt");
  if (arquivo == NULL)  // Se houve erro na abertura
  {
     printf("Problemas na abertura do arquivo\n");
     return 0 ;
  }
  printf("Digite 1 para printar o texto \n");
  printf("Digite 2 para fechar o arquivo \n");
  scanf("%d",&numero);
  if(numero== 1){
    
  i = 1;
  while (!feof(arquivo)) // Printando a leitura do arquvo
  {
    result = fgets(Linha,100, arquivo);
      if (result)  // Se foi possível ler
	      printf("L%d: %s",i,Linha);
        i++;
    } 
    return 1;
  }
  else if (numero==2){
    
  fclose(arquivo); // fechando o arquivo
    return 0 ; 
    }
  }
