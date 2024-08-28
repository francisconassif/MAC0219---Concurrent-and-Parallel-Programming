/*
leapfrog.cpp

Código para o MiniEP #1 da disciplina MAC0219
Professor: Alfredo Goldman
Autor: Francisco Nassif Membrive

Execução:

g++ -o leapfrog leapfrog.cpp
./leapfrog

Entrada: não possui
Saída: valores solicitados no enunciado u[i] e x[i]
*/

#include <bits/stdc++.h>    // Utilizado para vetores, I/O, etc;
#include <cmath>            // Utilizado para exponencial

// Comandos para deixar o código mais limpo e ágil:

using namespace std;

#define pb push_back
#define FOR(i, a, n) for(int i = a; i < n; i++)
typedef long double ld;

// Main:

int main(){

    // Variáveis, todas em long double para evitar problemas nos
    // cálculos.
    ld nx = 500.0;
    ld x0 = 0.0;
    ld t0 = 0.0;
    ld xf = 10.0;
    ld tf = 10.0;

    // Vetores, também em long double e utilizando alocação dinâmica
    // assim como no código em python:

    vector<ld> u;
    vector<ld> v;
    vector<ld> a;
    vector<ld> x;

    // Deltas, nt e inicialização do contador de tempo:

    ld delx = (xf-x0)/(nx-1.0);
    ld delt = delx/2.0;
    ld nt = (tf-t0)/delt + 1.0;
    ld curr = t0;

    // Percorre todas as posições de t0 a tf enquanto preenche o vetor x:

    while(curr <= tf){
        x.pb(curr);
        curr += delx;
    }

    // Percorre os elementos de x enquanto preenche os vetores a, v e u:

    for(auto el : x){
        a.pb(0.0);
        v.pb(0.0);
        ld expoente = (el - 5.0)*(el - 5.0);
        ld add_u = exp(-expoente);
        u.pb(add_u);
    }

    // Reinicia o tempo para t0 e inicializa delt leapfrog:

    curr = t0;
    ld leapfrog;

    // Percorre novamente todos os tempos, com intervalo delt:

    while(curr <= tf){
        // Define o valor de delt leapfrog:
        if(curr == t0) leapfrog = delt/2.0;
        else leapfrog = delt;

        // Define os valores do vetor a:
        FOR(i, 1, x.size()-1){
            a[i] = u[i-1] + u[i+1] - 2.0*u[i];
            a[i] /= delx * delx;
        }

        // Define os valores do vetor v baseados nos calculados em a:
        FOR(i, 0, v.size()){
            v[i] = v[i] + a[i]*leapfrog;
        }

        // Por fim, define u baseado em v:
        FOR(i, 0, u.size()){
            u[i] = u[i] + v[i]*delt;
            //cout<<u[i]<<endl;
        }

        // Incrementa o tempo:
        curr += delt;
    }

    // Define os limites do intervalo que deve ser impresso [left, right):

    int left = (int) nx/2;
    left = left - 10;
    int right = left + 21;


    // Imprime os valores solicitados:
    FOR(i, left, right){
        cout<<x[i]<<' '<<u[i]<<endl;
    }

}
