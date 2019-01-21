#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
#include<vector>
#include "Chromosome.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <map>



class GeneticAlgorithm
{
    public:
    int noOfParents;
    int populationSize;
    vector<Chromosome> populations;
    vector<Chromosome> parents;
    vector<Chromosome> offsprings;
    double crossOverProb;
    double mutationProb;
    Chromosome bestChromosome;
    float bestFitness;

        GeneticAlgorithm(int populationSize,int noOfParents,double crossOverProb,double mutationProb,float bestFitness);
        void createChromosome();
        int getRandom();
        Chromosome getBestChromosome();
        void selectParent();
        void evaluateFitnessForAllChromosome();
        vector<Chromosome> crossOver(Chromosome parent1,Chromosome parent2);
        Chromosome mutation(Chromosome chro);
        vector<Chromosome> performCrossOverAndMutation();
        double getTotalFitness();
        void runGA(int noOfIteration);
        void displayChromosome();
        ~GeneticAlgorithm();


    protected:
    private:
};

#endif // GENETICALGORITHM_H
