#include "GeneticAlgorithm.h"


GeneticAlgorithm::GeneticAlgorithm(int populationSize,int noOfParents,double crossOverProb,double mutationProb,float bestFitness)
{
    this->populationSize=populationSize;
    this->noOfParents=noOfParents;
    this->crossOverProb=crossOverProb;
    this->mutationProb=mutationProb;
    this->bestFitness=bestFitness;

}

void GeneticAlgorithm::createChromosome()
{

    for(int i=0;i<populationSize;i++)
    {
        int* genes=new int[4];

        Chromosome chro=Chromosome(genes,4);

        for(int g=0;g<chro.getChromosomeLength();g++)
       {
        genes[g]=getRandom();
        //cout<<genes[g]<<" ";
       }
       //cout<<endl;
        this->populations.push_back(chro);
    }
}

int GeneticAlgorithm::getRandom()
{
    return (rand()%30)+1;
}

Chromosome GeneticAlgorithm::getBestChromosome()
{
    Chromosome bestCh=populations[0];

    for(int i=0;i<populationSize;i++)
    {
        Chromosome current=populations[i];
        if(current.fitness>bestCh.fitness)
            bestCh=current;
    }

    Chromosome ch=Chromosome(bestCh.getChromosomeLength());
    for(int i=0;i<ch.size;i++)
    ch.genes[i]=bestCh.getGeneAt(i);
    ch.evaluateFitness();
    return bestCh;
}

void GeneticAlgorithm::selectParent()
{
    double totalFitness=0;

    for(int i=0;i<populationSize;i++)
    totalFitness+=populations[i].fitness;

    double start=0;
    for(int i=0;i<populationSize;i++)
    {
        double end=start+populations[i].fitness/totalFitness;
        populations[i].from=start;
        populations[i].to=end;
        start=end;
    }


    for(int i=0;i<noOfParents;i++)
    {
        double random=(double)rand()/(RAND_MAX+1.0);

        int p=0;
        for(int c=0;c<populationSize;c++)
        {

            if( populations[c].from<=random && random < populations[c].to)
                p=c;
        }

        Chromosome best=populations[p];
        parents.push_back(best);

    }
}


void GeneticAlgorithm::evaluateFitnessForAllChromosome()
{
    for(int i=0;i<populationSize;i++)
    populations[i].evaluateFitness();

    if(getBestChromosome().getFitness()>bestFitness)
    {
        bestChromosome=getBestChromosome();
        bestFitness=(float)getBestChromosome().getFitness();
    }

}

vector<Chromosome> GeneticAlgorithm::crossOver(Chromosome parent1,Chromosome parent2)
{
    vector<Chromosome> newChilds;
    double crossOver=(double)rand()/(RAND_MAX+1.0);
    int size=parent1.getChromosomeLength();
    int *geneOne=new int[size];
    int *geneTwo=new int[size];
    //Copy gene into new chromosome
    for(int i=0;i<size;i++)
    {
        geneOne[i]=parent1.getGeneAt(i);
        geneTwo[i]=parent2.getGeneAt(i);
    }

    Chromosome childOne=Chromosome(geneOne,size);
    Chromosome childTwo=Chromosome(geneTwo,size);

    if(crossOver<crossOverProb)
    {
      int crossOverPoint=rand()% size;

      //Perform crossover
      for(int c=crossOverPoint;c<size;c++)
      {
          int gOne=parent1.getGeneAt(c);
          int gTwo=parent2.getGeneAt(c);

          //mapping.insert(pair<int,int>(gOne,gTwo));
          //mapping.insert(pair<int,int>(gTwo,gOne));

          childOne.genes[c]=gTwo;
          childTwo.genes[c]=gOne;

      }

    }
    newChilds.push_back(childOne);
    newChilds.push_back(childTwo);

    return newChilds;
}

Chromosome GeneticAlgorithm::mutation(Chromosome chro)
{
    for(int i=0;i<chro.getChromosomeLength();i++)
    {
        double ran=(double)rand()/(RAND_MAX+1.0);
        if(ran<mutationProb)
        chro.genes[i]=getRandom();
    }
    return chro;
}

vector<Chromosome> GeneticAlgorithm::performCrossOverAndMutation()
{
    vector<Chromosome> newChilds;

    int parentOneIndex=rand()% noOfParents;

    int parentTwoIndex;

    do
    {
        parentTwoIndex=rand()% noOfParents;
    }while(parentOneIndex==parentTwoIndex);

    Chromosome parentOne=parents[parentOneIndex];
    Chromosome parentTwo=parents[parentTwoIndex];

    newChilds=crossOver(parentOne,parentTwo);


    for(int c=0;c<2;c++)
    newChilds[c]=mutation(newChilds[c]);

    return newChilds;
}

double GeneticAlgorithm::getTotalFitness()
{
    double sum=0;
    for(int i=0;i<populationSize;i++)
    sum+=populations[i].getFitness();
    return sum;
}

void GeneticAlgorithm::runGA(int noOfIteration)
{
    for(int i=0;i<noOfIteration;i++)
    {
        evaluateFitnessForAllChromosome();
        selectParent();
        cout<<"Iteration "<<i<<" total fitness "<<getTotalFitness()<<" Best "<<getBestChromosome().fitness<<endl;
        vector<Chromosome> offsprings;

        for(int j=0;j<populationSize/2;j++)
        {
            vector<Chromosome> childs=performCrossOverAndMutation();
            for(int z=0;z<2;z++)
            offsprings.push_back(childs[z]);
        }

        populations.clear();
        for(int c=0;c<populationSize;c++)
        populations.push_back(offsprings[c]);
    }
}

void GeneticAlgorithm::displayChromosome()
{
    for(int i=0;i<populationSize;i++)
    {
        Chromosome chrom=populations[i];
        cout<<"Chromosome "<<i<<endl;
        chrom.evaluateFitness();
        cout<<"Fitness "<<chrom.getFitness()<<endl;
    }
}

GeneticAlgorithm::~GeneticAlgorithm()
{
    for(int i=0;i<populationSize;i++)
    delete []populations[i].genes;
}
