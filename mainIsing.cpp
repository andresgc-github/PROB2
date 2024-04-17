// Inclusión de paquetes
# include <stdio.h>
# include <cstdio> // Para el FILE
# include <iostream>
# include <cmath> // Para el sqrt por ejemplo
# include <string> // Para usar strings o algo así
# include <vector> // Para trabajar más cómodamente con arrays enormes
# include <random> // Para generar números pseudoaleatorios
# include <chrono> // Para generar la seed usando el reloj interno del dispositivo

using namespace std;

void Leer(vector<vector<int>> &S,string entrada);
void Escribir(vector<vector<int>> &S,string salida);
void ElegirPuntoRandom(int &n,int &m);
double DiferenciaEnergias(int n,int m,double S[]);
double ProbabilidadMetropolis(double DE,double T);
void SpinFlip(int n,int m,vector<vector<int>> &S);

int main(){

    
    vector<vector<int>> S; // Matriz de spins // nombre_del_vector.size() es un entero
    int N=S.size(); // Tamaño de la matriz de spins
    int n,m;  // Índices del punto random
    double T; // Temperatura entre 0 y 5
    double DE; // Diferencia de energía entre dos estados (Delta de E)
    double P; // Probabilidad Metrópolis =min(1,exp-DE/T)
    double p; // Probabilidad uniforme entre 0 y 1

    unsigned seed1 = chrono::system_clock::now().time_since_epoch().count(); // obtain a seed from the system clock
    mt19937_64 generator(seed1);  // initialize the random number engine with seed1
    uniform_real_distribution<double> p_distribution(0., 1.); //initialize the distribution r_distribution

    string entrada="spininicial"; // Fichero con la matriz de spines iniciales
    string salida="spins_data"; // No sé cómo se llama en el script

    
    int it_MonteCarlo=100;
    int it_Metropolis=N*N;
    int i,j; // Índices de los bucles de Monte Carlo y de Metrópolis respectivamente
    for(i=0,i<it_MonteCarlo,i++){
        for(j=0,j<it_Metropolis,j++){
            ElegirPuntoRandom(n,m,N);
            DE=DiferenciaEnergias(n,m,S);
            P=ProbabilidadMetropolis(DE,T);
            p=p_distribution(generator);
            if(P>p){
                SpinFlip(n,m,S);
            } else;
        }
        Escribir(S,salida);
    }

    return 0;
}

void Leer(vector<vector<int>> &S,string entrada){



    return;
}

void Escribir(vector<vector<int>> &S,string salida){



    return;
}

// Esto está mal (aunque quizás funcione) porque estoy generando una distribución nueva (aunque al menos con seed diferente) cada vez que genero un número random.
// En su lugar, sería preferible inicializar la distribución fuera de la función y que cada llamada a la función simplemente tomase el siguiente número
// pseudoaletorio de la misma distribución, garantizando así que sea uniforme. De esta manera, no queda claro si será uniforme o no.
void ElegirPuntoRandom(int &n,int &m,int N){

    unsigned seed1 = chrono::system_clock::now().time_since_epoch().count(); // obtain a seed from the system clock
    mt19937_64 generator(seed1);  // initialize the random number engine with seed1
    uniform_int_distribution<int> i_distribution(0,N-1); //initialize the distribution i_distribution (from which we want to draw random numbers)

    n=N*i_distribution(generator); // Probabilidad uniforme entre 0 y N-1
    m=N*i_distribution(generator); // Confío y rezo por que genere un número random distinto cada vez que llamo a la distribución con generator

    return;
}

double DiferenciaEnergias(int n,int m,const vector<vector<int>> &S){ // El const impide que pueda alterarlo desde dentro de la función, 
// y el & (pasarlo por referencia) evita que se haga una copia del vector entero (comportamiento estandar al pasar objetos como parámetros). 
// En su lugar, pasa la referencia y trabaja con ella.

    int N=S.size();
    double DE;
    DE=2*S[n][m]*(S[(n+1)%N][m]+S[(n-1)%N][m]+S[n][(m+1)%N]+S[n][(m-1)%N]);

    return DE;
}

double ProbabilidadMetropolis(double DE,double T){

    double P;
    P=exp(-DE/T);
    if(P<1){return P;} else return 1;
}

void SpinFlip(int n,int m,vector<vector<int>> &S){

    S[n][m]*=-1; // Invierte el signo del spin
    return;
}