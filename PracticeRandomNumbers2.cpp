// Code to learn to extract an event with probability p
// here we increase a counter with probability p 
// After N>>1 iterations, we expect that counter/N=p

# include <stdio.h>
#include <chrono>
#include <random>

using namespace std;

int main ()
{
    double x;
    int counter=0;
    double P=0.7;
    int N=1e8;

    unsigned seed1 = chrono::system_clock::now().time_since_epoch().count(); // obtain a seed from the system clock
    mt19937_64 generator(seed1);  // initialize the random number engine with seed1
    uniform_real_distribution<double> r_distribution(0., 1.); //initialize the distribution r_distribution

    for (int i=0;i<N;i++)
    {
        x=r_distribution(generator); //a random double extracted from the distribution r_distribution
        if(x<P)
            counter++;
    }

    printf("P= %lf, counter/N= %lf", P, counter/(1.*N));

  return 0;
}