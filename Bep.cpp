//
// Created by Matias Araya on 6/16/17.
//
#include "Bep.h"

Bep::Bep(string instance) {
    string line;
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
                    if (i == 0) buses = stoi(token2);
                    else if (i == 1) bus_capacity = stoi(token2);
                    else if (i == 2) {
                        sources = stoi(token2);
                        for (int j = 0; j < sources; j++) {
                            getline(iss, token, ' ');
                            sources_capacity.push_back(stoi(token));
                        }
                    } else if (i == 3) collections = stoi(token2);
                    else if (i == 4) {
                        p_total = stoi(token2);
                        for (int j = 0; j < collections; j++) {
                            getline(iss, token, ' ');
                            p_collections.push_back(stoi(token));
                        }
                    } else if (i == 5) shelters = stoi(token2);
                    else if (i == 6) {
                        shelters_total = stoi(token2);
                        for (int j = 0; j < shelters; j++) {
                            getline(iss, token, ' ');
                            shelters_capacity.push_back(stoi(token));
                        }
                    } else if (i == 8) {
                        for (int k = 0; k < sources; k++) {
                            vector<int> v;
                            if (k == 0) {
                                for (int j = 0; j < collections; j++) {
                                    getline(iss, token, ' ');
                                    v.push_back(stoi(token));
                                }

                            } else {
                                getline(myfile, line);
                                istringstream iss2(line);
                                getline(iss2, token, ' '); // Número con :

                                for (int j = 0; j < collections; j++) {
                                    getline(iss2, token, ' ');
                                    v.push_back(stoi(token));
                                }
                            }

                            d_sources_collections.push_back(v);
                        }
                    } else if (i == 11) {
                        for (int k = 0; k < collections; k++) {
                            vector<int> v;
                            if (k == 0) {
                                for (int j = 0; j < shelters; j++) {
                                    getline(iss, token, ' ');
                                    v.push_back(stoi(token));
                                }
                            } else {
                                getline(myfile, line);
                                istringstream iss2(line);
                                getline(iss2, token, ' ');

                                for (int j = 0; j < shelters; j++) {
                                    getline(iss2, token, ' ');
                                    v.push_back(stoi(token));
                                }
                            }

                            d_collections_shelters.push_back(v);
                        }
                    }
                    i++;
                }
            }
        }
        myfile.close();
    } else cout << "Unable to open file";
}

void printVector(vector<int> v, int length) {
    for (int i = 0; i < length; i++) {
        cout << v[i] << endl;
    }
}

void printMatrix(vector<vector<int>> m) {
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[i].size(); j++) {
            cout << m[i][j];
            cout << " ";
        }
        cout << " " << endl;
    }
}