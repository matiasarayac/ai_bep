#include "Bep.h"
#include "SimulatedAnnealing.h"

int main () {
    Bep b("../InstanciasBEP/InstanceBEP-1-4-2-4.txt");
//    cout << b.getBus() << endl;
//    cout << b.getBusCapacity() << endl;
//    cout << b.getSources() << endl;
//    printVector(b.sources_capacity, b.getSources());
//    cout << b.getCollections() << endl;
//    cout << b.getPeopleTotal() << endl;
//    printVector(b.p_collections, b.getCollections());
//    cout << b.getShelters() << endl;
//    cout << b.getSheltersTotal() << endl;
//    printVector(b.shelters_capacity, b.getShelters());
//    printMatrix(b.d_sources_collections, b.getSources(), b.getCollections());
//    printMatrix(b.d_collections_shelters, b.getCollections(), b.getShelters());

//    generateTourRandom(b.getCollections(), b.getShelters());

    SimulatedAnnealing sa(b);
    sa.generateSolution(b);
//    printSolution(sa.initial_sol);
//    getQualitySol(b, sa.initial_sol);

    return 0;
}