//
// Created by Matias Araya on 6/15/17.
//

#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(Bep b) {
    vector<vector<int> > busesTour;
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

//            printVector(tourRandom, 2);

            count++;
        }
    }

//    cout << "" << endl;

//    printMatrix(busesTour);

    vector<int> busTour;
    int sum = 0;

    for (int j = 1; j < b.getBus(); j++) {
        sum += (count / b.getBus());
        busTour.push_back(sum);
    }

    busTour.push_back(count);

//    printVector(busTour, busTour.size());

    vector<vector<int> > v;
    int bus = 0;

    for (int j = 0; j < count; j++) {

        v.push_back(busesTour[j]);

        if ((j + 1) >= busTour[bus]) {
            initial_sol.push_back(v);
            v.clear();
            bus++;
        }
    }

//    cout << "" << endl;
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

void SimulatedAnnealing::printSolution(vector<vector<vector<int> > > sol, vector<int> qualityBuses, Bep b) {

    ofstream solfile;
    string file;
    string sources = to_string(b.getSources());
    string collections = to_string(b.getCollections());
    string shelters = to_string(b.getShelters());
    string buses = to_string(b.getBus());
    file = "results/InstanceBEP-" + sources + "-" + collections + "-" + shelters +"-"+ buses + ".txt";
    solfile.open(file);

    for (int i = 0; i < sol.size(); i++) {
//        cout << i + 1;
//        cout << " ";
//        cout << qualityBuses[i];
//        cout << " ";

        solfile << i + 1;
        solfile << " ";
        solfile << qualityBuses[i];
        solfile << " ";
        for (int j = 0; j < sol[i].size(); j++) {
            for (int k = 0; k < sol[i][j].size(); k++) {
                if (k == 0) {
                    solfile << "(";
//                    cout << "(";
                }
                solfile << sol[i][j][k];
//                cout << sol[i][j][k];
                if (k == 0) {
                    solfile << ",";
//                    cout << ",";
                }
                if (k == 1) {
                    solfile << ") ";
//                    cout << ") ";
                }
            }
        }
        solfile << "" << endl;
//        cout << "" << endl;
    }
//    printBusesMaxDistance(qualityBuses);

    int max = returnMaxFromVector(qualityBuses);
    vector<int> busesMax;
    for (int i = 0; i < qualityBuses.size(); i++) {
        if (qualityBuses[i] == max) {
            busesMax.push_back(i + 1);
        }
    }

    for (int i = 0; i < busesMax.size(); i++) {
        solfile << busesMax[i];
        solfile << " ";
    }

    solfile << "" << endl;

//    printVector(c_shelters, c_shelters.size());

    for (int i = 0; i < c_shelters.size(); i++) {
        solfile << c_shelters[i] << endl;
    }

    solfile.close();
}

int getQualitySol(Bep b, vector<vector<vector<int> > > sol) {
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
//        printVector(distanceTotal, distanceTotal.size());
//        cout << "" << endl;
    }

    return returnMaxFromVector(distanceTotal);
}


int returnMaxFromVector(vector<int> v) {
    int max = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] > max) max = v[i];
    }
//    cout << "Max: ";
//    cout << max << endl;
    return max;
}

