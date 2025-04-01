"""
EP2 - MAC0219 - Programação Concorrente e Paralela      

Prof: Alfredo Goldman                   

Alunos:
 - Felipe Pereira Ramos Barboza
 - Francisco Nassif Membrive
 - Guilherme Luiz Pereira de Almeida

Data de entrega: 20/11/2024

Arquivo: run_tests.py

Programa em python que executa, para cada combinação
de parâmetros, 10 testes, tanto para heat quanto
para heat_cuda, certificando-se de que as saídas 
são iguais e registrando os tempos de execução em um
arquivo CSV.

Saída: test_results.csv
"""

import subprocess
import csv
import itertools
import time
import os

# Parâmetros:
n_values = [512, 1024, 2048, 4096, 8192]  
block_sizes = [(8, 8), (16, 16)]            # Tamanhos dos blocos bidimensionais de threads
iter_limit = 1000                    
runs_per_case = 10                   

heat_executable = "./heat"
heat_cuda_executable = "./heat_cuda"

c_output_file = "room.txt"
cuda_output_file = "room_cuda.txt"

compare_script = "compare_rooms.py"

csv_filename = "test_results.csv"

def run_command(command):
    """
    Função para registrar o tempo de execução de um comando.
    """
    start_time = time.perf_counter()
    try:
        subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
        end_time = time.perf_counter()
        elapsed = end_time - start_time
        return elapsed, True
    except subprocess.CalledProcessError as e:
        print(f"Erro ao executar {' '.join(command)}:")
        print(e.stderr.decode())
        return None, False

def compare_outputs(file1, file2):
    """
    Usa compare_rooms.py para verificar se as saídas 
    estão compatíveis.
    """
    try:
        subprocess.run(
            ["python3", compare_script, file1, file2],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            check=True
        )
        return True
    except subprocess.CalledProcessError as e:
        print(f"Comparação falhou entre {file1} e {file2}:")
        print(e.stdout)
        return False

def main():
    """
    Cria o csv, executa ambos os programas, compara 
    as saídas e registra no CSV os tempos, se as saídas
    estavam compatíveis, os parâmetros e o speedup.

    O CSV registra Block_Size_X e Block_Size_Y, embora
    tenham o mesmo valor, pois anteriormente o código 
    permitia valores diferentes. 
    """
    with open(csv_filename, mode='w', newline='') as csvfile:
        csv_writer = csv.writer(csvfile)
        csv_writer.writerow([
            "Run_ID",
            "n",
            "Iter_Limit",
            "Block_Size_X",
            "Block_Size_Y",
            "Time_C_Seconds",
            "Time_CUDA_Seconds",
            "Speedup",
            "Comparison_Passed"
        ])

        for n, block_size in itertools.product(n_values, block_sizes):
            block_size_x, block_size_y = block_size
            for run in range(1, runs_per_case + 1):
                run_id = f"{n}_{block_size_x}x{block_size_y}_run{run}"
                print(f"Rodando {run_id}...")

                # Remove arquivos de saída anteriores:
                for outfile in [c_output_file, cuda_output_file]:
                    if os.path.exists(outfile):
                        os.remove(outfile)

                # Executa o C:
                cmd_c = [heat_executable, str(n), str(iter_limit)]
                time_c, success_c = run_command(cmd_c)
                if not success_c:
                    print(f"Erro na execução de {heat_executable} para {run_id}")
                    time_c = -1

                # Executa o CUDA:
                cmd_cuda = [heat_cuda_executable, str(n), str(iter_limit), str(block_size_x)]
                time_cuda, success_cuda = run_command(cmd_cuda)
                if not success_cuda:
                    print(f"Erro na execução de {heat_cuda_executable} para {run_id}")
                    time_cuda = -1

                # Compara as saídas:
                if os.path.exists(c_output_file) and os.path.exists(cuda_output_file):
                    comparison_passed = compare_outputs(c_output_file, cuda_output_file)
                else:
                    print(f"Arquivos de saída ausentes para {run_id}")
                    comparison_passed = False

                if time_cuda and time_c > 0:
                    speedup = time_c / time_cuda
                else:
                    speedup = -1

                csv_writer.writerow([
                    run_id,
                    n,
                    iter_limit,
                    block_size_x,
                    block_size_y,
                    f"{time_c:.6f}" if time_c > 0 else "Erro",
                    f"{time_cuda:.6f}" if time_cuda > 0 else "Erro",
                    f"{speedup:.4f}" if speedup > 0 else "N/A",
                    1 if comparison_passed else 0
                ])

    print(f"Testes concluídos. Resultados armazenados em {csv_filename}.")

if __name__ == "__main__":
    main()
