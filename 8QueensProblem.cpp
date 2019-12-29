#include<iostream>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<sstream>
#include<cstring>
#include<map>
#include<list>
#include<queue>
#include<ctime>
using namespace std;

int initialPopulationSize=10;
int chessBoardSize=8;

typedef struct{
    string arrangement;
    int cost;
}individual;

individual* createNode(){
    individual *ind = new individual();
    return ind;
}

typedef vector<individual*> population_type;

population_type population;


int fitnessValue(string arrangement){
    int fitness=(chessBoardSize)*(chessBoardSize-1)/2;
    for(int i=0;i<chessBoardSize;i++){
        for(int j=i+1;j<chessBoardSize;j++){
            if(arrangement[i]==arrangement[j] || (i-arrangement[i])==(j-arrangement[j]) || (i+arrangement[i])==(j+arrangement[j]))
               fitness--;
        }
    }
    return fitness;

}

void generatePopulation(){
    string samplePopulation="";
    individual *temp;
    int i;
    for(i=1;i<=chessBoardSize;i++){
            ostringstream s;
            s<<i;
            samplePopulation =samplePopulation+s.str();
    }

    for(i=0;i<initialPopulationSize;i++){
        random_shuffle(samplePopulation.begin(),samplePopulation.end());
        temp=createNode();
        temp->arrangement=samplePopulation;
        temp->cost=fitnessValue(samplePopulation);
        population.push_back(temp);
    }
}

individual *reproduce(individual*x,individual *y){
    individual *child=createNode();
    int n=chessBoardSize;
    int c=rand()%n;
    child->arrangement=(x->arrangement).substr(0,c)+(y->arrangement).substr(c,n-c+1);
    child->cost=fitnessValue(child->arrangement);
    return child;
}

individual* mutate(individual *child){
    int randomQueen= rand()%chessBoardSize+1;
    int randomPos=rand()%chessBoardSize+1;
    child->arrangement[randomQueen]=randomPos+48;
    return child;
}

bool isFit(individual *test){
    if(fitnessValue(test->arrangement)==((chessBoardSize)*(chessBoardSize-1)/2))
        return true;
    return false;
}

int randomSelection(){
    int randomPosition =rand()%population.size()%2;
    return randomPosition;
}

bool comp(individual *a,individual *b){
    return (a->cost,b->cost);
}

individual* GA(){

    individual *randomX,*randomY,*child;
    int rand1,rand2;
    bool found=0;

    while(!found){
        population_type new_population;
        for(int i=0;i<population.size();i++){
            sort(population.begin(),population.end(),comp);
            rand1=randomSelection();
            randomX=population[rand1];

            rand2=randomSelection();
            randomY=population[rand2];

            child=reproduce(randomX,randomY);
            if(rand()%2==0)
                child=mutate(child);
            if(isFit(child)){
                found=1;
                return child;
            }
            new_population.push_back(child);
        }
        population=new_population;
        return child;
    }

}

int main(){

    generatePopulation();
    individual* solution=GA();
    cout<<"The Possible Arrangement of 8 Queens so that no Queen attack the each other is:\n"<<"\t->"<<solution->arrangement<<endl;

    return 0;
}
