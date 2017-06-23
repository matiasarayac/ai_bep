//
// Created by Matias Araya on 6/15/17.
//

#ifndef IA_SIMULATEDANNEALING_SIMULATEDANNEALING_H
#define IA_SIMULATEDANNEALING_SIMULATEDANNEALING_H

#include "includes.h"
#include "Bep.h"

class SimulatedAnnealing {
    public:
        int T;
        vector<vector<vector<int>>> initial_sol;
        vector<int> p_collections;
        vector<int> c_shelters;

        SimulatedAnnealing();
        void printSolution();

};

vector<int> generateTourRandom(int, int);
int peopleInCollections(vector<int>, int);
int getQualitySol(Bep, vector<vector<vector<int>>>);
int returnMaxFromVector(vector<int>);


#endif //IA_SIMULATEDANNEALING_SIMULATEDANNEALING_H
