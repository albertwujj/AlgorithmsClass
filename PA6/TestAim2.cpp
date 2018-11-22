//
//  TestAim2.cpp
//  DSA_Xcode
//
//  Created by Albert Wu on 11/21/18.
//

#include <stdio.h>
#include "TestAim.hpp"
//
//  TestAim1.cpp
//  DSA_Xcode
//
//  Created by Albert Wu on 11/21/18.
//

// class T is the hash function class
template <class T>
double insertIntoHT(QuadHashTable<string, T> ht, vector<string> data, int & num_collisions) {
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
double searchHT(QuadHashTable<string, T> ht, vector<string> queries) {
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
    full_hash hello;
    ifstream datafile;
    datafile.open("OHenry.txt");
    std::istream_iterator<string> start(datafile), end;
    vector<string> data(start, end);
    ifstream queriesfile;
    queriesfile.open("queries.txt");
    std::istream_iterator<string> startq(queriesfile), endq;
    vector<string> queries(startq, endq);

    //declare hash function functors
    simple_hash simpleh;
    prefix_hash prefixh;
    full_hash fullh;

    //open output csv
    ofstream csv;
    csv.open("aim2.csv");
    int num_collisions = 0;
    csv << ",Insert,,,Search, \nCollision Strategy, Total time, Average time, Total Collisions, Total time, Average time\n";

    //initialize hash tables with diff hash functions
    QuadHashTable<string, simple_hash> sht = QuadHashTable<string, simple_hash>(simpleh);
    QuadHashTable<string, prefix_hash> pht = QuadHashTable<string, prefix_hash>(prefixh);
    QuadHashTable<string, full_hash> fht = QuadHashTable<string, full_hash>(fullh);

    //collect and write data to csv
    double insertTime = insertIntoHT<simple_hash>(sht, data, num_collisions);
    double searchTime = searchHT<simple_hash>(sht, queries);
    csv << "Simple," << insertTime << "," << insertTime / data.size() << "," << num_collisions << ",";
    csv << searchTime << "," << searchTime / queries.size() << endl;

    insertTime = insertIntoHT<prefix_hash>(pht, data, num_collisions);
    searchTime = searchHT<prefix_hash>(pht, queries);
    csv << "Prefix," << insertTime << "," << insertTime / data.size() << "," << num_collisions << ",";
    csv << searchTime << "," << searchTime / queries.size() << endl;

    insertTime = insertIntoHT<full_hash>(fht, data, num_collisions);
    searchTime = searchHT<full_hash>(fht, queries);
    csv << "Full-Length," << insertTime << "," << insertTime / data.size() << "," << num_collisions << ",";
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
