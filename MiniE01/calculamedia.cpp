#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

int main(){
    vector<ld> tempos(100);
    ld media=0.0;
    ld qtd = 100.0;
    int it = 100;
    while(it--){
        cin>>tempos[it];
        media += tempos[it];
    }
    media /= qtd;
    ld soma = 0.0;
    for(auto t : tempos){
        soma += (t - media)*(t-media);
    }
    soma /= qtd;

    ld dp = sqrt(soma);

    if(media > 100){
        cout<<"Tempo médio de execução em python: "<<media<<" ms"<<endl;
        cout<<"Desvio-padrão em python: "<<dp<<" ms"<<endl;
    }
    else{
        cout<<"Tempo médio de execução em c++: "<<media<<" ms"<<endl;
        cout<<"Desvio-padrão em c++: "<<dp<<" ms"<<endl;
    }
    
}
