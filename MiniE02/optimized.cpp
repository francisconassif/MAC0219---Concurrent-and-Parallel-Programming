/*
eficiente.cpp

Código para o MiniEP #2 da disciplina MAC0219
Professor: Alfredo Goldman
Autor: Francisco Nassif Membrive

Execução:

g++ -O3 -mavx -mfma optimized.cpp -o optimized 
./optimized

Entrada: não possui
Saída: valores solicitados no enunciado u[i] e x[i]
*/

#include <bits/stdc++.h>    // Utilizado para vetores, I/O, etc;
#include <cmath>            // Utilizado para exponencial

// Comandos para deixar o código mais limpo e ágil:

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define pb push_back
#define FOR(i, a, n) for(int i = a; i < n; i++)
typedef double ld;

// Main:

int main(){ _

    // Variáveis
    ld nx = 500.0;
    ld x0 = 0.0;
    ld t0 = 0.0;
    ld xf = 10.0;
    ld tf = 10.0;

    // Vetores, agora utilizando alocação estática

    ld u[500];
    ld v[500];
    ld a[500];
    ld x[500];

    memset(v, 0.0, sizeof u);
    memset(a, 0.0, sizeof a);

    // Deltas, nt e inicialização do contador de tempo:
    // Foi removido nt que não era utilizado

    ld delx = (10.0)/(499.0);
    ld delt = (5.0)/499.0;
    ld curr = t0;

    // Percorre todas as posições de t0 a tf enquanto preenche o vetor x:

    FOR(i, 0, 500){
        x[i]=curr;
        curr+=delx;
        ld expoente = (x[i] - 5.0)*(x[i] - 5.0);
        ld add_u = exp(-expoente);
        u[i]=add_u;
    }
    
    // Reinicia o tempo para t0 e inicializa delt leapfrog:

    curr = t0;
    ld leapfrog;
    ld div = delx*delx;

    // Percorre novamente todos os tempos, com intervalo delt:

    while(curr <= tf){
        // Define o valor de delt leapfrog:
        if(curr == t0) leapfrog = delt/2.0;
        else leapfrog = delt;

        FOR(i, 0, 500){
            if(i != 0 && i != nx-1){
                a[i] = u[i-1] + u[i+1] - 2.0*u[i];
                a[i] /= div;
            }
            v[i] = v[i] + a[i]*leapfrog;
            if(i != 0){
                u[i-1] = u[i-1] + v[i-1]*delt;
            }
        }
        u[0]=u[0]+v[0]*delt;
        u[499]=u[499]+v[499]*delt;

        curr += delt;
    }

    // Define os limites do intervalo que deve ser impresso [left, right):

    int left = 240;
    int right = 261;

    // Imprime os valores solicitados:
    FOR(i, left, right){
        cout<<x[i]<<' '<<u[i]<<endl;
    }

}
