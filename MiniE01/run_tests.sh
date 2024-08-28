#!/bin/bash

# Arquivos para armazenar os tempos de execução
python_times_file="mini1_py_times.txt"
cpp_times_file="mini1_cpp_times.txt"

# Limpar os arquivos de saída antes de iniciar
> $python_times_file
> $cpp_times_file

# Executar o programa Python 100 vezes e registrar os tempos
echo "Executando leapfrog.py 100 vezes..."
for i in {1..100}; do
    start_time=$(date +%s%N)
    python3 leapfrog.py > /dev/null
    end_time=$(date +%s%N)
    elapsed_time=$((end_time - start_time))
    elapsed_time_ms=$(echo "scale=3; $elapsed_time / 1000000" | bc)
    echo $elapsed_time_ms >> $python_times_file
done
echo "Tempos de execução do leapfrog.py registrados em $python_times_file"

# Compilar e executar o programa C++ 100 vezes e registrar os tempos
echo "Compilando leapfrog.cpp..."
g++ leapfrog.cpp -o leapfrog

echo "Executando leapfrog.cpp 100 vezes..."
for i in {1..100}; do
    start_time=$(date +%s%N)
    ./leapfrog > /dev/null
    end_time=$(date +%s%N)
    elapsed_time=$((end_time - start_time))
    elapsed_time_ms=$(echo "scale=3; $elapsed_time / 1000000" | bc)
    echo $elapsed_time_ms >> $cpp_times_file
done
echo "Tempos de execução do leapfrog.cpp registrados em $cpp_times_file"

