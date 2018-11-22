//
//  TestAim1.cpp
//  DSA_Xcode
//
//  Created by Albert Wu on 11/21/18.
//

#include "TestAim.hpp"

template <class T>
double insertIntoHT(T ht, vector<string> data, int & num_collisions) {
    double insertTime = 0.0;
    num_collisions = 0;
    //insert each string and count collisions and time taken
    for (std::vector<string>::iterator i = data.begin(); i != data.end(); i++) {
        int new_collisions = 0;
        timespec start = startTimer();
        ht.insert(*i, new_collisions);
        double diff = endTimer(start);

        insertTime += diff;
        num_collisions += new_collisions;
    }
    return insertTime;
}

template <class T>
double searchHT(T ht, vector<string> queries) {
    double searchTime = 0.0;
    //query each string and count time taken
    for (std::vector<string>::iterator i = queries.begin(); i != queries.end(); i++) {
        timespec start = startTimer();
        ht.contains(*i);
        double diff = endTimer(start);
        searchTime += diff;
    }
    return searchTime;
}

int main(void) {
    //open input files
    ifstream datafile;
    datafile.open("OHenry.txt");
    std::istream_iterator<string> start(datafile), end;
    vector<string> data(start, end);
    ifstream queriesfile;
    queriesfile.open("queries.txt");
    std::istream_iterator<string> startq(queriesfile), endq;
    vector<string> queries(startq, endq);

    //make hash tables with different collision reso. techniques
    ChainHashTable<string> chainingHT = ChainHashTable<string>();
    LinearHashTable<string> linearHT = LinearHashTable<string>();
    QuadHashTable<string> quadHT = QuadHashTable<string>();

    //open output csv
    ofstream csv;
    csv.open("aim1.csv");
    int num_collisions = 0;
    csv << ",Insert,,,Search, \nCollision Strategy, Total time, Average time, Total Collisions, Total time, Average time\n";

    //collect and write data to csv
    double insertTime = insertIntoHT<ChainHashTable<string>>(chainingHT, data, num_collisions);
    double searchTime = searchHT<ChainHashTable<string>>(chainingHT, queries);
    csv << "Chaining," << insertTime << "," << insertTime / data.size() << "," << num_collisions << ",";
    csv << searchTime << "," << searchTime / queries.size() << endl;

    insertTime = insertIntoHT<LinearHashTable<string>>(linearHT, data, num_collisions);
    searchTime = searchHT<LinearHashTable<string>>(linearHT, queries);
    csv << "Linear Probing," << insertTime << "," << insertTime / data.size() << "," << num_collisions << ",";
    csv << searchTime << "," << searchTime / queries.size() << endl;

    insertTime = insertIntoHT<QuadHashTable<string>>(quadHT, data, num_collisions);
    searchTime = searchHT<QuadHashTable<string>>(quadHT, queries);
    csv << "Quadratic Probing," << insertTime << "," << insertTime / data.size() << "," << num_collisions << ",";
    csv << searchTime << "," << searchTime / queries.size() << endl;


    csv.close();
}


timespec startTimer() {
    timespec *start = new timespec();
    clock_gettime(CLOCK_REALTIME, start);
    return *start;
}

double endTimer(timespec &start) {
    timespec *end = new timespec();
    clock_gettime(CLOCK_REALTIME, end);
    // find diff in milliseconds
    return (end->tv_sec - start.tv_sec) * 1000000 + (end->tv_nsec - start.tv_nsec) / 1000;
}
