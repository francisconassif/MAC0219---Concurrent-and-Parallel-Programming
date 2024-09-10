MiniEP4 - MAC0219 - Programação Concorrente e Paralela 
Aluno: Francisco Nassif Membrive
Professor: Alfredo Goldman

Descricao:  O objetivo deste miniep é mostrar um dos possiveis problemas
na concorrencia de threads. O problema selecionado foi o uso de uma fila
compartilhada por uma thread que produz os elementos e outra que consome.

No codigo problemqueue.c esse problema acontece. E no código safequeue.c
sao adicionados mutex e semaforos para impedir que a fila seja acessada
simultaneamente pelas duas funcoes.

Alem disso, foi mantido o makefile e o codigo compare.py que executa cada
programa 1000 vezes e registra a quantidade de erros.

Exemplo de execucao:

francisco@francisco:~/Paralela/MiniEP4$ gcc -pthread -o problemqueue problemqueue.c
francisco@francisco:~/Paralela/MiniEP4$ gcc -pthread -o safequeue safequeue.c
francisco@francisco:~/Paralela/MiniEP4$ python3 compare.py
Resultados do código original (com problema de concorrência):
Número de ocorrências de Fila cheia: 973
Número de ocorrências de Fila vazia: 30973

Resultados do código corrigido (com mutex):
Número de ocorrências de Fila cheia: 0
Número de ocorrências de Fila vazia: 0
