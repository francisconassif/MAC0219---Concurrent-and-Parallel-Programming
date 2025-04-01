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
* Arquivo: heat_body.c
*
* Objetivo: adicionar um corpo quente ao programa heat.c
*
* Compilação: gcc -o heat_body heat_body.c -lm 
* Uso: ./heat_body <número de pontos> <limite de iterações>
*
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define WALL_TEMP 20.0
#define FIREPLACE_TEMP 100.0
#define BODY_TEMP 37.0

#define FIREPLACE_START 3
#define FIREPLACE_END 7
#define ROOM_SIZE 10

// Definição da posição e tamanho do corpo quente
#define BODY_START_X 4
#define BODY_END_X 6
#define BODY_START_Y 4
#define BODY_END_Y 6

/*
initialize: análogo a heat.c, mas com adição da
condição para colocar a temperatura do corpo
no local correto.
*/
void initialize(double **h, int n)
{
    int fireplace_start = (FIREPLACE_START * n) / ROOM_SIZE;
    int fireplace_end = (FIREPLACE_END * n) / ROOM_SIZE;

    // Cálculo das posições do corpo no grid
    int body_start_x = (BODY_START_X * n) / ROOM_SIZE;
    int body_end_x = (BODY_END_X * n) / ROOM_SIZE;
    int body_start_y = (BODY_START_Y * n) / ROOM_SIZE;
    int body_end_y = (BODY_END_Y * n) / ROOM_SIZE;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1)
            {
                h[i][j] = (i == n - 1 && j >= fireplace_start && j <= fireplace_end) ? FIREPLACE_TEMP : WALL_TEMP;
            }
            // Adição do corpo quente:
            else if (i >= body_start_y && i <= body_end_y && j >= body_start_x && j <= body_end_x)
            {
                h[i][j] = BODY_TEMP;
            }
            else
            {
                h[i][j] = 0.0;
            }
        }
    }
}


/*
Novamente, jacobi_iteration é análogo 
a heat.c, mas agora considera o corpo
e não varia a temperatura na região
correspondente.
*/
void jacobi_iteration(double **h, double **g, int n, int iter_limit)
{
    int body_start_x = (BODY_START_X * n) / ROOM_SIZE;
    int body_end_x = (BODY_END_X * n) / ROOM_SIZE;
    int body_start_y = (BODY_START_Y * n) / ROOM_SIZE;
    int body_end_y = (BODY_END_Y * n) / ROOM_SIZE;

    for (int iter = 0; iter < iter_limit; iter++)
    {
        for (int i = 1; i < n - 1; i++)
        {
            for (int j = 1; j < n - 1; j++)
            {
                // Não atualiza os pontos do corpo 
                if (i >= body_start_y && i <= body_end_y && j >= body_start_x && j <= body_end_x)
                {
                    g[i][j] = h[i][j]; 
                }
                else
                {
                    g[i][j] = 0.25 * (h[i - 1][j] + h[i + 1][j] + h[i][j - 1] + h[i][j + 1]);
                }
            }
        }
        for (int i = 1; i < n - 1; i++)
        {
            for (int j = 1; j < n - 1; j++)
            {
                h[i][j] = g[i][j];
            }
        }
    }
}

/*
Inalterada
*/
double calculate_elapsed_time(struct timespec start, struct timespec end)
{
    double start_sec = (double)start.tv_sec * 1e9 + (double)start.tv_nsec;
    double end_sec = (double)end.tv_sec * 1e9 + (double)end.tv_nsec;
    return (end_sec - start_sec) / 1e9;
}


/*
Inalterada, salvo pelo nome do arquivo.
*/
void save_to_file(double **h, int n)
{
    FILE *file = fopen("room_body.txt", "w");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(file, "%lf ", h[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}


/*
Inalterada
*/
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Uso: %s <número de pontos> <limite de iterações>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int iter_limit = atoi(argv[2]);

    double **h = (double **)malloc(n * sizeof(double *));
    double **g = (double **)malloc(n * sizeof(double *));
    if (h == NULL || g == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para h ou g\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++)
    {
        h[i] = (double *)malloc(n * sizeof(double));
        g[i] = (double *)malloc(n * sizeof(double));
        if (h[i] == NULL || g[i] == NULL)
        {
            fprintf(stderr, "Erro ao alocar memória para h[%d] ou g[%d]\n", i, i);
            exit(EXIT_FAILURE);
        }
    }

    struct timespec start, end;
    initialize(h, n);

    clock_gettime(CLOCK_MONOTONIC, &start);
    jacobi_iteration(h, g, n, iter_limit);
    clock_gettime(CLOCK_MONOTONIC, &end);
    save_to_file(h, n);

    double elapsed_time = calculate_elapsed_time(start, end);
    printf("Tempo de execução: %.9f segundos\n", elapsed_time);

    for (int i = 0; i < n; i++)
    {
        free(h[i]);
        free(g[i]);
    }
    free(h);
    free(g);

    return 0;
}
