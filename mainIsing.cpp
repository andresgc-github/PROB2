// Inclusión de paquetes
# include <stdio.h>
# include <cstdio> // Para el FILE
# include <iostream>
# include <cmath> // Para el sqrt por ejemplo
# include <string> // Para usar strings o algo así

using namespace std;
C:\COMPU2024
void Leer(int S[],string entrada);
void Escribir(int S[],string salida);
void ElegirPuntoRandom(int &n,int &m);
double DiferenciaEnergias(int n,int m,int N,double S[]);
double ProbabilidadMetropolis(double DE,double T);
void SpinFlip(int n,int m,int N,int S[]);

int main(){

    int SIZE=; // Tamaño de la matriz de spins
    int S[SIZE]; // Matriz de spins
    int n,m;  // Índices del punto random
    double T; // Temperatura entre 0 y 5
    double DE; // Diferencia de energía entre dos estados (Delta de E)
    double P; // Probabilidad Metrópolis =min(1,exp-DE/T)
    double p; // Probabilidad uniforme entre 0 y 1
    
    string entrada="spininicial"; // Fichero con la matriz de spines iniciales
    string salida="spins_data"; // No sé cómo se llama en el script

    int it_MonteCarlo=100;
    int it_Metropolis=SIZE*SIZE;
    int i,j; // Índices de los bucles de Monte Carlo y de Metrópolis respectivamente
    for(i=0,i<it_MonteCarlo,i++){
        for(j=0,j<it_Metropolis,j++){
            ElegirPuntoRandom(&n,&m);
            DE=DiferenciaEnergias(n,m,S);
            P=ProbabilidadMetropolis(DE,T);
            p=ProbabilidadRandom01;
            if(P>p){
                SpinFlip(n,m,S);
            } else;
        }
        Escribir(S,salida);
    }

    return 0;
}

void Leer(int S[],string entrada){



    return;
}

void Escribir(int S[],string salida){



    return;
}

void ElegirPuntoRandom(int &n,int &m){



    return;
}

double DiferenciaEnergias(int n,int m,int N,double S[]){

    double DE;
    DE=2*S[n][m]*(S[(n+1)%N][m]+S[(n-1)%N][m]+S[n][(m+1)%N]+S[n][(m-1)%N]);

    return DE;
}

double ProbabilidadMetropolis(double DE,double T){

    double P;
    P=exp(-DE/T);
    if(P<1){return P;} else return 1;
}

void SpinFlip(int n,int m,int S[]){

    S[n][m]*=-1, // Invierte el signo del spin
    return;
}