#include "Chromosome.h"



Chromosome::Chromosome(){};
Chromosome::Chromosome(int* genes,int size)
{
    this->genes=genes;
    this->size=size;

}

Chromosome::Chromosome(int size)
{
    genes=new int[size];
    this->size=size;
}

int Chromosome::getGeneAt(int index)
{
    return genes[index];
}

double Chromosome::evaluateFitness()
{
    double a=genes[0],b=genes[1],c=genes[2],d=genes[3];
    fitness=1/(a+2*b+3*c+4*d-30);
    return fitness;
}

double Chromosome::getFitness()
{
    return fitness;
}

int Chromosome::getChromosomeLength()
{
    return size;
}

string Chromosome::toStr()
{
    string s="[ ";
    for(int i=0;i<size;i++)
    {
        stringstream g;
        g<<genes[i];
        s += g.str() + " ";
    }

    s+="]";
    return s;
}

Chromosome::~Chromosome()
{
    //delete[] genes;
    }
