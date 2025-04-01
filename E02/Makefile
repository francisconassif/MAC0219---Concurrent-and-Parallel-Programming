###########################################################################################
# EP2 - MAC0219 - Programação Concorrente e Paralela                                    
# Prof: Alfredo Goldman                                                                  
# Alunos:
#  - Felipe Pereira Ramos Barboza
#  - Francisco Nassif Membrive
#  - Guilherme Luiz Pereira de Almeida
#
# Data de entrega: 20/11/2024
#
# Arquivo: Makefile
#
# Objetivo - compila os 4 arquivos:
# - heat.c
# - heat_body.c
# - heat_cuda.cu
# - heat_body_cuda.cu
#
###########################################################################################


# Executáveis:
TARGET_C = heat
TARGET_BODY_C = heat_body
TARGET_CUDA = heat_cuda
TARGET_BODY_CUDA = heat_body_cuda

# Compiladores
CC = gcc
NVCC = nvcc

# Flags:
CFLAGS = -Wall -Wextra -O2
NVCCFLAGS = -O2

# Objetos:
OBJ_C = heat.o
OBJ_BODY_C = heat_body.o
OBJ_CUDA = heat_cuda.o
OBJ_BODY_CUDA = heat_body_cuda.o

.PHONY: all clean

all: $(TARGET_C) $(TARGET_BODY_C) $(TARGET_CUDA) $(TARGET_BODY_CUDA)

$(TARGET_C): $(OBJ_C)
	$(CC) $(CFLAGS) -o $(TARGET_C) $(OBJ_C)

heat.o: heat.c
	$(CC) $(CFLAGS) -c heat.c

$(TARGET_BODY_C): $(OBJ_BODY_C)
	$(CC) $(CFLAGS) -o $(TARGET_BODY_C) $(OBJ_BODY_C)

heat_body.o: heat_body.c
	$(CC) $(CFLAGS) -c heat_body.c

$(TARGET_CUDA): $(OBJ_CUDA)
	$(NVCC) $(NVCCFLAGS) -o $(TARGET_CUDA) $(OBJ_CUDA)

heat_cuda.o: heat_cuda.cu
	$(NVCC) $(NVCCFLAGS) -c heat_cuda.cu

$(TARGET_BODY_CUDA): $(OBJ_BODY_CUDA)
	$(NVCC) $(NVCCFLAGS) -o $(TARGET_BODY_CUDA) $(OBJ_BODY_CUDA)

heat_body_cuda.o: heat_body_cuda.cu
	$(NVCC) $(NVCCFLAGS) -c heat_body_cuda.cu

clean:
	rm -f $(TARGET_C) $(TARGET_BODY_C) $(TARGET_CUDA) $(TARGET_BODY_CUDA) $(OBJ_C) $(OBJ_BODY_C) $(OBJ_CUDA) $(OBJ_BODY_CUDA)
