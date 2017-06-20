#include "Bep.h"

int main () {
    Bep b("../InstanciasBEP/InstanceBEP-3-11-10-7.txt");
    cout << b.getBus() << endl;
    cout << b.getBusCapacity() << endl;
    cout << b.getSources() << endl;
    b.printVector(b.sources_capacity, b.getSources());
    cout << b.getCollections() << endl;
    cout << b.getPeopleTotal() << endl;
    b.printVector(b.p_collections, b.getCollections());
    cout << b.getShelters() << endl;
    cout << b.getSheltersTotal() << endl;
    b.printVector(b.shelters_capacity, b.getShelters());
    b.printMatrix(b.d_sources_collections, b.getSources(), b.getCollections());
    return 0;
}