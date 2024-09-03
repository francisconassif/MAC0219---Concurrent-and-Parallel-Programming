/*
 * =====================================================================================
 *
 *  MiniEP3 - MAC0219 - Programação Concorrente e Paralela
 * 
 *  Aluno: Francisco Nassif Membrive
 *  Professor: Alfredo Goldman
 *
 *  Descricao: O objetivo deste miniep é otimizar o código em mini_ep3.c, reduzindo seu 
 *  tempo de execução. O resultado está neste arquivo fast.c, que otimizou atravéś de 
 *  duas estratégias:
 *      - substituição do slowsort pelo quicksort
 *      - substituição do cálculo do número de fibonacci recursivo por matricial
 * 
 *  A main foi mantida inalterada para comparação direta do desempenho dos dois programas.
 *  Tempo de mini_ep3.c: 10.248 s
 *  Tempo de fast.c:      0.003 s
 * 
 *  Após as modificações, o gprof não foi mais capaz de mensurar tempos significativos da
 *  execução.
 *
 *  O Fibonacci matricial foi extraído da internet e o quicksort foi baseado nos slides
 *  de MAC0338 do professor Paulo Feofillof.
 * 
 *  Compilação: gcc -o fast fast.c
 *  Execução: ./fast
 *
 * =====================================================================================
 */


#include <stdio.h>
#include <stdlib.h>

void matrix_multiply(int A[2][2], int B[2][2], int result[2][2]) {
    result[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
    result[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
    result[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
    result[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
}

void matrix_power(int matrix[2][2], int n, int result[2][2]) {
    result[0][0] = 1;
    result[0][1] = 0;
    result[1][0] = 0;
    result[1][1] = 1;
    
    int base[2][2];
    base[0][0] = matrix[0][0];
    base[0][1] = matrix[0][1];
    base[1][0] = matrix[1][0];
    base[1][1] = matrix[1][1];
    
    int temp[2][2];
    
    while (n > 0) {
        if (n % 2 == 1) {
            matrix_multiply(result, base, temp);
            result[0][0] = temp[0][0];
            result[0][1] = temp[0][1];
            result[1][0] = temp[1][0];
            result[1][1] = temp[1][1];
        }
        matrix_multiply(base, base, temp);
        base[0][0] = temp[0][0];
        base[0][1] = temp[0][1];
        base[1][0] = temp[1][0];
        base[1][1] = temp[1][1];
        
        n /= 2;
    }
}

int fibonacci(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    }
    
    int T[2][2] = {{1, 1}, {1, 0}};
    int result[2][2];
    matrix_power(T, n - 1, result);
    
    return result[0][0];
}

int particiona(int arr[], int i, int j, int k){
    int temp = arr[j];
    arr[j] = arr[k];
    arr[k] = temp;
    int p1 = i;
    for(int p2 = i; p2 < j; p2++) {
        if(arr[p2] < arr[j]){
            temp = arr[p1];
            arr[p1] = arr[p2];
            arr[p2] = temp;
            p1++;
        }
    }
    temp = arr[p1];
    arr[p1] = arr[j];
    arr[j] = temp;
    return p1;
}

void quicksort(int arr[], int i, int j){
    if(i >= j) return;
    int k = i + rand() % (j - i + 1);
    int index = particiona(arr, i, j, k);
    quicksort(arr, i, index-1);
    quicksort(arr, index+1, j);
}

int main() {
    const int TAMANHO = 200; // Tamanho do vetor
    const int SEED = 42; // Semente para números aleatórios
    int vetor[TAMANHO];
    int soma = 0;

    // Inicializa o gerador de números aleatórios
    srand(SEED);

    // Preenche o vetor com números aleatórios entre 2^2 e (2^2 + 2^5) - 1
    for (int i = 0; i < TAMANHO; i++) {
        vetor[i] = (rand() % (1 << 5)) + (1 << 2);
    }

    // Ordena o vetor usando Slowsort
    quicksort(vetor, 0, TAMANHO - 1);

    // Calcula o Fibonacci para cada elemento e soma os pares
    for (int i = 0; i < TAMANHO; i++) {
        int fib = fibonacci(vetor[i]);
        if (fib % 2 == 0) {
            soma += fib;
        }
    }

    printf("Soma dos números de Fibonacci pares: %d\n", soma);

    return 0;
}
