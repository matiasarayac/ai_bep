#include "SimulatedAnnealing.h"

int main (int argc, char* argv[]) {

    if(!argv[1]){
        cout<<"Problemas en la lectura de los parametros" << endl;
        exit(1);
    } else{
        Bep b(argv[1]);
        SimulatedAnnealing sa(b);
        sa.generateSolution(b);
    }

    return 0;
}