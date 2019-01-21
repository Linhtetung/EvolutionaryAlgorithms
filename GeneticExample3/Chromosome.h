#ifndef CHROMOSOME_H
#define CHROMOSOME_H
#include<string>
#include <string>
#include <sstream>
using namespace std;

class Chromosome
{
    public:
        int* genes;
        int size;
    double fitness;
    double from,to;
        Chromosome();
        Chromosome(int *genes,int size);
        Chromosome(int size);
        ~Chromosome();
    int getGeneAt(int index);
    double evaluateFitness();
    double getFitness();
    int getChromosomeLength();
    std::string toStr();

    protected:
    private:
};

#endif // CHROMOSOME_H
