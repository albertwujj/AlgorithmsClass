#include "header.hpp"

using std::cout;
using std::string;
using std::vector;
using std::endl;

int main(int argc, char *argv[]) {
    char *filename = argv[1];
    std::ifstream infile(filename);
    std::string line;
    vector<int> vec;
    while(getline(infile, line)) {
        int num = 0;
        std::istringstream iss(line);
        iss >> num;
        vec.push_back(num);
    }
    cout << "times in milliseconds, in order from algos 1-4\n";

    timespec start = startTimer();
    maxSubSum1(vec);
    double time1 = endTimer(start);
    cout << time1 << endl;

    start = startTimer();
    maxSubSum2(vec);
    double time2 = endTimer(start);
    cout << time2 << endl;

    start = startTimer();
    maxSubSum3(vec);
    double time3 = endTimer(start);
    cout << time3 << endl;

    start = startTimer();
    maxSubSum4(vec);
    double time4 = endTimer(start);
    cout << time4 << endl;



}

//from my old PAs
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
