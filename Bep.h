//
// Created by Matias Araya on 6/16/17.
//

#ifndef IA_SIMULATEDANNEALING_BEP_H
#define IA_SIMULATEDANNEALING_BEP_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

class Bep {
    int buses;
    int bus_capacity;
    int sources;
    int sources_capacity[];

public:
    Bep(string);

    int getBus() { return buses; };
    int getBusCapacity() {return bus_capacity;};
    int getSources() {return sources;};
    void printSourcesCapacity();
};


#endif //IA_SIMULATEDANNEALING_BEP_H
