//
//  TestAll.cpp
//  DSA_Xcode
//
//  Created by Albert Wu on 9/27/18.
//



#include "ListMyJosephus.h"
#include "VectorMyJosephus.h"

#include "TestAll.h"

//template function accepting either list or vector
template<typename Josephus, template <typename, typename> class Container>
times timeEither(int N, int M) {
    Josephus l(N, M);
    timespec startTotal = startTimer();
    double elimTime = 0;
    Container<Person, std::allocator<Person>> elimSeq;
    // eliminate until 1 player left
    while(l.currentSize() > 1) {
        timespec startElim = startTimer();
        elimSeq.push_back(l.eliminateNext());
        // removed print statements

        elimTime += endTimer(startElim);
    }
    double totalTime = endTimer(startTotal);
    elimTime /= (N - 1); //get average
    times timing;
    timing.total = totalTime;
    timing.elim = elimTime;
    return timing;
}


int main(void) {

    // test list and vector and print results
    testList(5,3);
    testVector(5,3);

    // time list and vector and print results to .csv file
    ofstream plot;
    plot.open("plot_test.csv");

    //with LIST
    //vary N from 4 to 8192
    int n = 2;
    for(n; n < 14; n++){
        int N = int(pow(2,n));
        int x;
        times timing = timeEither<ListMyJosephus, list>(N, 3);
        plot << N << "," << timing.total << ",," << N << "," << timing.elim << endl;
    }
    plot << endl;

    //vary M from 2 to 512
    int m = 1;
    for(m; m < 10; m++){
        int M = int(pow(2,m));
        times timing = timeEither<ListMyJosephus, list>(1024, M);
        plot << M << "," << timing.total << ",," << M << "," << timing.elim << endl;
    }
    plot << endl;

    //with VECTOR
    ///vary N from 4 to 8192
    n = 2;
    for(n; n < 14; n++){
        int N = int(pow(2,n));
        times timing = timeEither<VectorMyJosephus, vector>(N, 3);
        plot << N << "," << timing.total << ",," << N << "," << timing.elim << endl;
    }
    plot << endl;

    //vary M from 2 to 512
    m = 1;
    for(m; m < 10; m++){
        int M = int(pow(2,m));
        times timing = timeEither<VectorMyJosephus, vector>(1024, M);
        plot << M << "," << timing.total << ",," << M << "," << timing.elim << endl;
    }
}

// timing functions
timespec startTimer() {
    timespec *start = new timespec();
    clock_gettime(CLOCK_REALTIME, start);
    return *start;
}

double endTimer(timespec &start) {
    timespec *end = new timespec();
    clock_gettime(CLOCK_REALTIME, end);
    // find diff in microseconds
    return (end->tv_sec - start.tv_sec) * 1000000 + (end->tv_nsec - start.tv_nsec) / 1000;
}
