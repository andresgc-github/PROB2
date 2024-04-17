// mersenne_twister_engine random generator mt19937, it has period 2^19937 - 1
# include <stdio.h>
#include <chrono>
#include <random>

using namespace std;

int main ()
{
    double x;
    int k;
    //unsigned seed1 = 1946402705; // choose as seed a large number of choice
    unsigned seed1 = chrono::system_clock::now().time_since_epoch().count(); // obtain a seed from the system clock
    mt19937_64 generator(seed1);  // initialize the random number engine with seed1
    
    uniform_int_distribution<int> i_distribution(1, 100); //initialize the distribution i_distribution (from which we want to draw random numbers)
    uniform_real_distribution<double> r_distribution(0., 1.); //initialize the distribution r_distribution

    for (int i=0;i<10;i++)
    {
        k=i_distribution(generator);  //a random int extracted from the distribution i_distribution
        x=r_distribution(generator); //a random double extracted from the distribution r_distribution
        printf("%lf\t%i\n",x,k);
    }

  return 0;
}