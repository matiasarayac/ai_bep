#include "Bep.h"

int main () {
    Bep b("../InstanciasBEP/InstanceBEP-2-9-7-5.txt");
    cout << b.getBus() << endl;
    cout << b.getBusCapacity() << endl;
    cout << b.getSources() << endl;
    b.printSourcesCapacity();
    return 0;
}