MiniEP6 - MAC0219 - Programação Concorrente e Paralela 
Aluno: Francisco Nassif Membrive
Professor: Alfredo Goldman

O objetivo deste MiniEP foi utilizar diferentes formas 
de multiplicação de matrizes e mostrar como a blocagem
e a otimização do uso da memória cache podem resultar 
em ganhos de desempenho. O programa que fazia os testes
foi executado 10 vezes e as saídas estão ao fim do arquivo.

Resultados: 
- matrix_dgemm_0:
    Tempo médio: 157,30 segundos
    Desvio padrão: 4,69 segundos
- matrix_dgemm_1:
    Tempo médio: 4,44 segundos
    Desvio padrão: 0,25 segundos
- matrix_dgemm_2:
    Tempo médio: 3,35 segundos
    Desvio padrão: 0,07 segundos

matrix_dgemm_1 foi mais de 30 vezes mais rápida que
matrix_dgemm_0 e matrix_dgemm_2 foi mais de 40 vezes

Como mencionado no enunciado, matrix_dgemm_1 modificou
a ordem de acesso de i, j, k para i, k, j, evitando 
invalidação de cache. Além disso, foi incluida uma variavel
do tipo 'register' para diminuir a quantidade de acessos à
memória e deixar a multiplicação ainda mais rápida. 

Já para matrix_dgemm_2, incluimos a blocagem. Aqui, foram
feitos testes com diferentes tamanhos de blocos. O tamanho ideal do bloco
depende do tamanho do cache. Fiz testes com os tamanhos 16, 32, 64 e 96.

Com 64 o tempo ficou quase o mesmo do que sem usar blocagem, com 16 e 96 o
tempo ficou pior e com 32 foi observada uma redução significativa.

O processador utilizado foi um Ryzen 5 3600, com 6 núcleos. 

Saída do lscpu com os tamanhos de cache:
Caches (sum of all):
  L1d:                   192 KiB (6 instances)
  L1i:                   192 KiB (6 instances)
  L2:                    3 MiB (6 instances)
  L3:                    16 MiB (1 instance)


Saída dos testes:

gcc -Wall -pedantic -g -O2   -c -o test.o test.c
gcc  -Wall -pedantic -g -O2 -o test test.o matrix.o time_extra.o
./test
Executando dgemm_0...
    Tempo gasto em matrix_dgemm_0: 156.137383s
    Resultado OK!
    Tempo OK!

Executando dgemm_1...
    Tempo gasto em matrix_dgemm_1: 4.358861s
    Resultado OK!
    Tempo OK!

Executando dgemm_2...
    Tempo gasto em matrix_dgemm_2: 3.372709s
    Resultado OK!
    Tempo OK!

gcc  -Wall -pedantic -g -O2 -o test test.o matrix.o time_extra.o
./test
Executando dgemm_0...
    Tempo gasto em matrix_dgemm_0: 159.834180s
    Resultado OK!
    Tempo OK!

Executando dgemm_1...
    Tempo gasto em matrix_dgemm_1: 4.321576s
    Resultado OK!
    Tempo OK!

Executando dgemm_2...
    Tempo gasto em matrix_dgemm_2: 3.278730s
    Resultado OK!
    Tempo OK!

gcc  -Wall -pedantic -g -O2 -o test test.o matrix.o time_extra.o
./test
Executando dgemm_0...
    Tempo gasto em matrix_dgemm_0: 155.462479s
    Resultado OK!
    Tempo OK!

Executando dgemm_1...
    Tempo gasto em matrix_dgemm_1: 4.333699s
    Resultado OK!
    Tempo OK!

Executando dgemm_2...
    Tempo gasto em matrix_dgemm_2: 3.385345s
    Resultado OK!
    Tempo OK!

gcc  -Wall -pedantic -g -O2 -o test test.o matrix.o time_extra.o
./test
Executando dgemm_0...
    Tempo gasto em matrix_dgemm_0: 159.426134s
    Resultado OK!
    Tempo OK!

Executando dgemm_1...
    Tempo gasto em matrix_dgemm_1: 4.377890s
    Resultado OK!
    Tempo OK!

Executando dgemm_2...
    Tempo gasto em matrix_dgemm_2: 3.312465s
    Resultado OK!
    Tempo OK!

gcc  -Wall -pedantic -g -O2 -o test test.o matrix.o time_extra.o
./test
Executando dgemm_0...
    Tempo gasto em matrix_dgemm_0: 161.825659s
    Resultado OK!
    Tempo OK!

Executando dgemm_1...
    Tempo gasto em matrix_dgemm_1: 4.341933s
    Resultado OK!
    Tempo OK!

Executando dgemm_2...
    Tempo gasto em matrix_dgemm_2: 3.308188s
    Resultado OK!
    Tempo OK!

gcc  -Wall -pedantic -g -O2 -o test test.o matrix.o time_extra.o
./test
Executando dgemm_0...
    Tempo gasto em matrix_dgemm_0: 159.281694s
    Resultado OK!
    Tempo OK!

Executando dgemm_1...
    Tempo gasto em matrix_dgemm_1: 4.371035s
    Resultado OK!
    Tempo OK!

Executando dgemm_2...
    Tempo gasto em matrix_dgemm_2: 3.370744s
    Resultado OK!
    Tempo OK!

gcc  -Wall -pedantic -g -O2 -o test test.o matrix.o time_extra.o
./test
Executando dgemm_0...
    Tempo gasto em matrix_dgemm_0: 158.436667s
    Resultado OK!
    Tempo OK!

Executando dgemm_1...
    Tempo gasto em matrix_dgemm_1: 4.410777s
    Resultado OK!
    Tempo OK!

Executando dgemm_2...
    Tempo gasto em matrix_dgemm_2: 3.300551s
    Resultado OK!
    Tempo OK!

gcc  -Wall -pedantic -g -O2 -o test test.o matrix.o time_extra.o
./test
Executando dgemm_0...
    Tempo gasto em matrix_dgemm_0: 160.114912s
    Resultado OK!
    Tempo OK!

Executando dgemm_1...
    Tempo gasto em matrix_dgemm_1: 4.356062s
    Resultado OK!
    Tempo OK!

Executando dgemm_2...
    Tempo gasto em matrix_dgemm_2: 3.291122s
    Resultado OK!
    Tempo OK!

gcc  -Wall -pedantic -g -O2 -o test test.o matrix.o time_extra.o
./test
Executando dgemm_0...
    Tempo gasto em matrix_dgemm_0: 157.395245s
    Resultado OK!
    Tempo OK!

Executando dgemm_1...
    Tempo gasto em matrix_dgemm_1: 4.411247s
    Resultado OK!
    Tempo OK!

Executando dgemm_2...
    Tempo gasto em matrix_dgemm_2: 3.410039s
    Resultado OK!
    Tempo OK!

gcc  -Wall -pedantic -g -O2 -c matrix.c
gcc  -Wall -pedantic -g -O2 -o test test.o matrix.o time_extra.o
./test
Executando dgemm_0...
    Tempo gasto em matrix_dgemm_0: 145.063893s
    Resultado OK!
    Tempo OK!

Executando dgemm_1...
    Tempo gasto em matrix_dgemm_1: 5.137057s
    Resultado OK!
    Tempo OK!

Executando dgemm_2...
    Tempo gasto em matrix_dgemm_2: 3.492239s
    Resultado OK!
    Tempo OK!

