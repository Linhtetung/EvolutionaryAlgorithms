#include <iostream>
#include <string>
#include "Chromosome.h"
#include "GeneticAlgorithm.h"
#include <ctime>

/* This is genetic algorithm example for solving the equation : a+2b+3c+4d-30=0. This program is
C++ version of Ko Thet Khine's genetic algorithm example. But it is absolutely not the same and
in some places I eliminate some codes. */

using namespace std;




int main()
{
    srand(time(0));

    GeneticAlgorithm gm=GeneticAlgorithm(40,20,0.8,0.3,-100000);
    gm.createChromosome();
    gm.runGA(200);
    Chromosome ch=gm.bestChromosome;
    int a=ch.genes[0],b=ch.genes[1],c=ch.genes[2],d=ch.genes[3];
    double result=a+2*b+3*c+4*d-30;
    cout<<"Equation "<<result<<endl;
    cout<<"a: "<<a<<" b: "<<b<<" c: "<<c<<" d: "<<d<<endl;
    return 0;
}
