//
//  TestAll.hpp
//  DSA_Xcode
//
//  Created by Albert Wu on 9/27/18.
//

#ifndef TestAll_h
#define TestAll_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <list>
#include <vector>

using namespace std;

struct times {
    double total;
    double elim;
};

template<typename Josephus, template <typename, typename> class Container>
times timeEither(int N, int M);

void testList(int N, int M);
void testVector(int N, int M);

timespec startTimer();
double endTimer(timespec &start);

#endif /* TestAll_h */
