//
// Created by Matias Araya on 6/16/17.
//
#include "Bep.h"

Bep::Bep(string instance) {
    string line;
    string Sbus_capacity;
    string Sbuses;
    int i = 0;
    string token;
    string token2;
    ifstream myfile(instance);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            istringstream iss(line);
            while (getline(iss, token, ' ')) {
                istringstream isi(token);
                while (getline(isi, token2, ':')) {
//                    cout << token2 << endl;
                    if (i == 0) buses = stoi(token2);
                    else if (i == 1) bus_capacity = stoi(token2);
                    else if (i == 2) {
                        sources = stoi(token2);
                        for (int j = 0; j <= sources; j++) {
                            getline(iss, token, ' ');
                            sources_capacity[j] = stoi(token);
                        }
                    }

                    i++;
                }
            }
        }
        myfile.close();
    } else cout << "Unable to open file";
}

void Bep::printSourcesCapacity() {
    for (int i = 0; i < sources; i++) {
        cout << sources_capacity[i];
        cout << " ";
    }
    cout << "" << endl;
}
