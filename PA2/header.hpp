//
//  header.hpp
//  PA2


#ifndef header_hpp
#define header_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include <algorithm>
#include <vector>

using std::vector;
using std::string;

int maxSubSum1( const vector<int> & a );
int maxSubSum2( const vector<int> & a );
int maxSumRec( const vector<int> & a, int left, int right );
int maxSubSum3( const vector<int> & a );
int max3(int one, int two, int three) ;
int maxSubSum4( const vector<int> & a );
timespec startTimer();
double endTimer(timespec &start);
double handleAlgo(string algoName, int (*algoFunc)(const vector<int> &), const vector<int> & vec);
void writeToCSV();

#endif /* header_hpp */
