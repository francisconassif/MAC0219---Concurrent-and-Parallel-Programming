#!/usr/bin/env python3
import subprocess

def run_c_code(binary):
  """Executa o código C e retorna a saída completa."""
  process = subprocess.Popen([f"./{binary}"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
  stdout, stderr = process.communicate()
  return stdout

# Executar ambas as versões e coletar resultados
resultados_original = []
resultados_fixed = []

for _ in range(1000):
  resultados_original.append(run_c_code("problemqueue"))
  resultados_fixed.append(run_c_code("safequeue"))

# Contar ocorrências de "Fila cheia" e "Fila vazia"
contagem_original_cheia = sum([output.count("Fila cheia!") for output in resultados_original])
contagem_original_vazia = sum([output.count("Fila vazia!") for output in resultados_original])

contagem_fixed_cheia = sum([output.count("Fila cheia!") for output in resultados_fixed])
contagem_fixed_vazia = sum([output.count("Fila vazia!") for output in resultados_fixed])

# Imprimir e comparar resultados
print("Resultados do código original (com problema de concorrência):")
print(f"Número de ocorrências de Fila cheia: {contagem_original_cheia}")
print(f"Número de ocorrências de Fila vazia: {contagem_original_vazia}")

print("\nResultados do código corrigido (com mutex):")
print(f"Número de ocorrências de Fila cheia: {contagem_fixed_cheia}")
print(f"Número de ocorrências de Fila vazia: {contagem_fixed_vazia}")
