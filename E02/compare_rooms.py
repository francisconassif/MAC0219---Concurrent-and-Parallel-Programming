"""
EP2 - MAC0219 - Programação Concorrente e Paralela      

Prof: Alfredo Goldman                   

Alunos:
 - Felipe Pereira Ramos Barboza
 - Francisco Nassif Membrive
 - Guilherme Luiz Pereira de Almeida

Data de entrega: 20/11/2024

Arquivo: compare_rooms.py

Código python chamado a cada teste
para comparar se as saídas em GPU 
e CPU foram equivalentes.

Usa como tolerância 1e-6.

Uso: python3 compare_rooms.py <room.txt> <room_cuda.txt>
"""

import numpy as np
import sys

def compare_rooms(file1, file2, tolerance=1e-6):
    data1 = np.loadtxt(file1)
    data2 = np.loadtxt(file2)

    # Primeiro, compara o tamanho dos arquivos gerados:
    if data1.shape != data2.shape:
        print("Os arquivos têm tamanhos diferentes e não podem ser comparados.")
        return

    diff = np.abs(data1 - data2)

    max_diff = np.max(diff)

    # Verifica a diferença máxima:
    if max_diff < tolerance:
        print(f"Os arquivos são equivalentes dentro da tolerância de {tolerance}.")
    else:
        print(f"Os arquivos diferem além da tolerância de {tolerance}.")

    return

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Uso: python3 compare_rooms.py <file1> <file2>")
        sys.exit(1)
    file1 = sys.argv[1]
    file2 = sys.argv[2]
    compare_rooms(file1, file2)
    sys.exit(0)
