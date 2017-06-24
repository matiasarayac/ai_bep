//
// Created by Matias Araya on 6/15/17.
//

#ifndef IA_SIMULATEDANNEALING_SIMULATEDANNEALING_H
#define IA_SIMULATEDANNEALING_SIMULATEDANNEALING_H

#include "Bep.h"

class SimulatedAnnealing {
    public:
        int T;
        vector<vector<vector<int> > > initial_sol;
        vector<int> p_collections;
        vector<int> c_shelters;
        vector<vector<vector<int> > > final_sol;

        SimulatedAnnealing(Bep);
        void generateSolution(Bep);
        vector<int> getQualityBuses(Bep);
        void printSolution(vector<vector<vector<int> > >, vector<int>, Bep);
};

vector<int> generateTourRandom(int, int);
int peopleInCollections(vector<int>, int);
int getQualitySol(Bep, vector<vector<vector<int> > >);
int returnMaxFromVector(vector<int>);
vector<vector<vector<int> > > swapSolution(vector<vector<vector<int> > >, Bep b);
int differenceQuality(vector<vector<vector<int> > > sol1, vector<vector<vector<int> > > sol2, Bep);
void printBusesMaxDistance(vector<int>);



#endif //IA_SIMULATEDANNEALING_SIMULATEDANNEALING_H
