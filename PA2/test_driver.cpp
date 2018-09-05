#include "header.hpp"

using std::cout;
using std::string;

int main(int argc, char *argv[]) {
    string *filename = argv[1]
    std::ifstream infile(*filename);
    std::string 
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
