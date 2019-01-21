/* This program is written to show genetic algorithm example.
The objective function is f(x)=sin((pi/180)*x)-1/x=0. */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#define _USE_MATH_DEFINES

using namespace std;

double func(double x);
double mutation(double a, double b);
double inversion(double x, double eps);
void crossover(double *x, double eps,double a, double b);
void sort(double *x, double *y);
double genetic(double a, double b, double eps);

int main()
{
    srand(time(NULL));
    cout << genetic(1.0,10.0,0.000001)<< endl;
    cin.get();
    return 0;
}

double func(double x)
{
    return sin(M_PI * x /180)-1/x;
}

double mutation(double a, double b)
{
    return fabs(((double)rand()/RAND_MAX)*b)+a;
}

double inversion(double x, double eps)
{
    static int sign=0;
    sign++;
    sign%=2;
    if(sign==0) return x-eps;
    else return x+eps;
}

void crossover(double *x,double eps,double a,double b)
{
    int k=99;
    for(int i=0;i<8;i++)
        for(int j=i+1;j<8;j++)
        {
            x[k]=(x[i]+x[j])/2;
            k--;
        }
    for(int i=0;i<8;i++)
    {
        x[k]=inversion(x[i],eps); k--;
        x[k]=inversion(x[i],eps); k--;
    }
    for(int i=8;i<k;i++)
    x[i]=mutation(a,b);
}

void sort(double *x,double *y)
{
    for(int i=0;i<100;i++)
    for(int j=i+1;j<100;j++)
    if(fabs(y[j])<fabs(y[i]))
    {
        double temp=y[i];
        y[i]=y[j];
        y[j]=temp;
        temp=x[i];
        x[i]=x[j];
        x[j]=temp;
    }
}

double genetic(double a,double b,double eps)
{
    double population[100];
    double f[100];
    int iter=0;
    for(int i=0;i<100;i++)
    {
        population[i]=mutation(a,b);
        f[i]=func(population[i]);

    }
    sort(population,f);
    do{
        iter++;
        crossover(population,eps,a,b);
        for(int i=0;i<100;i++)
        {
            f[i]=func(population[i]);
            sort(population,f);

        }
        cout<<iter<<" iterations :"<<population[0]<<endl;
    }while(fabs(f[0])>eps && iter <20000);
    cout<<iter<<"iterations"<<endl;
    return population[0];
}
