#include "header.hpp"

using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

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
    int size = vec.size();
    cout << "size of input sequence: " << size << endl << endl;

    handleAlgo("maxSubSum1", maxSubSum1, vec);
    handleAlgo("maxSubSum2", maxSubSum2, vec);
    handleAlgo("maxSubSum3", maxSubSum3, vec);
    handleAlgo("maxSubSum4", maxSubSum4, vec);

    //writeToCSV();
}

double handleAlgo(string algoName, int (*algoFunc)(const vector<int> &), const vector<int> & vec) {
    timespec start = startTimer();
    int result = (*algoFunc)(vec);
    int time_taken = endTimer(start);
    cout << algoName << endl;
    cout << "Result (max subsequence sum): " << result << endl;
    cout << time_taken << " milliseconds taken" << endl << endl;
    return time_taken;
}

//makes all necessary timings automatically
void writeToCSV() {
    ofstream plot;
    plot.open("plot.csv");
    vector<string> sizes = {"8","16","32","64","128","256","512","1024","2048","4096","8192"};
    for(string size : sizes) {
        vector<int> total_times(4);
        int i = 0;
        for(i = 0; i < 10; i++) {
            string filename = "inputs/input_"+size+"_"+std::to_string(i)+".txt";
            cout << filename << endl;
            ifstream infile(filename);
            std::string line;
            vector<int> vec;
            while(getline(infile, line)) {
                int num = 0;
                std::istringstream iss(line);
                iss >> num;
                vec.push_back(num);
            }
            total_times.at(0) = handleAlgo("maxSubSum1", maxSubSum1, vec);
            total_times.at(1) = handleAlgo("maxSubSum2", maxSubSum2, vec);
            total_times.at(2) = handleAlgo("maxSubSum3", maxSubSum3, vec);
            total_times.at(3) = handleAlgo("maxSubSum4", maxSubSum4, vec);
        }
        plot << size << ",";
        for(double timing : total_times) {
            plot << timing/10 << ",";
        }
        plot << endl;
    }
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
