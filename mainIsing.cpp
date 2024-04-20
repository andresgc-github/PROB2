// Inclusión de paquetes
# include <stdio.h>
# include <cstdio> // Para el FILE
# include <iostream>
# include <cmath> // Para el sqrt por ejemplo
# include <string> // Para usar strings o algo así
# include <vector> // Para trabajar más cómodamente con arrays enormes
# include <random> // Para generar números pseudoaleatorios
# include <chrono> // Para generar la seed usando el reloj interno del dispositivo
# include <fstream> // Para usar el fstream

using namespace std;

void Leer(vector<vector<int>> &S,string filename);
void Escribir(vector<vector<int>> &S,string filename);
void ElegirPuntoRandom(int &n,int N);
int DiferenciaEnergias(int n,int m,const vector<vector<int>> &S);
double ProbabilidadMetropolis(int DE,double T);
void SpinFlip(int n,int m,vector<vector<int>> &S);
void SpinsRandom(int N,int M,vector<vector<int>> &S);

int main(){
    
    int N,M; // Dimensiones de la matriz de spins
    vector<vector<int>> S;//(N,vector<int>(N)); // Matriz de spins // nombre_del_vector.size() es un entero
    int n,m;  // Índices del punto random
    double T=1.8; // Temperatura entre 0 y 5
    int DE; // Diferencia de energía entre dos estados (Delta de E)
    double P; // Probabilidad Metrópolis =min(1,exp-DE/T)
    double p; // Probabilidad uniforme entre 0 y 1

    unsigned seed1 = chrono::system_clock::now().time_since_epoch().count(); // obtain a seed from the system clock
    mt19937_64 generator(seed1);  // initialize the random number engine with seed1
    uniform_real_distribution<double> p_distribution(0., 1.); //initialize the distribution r_distribution

    string entrada="spininicial"; // Fichero con la matriz de spines iniciales
    string salida="ising_dataT21"; // Así se llama en el script

    //Leer(S,entrada);
    N=500; M=300;
    SpinsRandom(N,M,S);
    Escribir(S,salida);
    N=S.size();
    M=S[0].size();
    
    int i,j;
    
    int it_MonteCarlo=250;
    int it_Metropolis=N*M; // Índices de los bucles de Monte Carlo y de Metrópolis respectivamente    
    for(i=0;i<it_MonteCarlo;i++){
        for(j=0;j<it_Metropolis;j++){
            ElegirPuntoRandom(n,N);
            ElegirPuntoRandom(m,M);
            DE=DiferenciaEnergias(n,m,S);
            P=ProbabilidadMetropolis(DE,T);
            p=p_distribution(generator);
            if(P>p){ // Si queremos que siempre haga spinflip cuando Metropolis es 1, entonces debería ser un >=
                SpinFlip(n,m,S);
            } else;
        }
        Escribir(S,salida);
    }

    return 0;
}

// Presupone matrices rectangulares, no serviría para arrays de tipo a[][][]
void Leer(vector<vector<int>> &S,string filename){

    int i,j;
    int N=0;
    int M=0;
    string linea;
    fstream f1;
    filename+=".txt"; //el operador += (o el propio +) sí que funciona con
    f1.open(filename.c_str(),ios::in); //este .c_str() convierte el string en un array de char
    // El ios::in son movidas del .open(,) que en vez de ponerse con "r" aquí para leer es ios::in xd
    while (getline(f1,linea)) { // Almacena una línea del fichero al que apunta f1 en el string linea. Además, f1 almacena también la posición en la que se queda
    // Como getline lee lineas completas, f1 se va quedando cada vez en la línea siguiente, de manera que al volver a usar getline coge la siguiente linea de código, hasta que no quedan más
        if(N==0){ // Este método de genio cuenta el número de comas en la primera línea
            for (int i = 0; i < linea.length(); i++){ // Hago tantas iteraciones como caracteres haya en la línea, almacenada en el string linea
            // string.length() es un entero igual al número de caracteres en el string
                if (linea[i] == ',') M++; // Por cada caracter del string que sea una coma, cuenta 1
            }
            M++; // El número de componentes es el número de comas +1.
        }
        N++; // Incrementa el contador por cada línea leída        
    }
    f1.close();

    // Inicialización provisional para la matriz de spins
    // Para hacerlo, utilizo un método de pushbacks
     
    for(i=0;i<N;i++){ // El método consiste en crear primero vectores auxiliares, inyectárselos a S (con .push_back) y después...
        vector<int> aux; 
        S.push_back(aux);  // S.push_back(x) añade, cada vez que se aplica, el elemento (x) al vector S (es de la lib. <vector>)
        for(j=0;j<M;j++){  
            S[i].push_back(1); // ... inyectar el valor (1 en este caso) a cada componente de S[i], que es el vector auxiliar que le acabo de inyectar
        }
    }

    // Esta parte es lo de siempre ya por suerte
    FILE *f2;
    f2=fopen(filename.c_str(),"r");
    for(i=0;i<N;i++){
        for(j=0;j<(M-1);j++){
            fscanf(f2,"%i,",&S[i][j]); // Es muy importante el &, ya que lo que quiero pasarle es la dirección donde almacenar el entero
        } // Si no pongo el & lo que paso es el valor, lo cual no tendría ningún sentido
        fscanf(f2,"%i\n",&S[i][j]);
    }
    fclose(f2);

    return;
}





