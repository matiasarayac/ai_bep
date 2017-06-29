#include "SimulatedAnnealing.h"

int main (int argc, char* argv[]) {

    if(!argv[1]){
        cout<<"Problems reading parameters" << endl;
        return 0;
    } else{
        Bep b(argv[1]);
        SimulatedAnnealing sa(b);
        sa.generateSolution(b);
    }

    return 0;
}