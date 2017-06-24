//
// Created by Matias Araya on 6/16/17.
//

#ifndef IA_SIMULATEDANNEALING_BEP_H
#define IA_SIMULATEDANNEALING_BEP_H

#include "includes.h"

class Bep {
    int buses;
    int bus_capacity;
    int sources;
    int collections;
    int p_total;
    int shelters;
    int shelters_total;


public:
    vector<int>sources_capacity;
    vector<int>p_collections;
    vector<int>shelters_capacity;
    vector<vector<int> > d_sources_collections;
    vector<vector<int> > d_collections_shelters;

    Bep(string);

    int getBus() { return buses; };
    int getBusCapacity() {return bus_capacity;};
    int getSources() {return sources;};
    int getCollections() {return collections;};
    int getPeopleTotal(){return p_total;};
    int getShelters(){return shelters;};
    int getSheltersTotal(){return shelters_total;};
};

void printVector(vector<int>, int);
void printMatrix(vector<vector<int> >);


#endif //IA_SIMULATEDANNEALING_BEP_H