void SimulatedAnnealing::generateSolution(Bep b) {
    int i = 0;
    int diff = 0;
    int collections = b.getCollections();
    T = collections * 10;
    int count = 0;
    int it = 0;
    int reduceTemp = T / 10;
    vector<vector<vector<int> > > current_sol = initial_sol;
    vector<vector<vector<int> > > best_sol = initial_sol;
    vector<vector<vector<int> > > new_sol;
    double random;
    double e = 0;
    while (count < 100) {

        if (it == reduceTemp) {
            it = 0;
            if (T - collections > 0) {
                T -= collections;
            }
        } else {
            it++;
        }


//        cout << T << endl;

//        cout << "Q current Sol: ";
//        cout << getQualitySol(b, current_sol) << endl;

        new_sol = swapSolution(current_sol, b);
//        cout << "Q new Sol: ";
//        cout << getQualitySol(b, new_sol) << endl;
        diff = differenceQuality(current_sol, new_sol, b);

//        cout << "Q best Sol: ";
//        cout << getQualitySol(b, best_sol) << endl;

//        cout << "Difference: ";
//        cout << diff << endl;

        random_device rd;
        mt19937 rng(rd());
        uniform_real_distribution<> dis(0, 1); // rage 0 - 1
        random = dis(rng);
//        cout << "Random : ";
//        cout << random << endl;

        e = exp((double) diff / (double) T);

//        cout << "Exp: ";
//        cout << e << endl;

        if (random < e) {
            current_sol = new_sol;
//            cout << "Accepted" << endl;
        }

        if (getQualitySol(b, current_sol) < getQualitySol(b, best_sol)) {
            best_sol = current_sol;
            count = 0;
        } else {
            count++;
        }

        i++;
    }

    final_sol = best_sol;
    printSolution(best_sol, getQualityBuses(b), b);

}

//The swap works taking the last tour of the bus with more tours
//And put it in other random bus
vector<vector<vector<int> > > swapSolution(vector<vector<vector<int> > > sol, Bep b) {
    int busMaxTours = 0;
    int maxTours = 0;
    int tours = 0;
    for (int i = 0; i < sol.size(); i++) {
        tours = 0;
        for (int j = 0; j < sol[i].size(); j++) {
            tours++;
        }
        if (tours > maxTours) {
            busMaxTours = i;
            maxTours = tours;
        }
    }

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> ranges(0, (b.getBus() - 1));
    int busRandom = ranges(rng);

    while (busRandom == busMaxTours) {
        busRandom = ranges(rng);
    }

    //Swap vector of bus with max tours to random bus
    sol[busRandom].push_back(sol[busMaxTours][maxTours - 1]);
    sol[busMaxTours].erase(sol[busMaxTours].begin() + (maxTours - 1));

//    printSolution(sol);
//    getQualitySol(b, sol);

    return sol;

}

int differenceQuality(vector<vector<vector<int> > > current_sol, vector<vector<vector<int> > > new_sol, Bep b) {
    // We need to minimize the solution, so it's current - new
    return getQualitySol(b, current_sol) - getQualitySol(b, new_sol);
}

vector<int> SimulatedAnnealing::getQualityBuses(Bep b) {
    vector<int> busSources;
    vector<int> distanceTotal;
    for (int i = 0; i < b.getSources(); i++) {
        for (int j = 0; j < b.sources_capacity[i]; j++) {
            busSources.push_back(i + 1);
            distanceTotal.push_back(0); // Initialize all buses with distance 0
        }
    }

    int collection = 0;
    int shelter = 0;
    int next_collection = 0;
    for (int i = 0; i < final_sol.size(); i++) { // Buses
        for (int j = 0; j < final_sol[i].size(); j++) { // Tours
            for (int k = 0; k < final_sol[i][j].size(); k++) { // Collection and Shelter
                if (k == 0) {
                    collection = final_sol[i][j][k];
                    if ((j + 1) < final_sol[i].size()) {
                        next_collection = final_sol[i][j + 1][k];
                    }
                } else shelter = final_sol[i][j][k];
            }

            // Add distance from source to first collection
            if (j == 0) {
                distanceTotal[i] += b.d_sources_collections[busSources[i] - 1][collection - 1];
            }

            // Add distance from collection to source
            distanceTotal[i] += b.d_collections_shelters[collection - 1][shelter - 1];

            //Add distance from source to next collection (only if there is another tour left)
            if ((j + 1) < final_sol[i].size()) {
                distanceTotal[i] += b.d_collections_shelters[next_collection - 1][shelter - 1];
            }


        }
    }

    return distanceTotal;
}

void printBusesMaxDistance(vector<int> v) {

    int max = returnMaxFromVector(v);
    vector<int> busesMax;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == max) {
            busesMax.push_back(i + 1);
        }
    }

    for (int i = 0; i < busesMax.size(); i++) {
        cout << busesMax[i];
        cout << " ";
    }

    cout << "" << endl;
}