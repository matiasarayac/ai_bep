#include <iostream>
#include "SimulatedAnnealing.h"

int main() {
    SimulatedAnnealing sa(3);
    std::cout << sa.get_number();
    return 0;

}