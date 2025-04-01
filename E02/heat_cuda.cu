/****************************************************************************************
* EP2 - MAC0219 - Programação Concorrente e Paralela                                    
* Prof: Alfredo Goldman                                                                  
* Alunos:
*  - Felipe Pereira Ramos Barboza
*  - Francisco Nassif Membrive
*  - Guilherme Luiz Pereira de Almeida
*
* Data de entrega: 20/11/2024
*
* Arquivo: heat_cuda.cu
*
* Objetivo: implementação paralela em CUDA 
* do programa heat.c dado. 
*
* Compilação: nvcc -o heat_cuda heat_cuda.cu
* Uso: ./heat_cuda <número de pontos> <limite de iterações> <block_size>
*
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cuda.h>

#define WALL_TEMP 20.0
#define FIREPLACE_TEMP 100.0

#define FIREPLACE_START 3
#define FIREPLACE_END 7
#define ROOM_SIZE 10

/*
Função para inicializar o grid. 

Aqui, modificamos a função de heat.c 
para utilizar um array unidimensional
e otimizar os acessos à memória.
*/
void initialize(double *h, int n)
{
    int fireplace_start = (FIREPLACE_START * n) / ROOM_SIZE;
    int fireplace_end = (FIREPLACE_END * n) / ROOM_SIZE;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1)
            {
                if (i == n - 1 && j >= fireplace_start && j <= fireplace_end)
                    h[i * n + j] = FIREPLACE_TEMP;
                else
                    h[i * n + j] = WALL_TEMP;
            }
            else
            {
                h[i * n + j] = 0.0;
            }
        }
    }
}




/*
Kernel CUDA para jacobi_iteration

Aqui adaptamos para usar o array
unidimensional de initialize.

O limite de iterações não é mais
um parâmetro da função, será 
verificado na execução da main
onde o loop ocorre.

idx converte os índices i e j
no índice unidimensional.
*/
__global__ void jacobi_iteration_kernel(double *h, double *g, int n)
{
    int i = blockIdx.y * blockDim.y + threadIdx.y;
    int j = blockIdx.x * blockDim.x + threadIdx.x;

    if (i >= n || j >= n) return;

    int idx = i * n + j;

    if (i == 0 || i == n - 1 || j == 0 || j == n - 1)
    {
        g[idx] = h[idx];
    }
    else
    {
        g[idx] = 0.25 * (h[(i - 1) * n + j] + h[(i + 1) * n + j] + h[i * n + (j - 1)] + h[i * n + (j + 1)]);
    }
}

/*
Salva o grid no arquivo txt a ser lido por 
show_room.py. 
*/
void cria_file(double *h, int n)
{
    FILE *file = fopen("room_cuda.txt", "w");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(file, "%lf ", h[i * n + j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

/*
main:

Recebe pela linha de comando os argumentos n, iter_limit e block_size.
O número de threads por bloco é block_size^2. E o número de blocos por
grid é (ceil(n/block_size))^2.

Em todos os testes, iter_limit foi fixado em 1000.

Os valores de n foram 512, 1024, 2048, 4096, 8192. 
Os valores de block_size foram 8 e 16.
*/

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        fprintf(stderr, "Uso: %s <número de pontos> <limite de iterações> <block_size>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int iter_limit = atoi(argv[2]);
    int block_size = atoi(argv[3]);

    if (n <= 0 || iter_limit <= 0 || block_size <= 0)
    {
        fprintf(stderr, "Erro: Todos os parâmetros de entrada devem ser inteiros positivos.\n");
        return 1;
    }

    dim3 blockSize(block_size, block_size);
    dim3 gridSize((n + block_size - 1) / block_size, (n + block_size - 1) / block_size);

    size_t size = n * n * sizeof(double);

    // Aloca memória no host
    double *h_host = (double *)malloc(size);
    if (h_host == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória no host.\n");
        exit(EXIT_FAILURE);
    }

    initialize(h_host, n);

    // Aloca memória no device
    double *h, *g;
    cudaMalloc((void **)&h, size);
    cudaMalloc((void **)&g, size);

    // Copia o grid inicial para o device
    cudaMemcpy(h, h_host, size, cudaMemcpyHostToDevice);

    // Cria eventos CUDA para medir o tempo
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // Registra o evento de início
    cudaEventRecord(start, 0);

    // Loop de iteração de Jacobi
    for (int iter = 0; iter < iter_limit; iter++)
    {
        // Lança o kernel
        jacobi_iteration_kernel<<<gridSize, blockSize>>>(h, g, n);

        // Sincroniza o dispositivo para garantir que o kernel terminou
        cudaDeviceSynchronize();

        // Troca os ponteiros
        double *temp = h;
        h = g;
        g = temp;
    }

    // Registra o evento de término
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);

    // Calcula o tempo de execução em milissegundos e imprime
    float elapsed_time_ms;
    cudaEventElapsedTime(&elapsed_time_ms, start, stop);

    printf("Tempo de execução na GPU: %.9f segundos\n", elapsed_time_ms / 1000.0);

    // Determina qual ponteiro contém o resultado final
    double *result;
    if (iter_limit % 2 == 0)
    {
        result = h;
    }
    else
    {
        result = g;
    }

    // Copia o resultado de volta para o host
    cudaMemcpy(h_host, result, size, cudaMemcpyDeviceToHost);

    // Salva o resultado no arquivo
    cria_file(h_host, n);

    // Libera a memória
    cudaFree(h);
    cudaFree(g);
    free(h_host);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    return 0;
}
