//
// Created by Matias Araya on 6/15/17.
//

#include "SimulatedAnnealing.h"

void readInstance(string instance){
    string line;
    int bus;
    int i = 0;
    ifstream myfile (instance);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            if(i == 0){
                bus = line[0] - 48;
            }
            i++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}