void Escribir(vector<vector<int>> &S,string filename){

    int i,j; // Contadores
    int N=S.size(); // Número de filas de la matriz de spins
    int M=S[0].size(); // Número de columnas de la matriz de spins

    FILE *f1;
    filename+=".dat";/*el operador += (o el propio +) sí que funciona con */
    f1=fopen(filename.c_str(),"a"); /*este .c_str() convierte el string en un array de 
    char. Esto lo hago porque el argumento de la funcion debe ser un  array de char*/
    /*"append": el write reescribe el archivo, el append añade justo al final B)*/
    for(i=0;i<N;i++){
        for(j=0;j<(M-1);j++){
            fprintf(f1,"%i,",S[i][j]); // El i es el entero, que en fprintf se escribe así
        }
        fprintf(f1,"%i\n",S[i][j]);
    }
    fprintf(f1,"\n"); // Escribe un enter al final de cada bloque de N líneas, para matchear con el script de Python
    fclose(f1);

    return;
}

// Esto está mal (aunque quizás funcione) porque estoy generando una distribución nueva (aunque al menos con seed diferente) cada vez que genero un número random.
// En su lugar, sería preferible inicializar la distribución fuera de la función y que cada llamada a la función simplemente tomase el siguiente número
// pseudoaletorio de la misma distribución, garantizando así que sea uniforme. De esta manera, no queda claro si será uniforme o no.
void ElegirPuntoRandom(int &n, int N){

    unsigned seed1 = chrono::system_clock::now().time_since_epoch().count(); // obtain a seed from the system clock
    mt19937_64 generator(seed1);  // initialize the random number engine with seed1
    uniform_int_distribution<int> i_distribution(0,N-1); //initialize the distribution i_distribution (from which we want to draw random numbers)
    
    n=1*i_distribution(generator); 
    // Confío y rezo por que genere un número random distinto cada vez que llamo a la distribución con generator

    return;
}

int DiferenciaEnergias(int n,int m,const vector<vector<int>> &S){ // El const impide que pueda alterarlo desde dentro de la función, 
// y el & (pasarlo por referencia) evita que se haga una copia del vector entero (comportamiento estandar al pasar objetos como parámetros). 
// En su lugar, pasa la referencia y trabaja con ella.

    int N=S.size();
    int M=S[0].size();
    int DE;
    DE=2*S[n][m]*(S[((n+1)%N+N)%N][m]+S[(((n-1)%N)+N)%N][m]+S[n][((m+1)%M+M)%M]+S[n][((m-1)%M+M)%M]); // Soy un genio

    return DE;
}

double ProbabilidadMetropolis(int DE,double T){

    double P;
    P=exp(-DE/T);
    if(P<1){return P;} else return 1;
}

void SpinFlip(int n,int m,vector<vector<int>> &S){

    S[n][m]*=-1; // Invierte el signo del spin
    return;
}

void SpinsRandom(int N,int M,vector<vector<int>> &S){

    unsigned seed1 = chrono::system_clock::now().time_since_epoch().count(); // obtain a seed from the system clock
    mt19937_64 generator(seed1);  // initialize the random number engine with seed1
    uniform_real_distribution<double> p_distribution(0.,1.); //initialize the distribution p_distribution (from which we want to draw random numbers)
    /*
    for(i=0;i<N;i++){ // El método consiste en crear primero vectores auxiliares, inyectárselos a S (con .push_back) y después...
        vector<int> aux; 
        S.push_back(aux);  // S.push_back(x) añade, cada vez que se aplica, el elemento (x) al vector S (es de la lib. <vector>)
        for(j=0;j<M;j++){  
            S[i].push_back(1); // ... inyectar el valor (1 en este caso) a cada componente de S[i], que es el vector auxiliar que le acabo de inyectar
        }
    }*/ // Así estaría recorriendo el bucle dos veces. Es mejor meter los valores con pushback directamente.
    
    int i,j;
    for(i=0;i<N;i++){
        vector<int> aux; 
        S.push_back(aux);
        for(j=0;j<M;j++){
            if(0.5<p_distribution(generator)){S[i].push_back(1);} else S[i].push_back(-1);
        }
    } // Compactito


    return;
}