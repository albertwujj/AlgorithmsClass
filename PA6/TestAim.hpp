//
//  TestAim.hpp
//  DSA_Xcode
//
//  Created by Albert Wu on 11/21/18.
//

#ifndef TestAim_hpp
#define TestAim_hpp

#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>
#include "QuadraticProbing.hpp"
#include "LinearProbing.hpp"
#include "SeparateChaining.hpp"
using std::vector;

timespec startTimer();
double endTimer(timespec &start);

template <class T>
double insertIntoHT(T ht, vector<string> data, int & num_collisions);

template <class T>
double searchHT(T ht, vector<string> queries);


//different hash functions as functors
struct simple_hash {
    simple_hash() {}
    int operator()(const string & key) const {
        int hashVal = 0;
        for (char ch: key) {
            hashVal += ch;
        }
        return hashVal % tableSize;
    }
    int tableSize;
};
struct prefix_hash {
    prefix_hash() {}
    int operator()(const string & key) const {
        return (key[0] + 27 * key[1] + 729 * key[2]) % tableSize;
    }
    int tableSize;
};
struct full_hash {
    full_hash() {}
    int operator()(const string & key) const {
        unsigned int hashVal = 0;
        for (char ch: key) {
            hashVal = 37 * hashVal + ch;
        }
        return hashVal % tableSize;
    }
    int tableSize;
};



#endif /* TestAim1_hpp */
