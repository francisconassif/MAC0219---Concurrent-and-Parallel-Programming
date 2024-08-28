"""
leapfrog.py

Código para o MiniEP #1 da disciplina MAC0219
Professor: Alfredo Goldman
Autor: Francisco Nassif Membrive

Execução:

python3 leapfrog.py

Entrada: não possui
Saída: valores solicitados no enunciado u[i] e x[i]
"""



import math # sera utilizado para a exponencial

# Declara as variáveis:
nx = 500
x0 = 0
t0 = 0
xf = 10
tf = 10

# Cria listas de alocação dinâmica para funcionarem como os vetores:
u = []
v = []
a = []
x = []

# Calcula delt e delx
delx = (xf-x0)/(nx-1)
delt = delx/2

# Calcula nt, que está no pseudo-código mas não é utilizado:
nt = (tf-t0)/delt + 1

# Inicia a variável do tempo em t0:
curr = t0

# Percorre todas as posições de t0 a tf enquanto preenche o vetor x:
while(curr <= tf):
    x.append(curr)
    curr+=delx

# Percorre os elementos de x enquanto preenche os vetores a, v e u:
for el in x:
    a.append(0)
    v.append(0)
    add_u = (math.e)**(-(el-5)**2)
    u.append(add_u)

# Reinicia o tempo para t0:    
t = t0

# Percorre novamente todos os tempos, com intervalo delt:
while(t <= tf):
    # Define o valor de delt leapfrog:
    if(t == t0):
        leapfrog = delt/2
    else:
        leapfrog = delt
    # Define os valores do vetor a:
    for i in range(len(x)-1):
        if(i == 0):
            continue
        a[i] = u[i-1] + u[i+1] - 2*u[i]
        a[i] /= delx**2
    # Define os valores do vetor v baseados nos calculados em a:
    for i in range(len(v)):
        v[i] = v[i] + a[i]*leapfrog
    # Por fim, define u baseado em v:
    for i in range(len(u)):
        u[i] = u[i] + v[i]*delt
    # Incrementa t
    t += delt

# Define os limites do intervalo que deve ser impresso [left, right):
left = nx//2 - 10
right = nx//2 + 11

# Imprime os valores solicitados:
for i in range(left, right):
    print(x[i],u[i])
        
