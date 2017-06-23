//
// Created by Matias Araya on 6/15/17.
//

#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing() {
    vector<vector<int>> busesTour;
    Bep b("../InstanciasBEP/InstanceBEP-1-4-2-4.txt");
    p_collections = b.p_collections;
    c_shelters = b.shelters_capacity;

    vector<int> tourRandom;
    int shelter = 0;
    int collection = 0;
    int count = 0;
    while (peopleInCollections(p_collections, b.getCollections()) == 0) {
        tourRandom = generateTourRandom(b.getCollections(), b.getShelters());

        shelter = (tourRandom[1] - 1);
        collection = (tourRandom[0] - 1);
        if (c_shelters[shelter] - b.getBusCapacity() >= 0 && p_collections[collection] >= b.getBusCapacity()) {
            busesTour.push_back(tourRandom);
            c_shelters[shelter] -= b.getBusCapacity();
            p_collections[collection] -= b.getBusCapacity();

            printVector(tourRandom, 2);

            count++;
        }
    }

    cout << "" << endl;

    printMatrix(busesTour);

    vector<int> rand;
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> range(1, (count / b.getBus()) + 1);
    int random = range(rng);
    int sum = 0;
    for (int j = 1; j < b.getBus(); j++) {
        sum += random;
        rand.push_back(sum);
        random = range(rng);
    }

    rand.push_back(count);

    vector<vector<int>> v;
    int bus = 0;
    for (int j = 0; j < count; j++) {

        v.push_back(busesTour[j]);

        if ((j + 1) >= rand[bus]) {
            initial_sol.push_back(v);
            v.clear();
            bus++;
        }
    }

    cout << "" << endl;
}

vector<int> generateTourRandom(int collections, int shelters) {
    vector<int> v;
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> rangeCollections(1, collections);
    uniform_int_distribution<int> rangeShelters(1, shelters);
    int randCollections = rangeCollections(rng);
    int randShelters = rangeShelters(rng);
    v.push_back(randCollections);
    v.push_back(randShelters);

    return v;
}

int peopleInCollections(vector<int> collections, int length) {
    for (int i = 0; i < length; i++) {
        if (collections[i] > 0) {
            return 0; //There is people left in collections
        }
    }

    return 1; //There is no people left in collections
}

void SimulatedAnnealing::printSolution() {
    for (int i = 0; i < initial_sol.size(); i++) {
        for (int j = 0; j < initial_sol[i].size(); j++) {
            for (int k = 0; k < initial_sol[i][j].size(); k++) {
                if (k == 0) cout << "(";
                cout << initial_sol[i][j][k];
                if (k == 0) cout << ",";
                if (k == 1) cout << ") ";
            }
        }
        cout << "" << endl;
    }
}

int getQualitySol(Bep b, vector<vector<vector<int>>> sol) {
    vector<int> busSources;
    vector<int> distanceTotal;
    for (int i = 0; i < b.getSources(); i++) {
        for (int j = 0; j < b.sources_capacity[i]; j++) {
            busSources.push_back(i + 1);
            distanceTotal.push_back(0); // Initialize all buses with distance 0
        }
    }

//   printVector(busSources, busSources.size());
//    printVector(distanceTotal, distanceTotal.size());

    int collection = 0;
    int shelter = 0;
    int next_collection = 0;
    for (int i = 0; i < sol.size(); i++) { // Buses
        for (int j = 0; j < sol[i].size(); j++) { // Tours
            for (int k = 0; k < sol[i][j].size(); k++) { // Collection and Shelter
                if (k == 0) {
                    collection = sol[i][j][k];
                    if ((j + 1) < sol[i].size()) {
                        next_collection = sol[i][j + 1][k];
                    }
                } else shelter = sol[i][j][k];
            }

            // Add distance from source to first collection
            if (j == 0) {
                distanceTotal[i] += b.d_sources_collections[busSources[i] - 1][collection - 1];
            }

            // Add distance from collection to source
            distanceTotal[i] += b.d_collections_shelters[collection - 1][shelter - 1];

            //Add distance from source to next collection (only if there is another tour left)
            if ((j + 1) < sol[i].size()) {
                distanceTotal[i] += b.d_collections_shelters[next_collection - 1][shelter - 1];
            }


        }
        printVector(distanceTotal, distanceTotal.size());
        cout << "" << endl;
    }

    return returnMaxFromVector(distanceTotal);
}


int returnMaxFromVector(vector<int> v) {
    int max = 0;
    for (int i = 0; i < v.size(); i++) {
        if(v[i] > max) max = v[i];
    }
    cout << "Max: ";
    cout << max << endl;
    return max;
}
