# Sistemas-Operacionais
## Projeto 02 
### Como rodar o progama 
1- baixe o arquivo.
2- dentro do terminal entre na pasta do arquivo e compile da seguinte forma ( gcc Projeto02.c -o teste -lpthread).
3- digite no terminal para rodar (./teste).
#### Como comprovar que os resultados propostos foram alcançados
Fizemos 100 threads para cada uma das transferencias (item 5).
Há uma variavel randomica que determina um valor entre 0 e 1 e que o mesmo determina se a conta estará recebendo ou enviando a transferencia (item 4).
Também temos uma condição (if) que verifica se a conta tem saldo, se a conta não tiver saldo, ela não conseguira realizar a transerencia (item 3).
Com o uso das threads as contas realizam transferencia simultaneas entre elas (item 1 e 2).
