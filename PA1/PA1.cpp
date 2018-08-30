//
//  PA1.cpp
//  PA1
//
//  Created by Albert Wu on 8/26/18.
//

#include "PA1.hpp"


struct Node {
    int data;
    Node *next;
};

using std::cout;

int main(void){

    setbuf(stdout, NULL);

    Node *head = NULL;
    Node *curr = NULL;
    std::ifstream input("input.txt");
    std::unordered_set<int> alreadyChosen;

    timespec start = startTimer();

    int size = 0;
    int j = 0;


    while(true) {
        int minNum = -1;
        int minNumI = -1;
        bool firstNum = false;
        int i = 0;
        std::string line;

        while(std::getline(input, line)) {
            int num = 0;
            std::istringstream iss(line);
            iss >> num;
            if (alreadyChosen.find(i) == alreadyChosen.end() && (num < minNum || !firstNum)) {
                minNum = num;
                minNumI = i;
                firstNum = true;
            }
            i++;
        }

        if(!firstNum) {
            // all numbers have already been chosen
            break;
        }

        alreadyChosen.insert(minNumI);
        Node* newNode = new Node;
        newNode->data = minNum;
        if (head == NULL) {
            head = newNode;
            curr = head;
        } else {
            curr->next = newNode;
            curr = curr->next;
        }
        // go back to beginning of file
        input.clear();
        input.seekg(0, std::ios::beg);
        if(j==0) {
            size = i;
        }
        j++;
    }

    std::cout << "\n" << "All times are in milliseconds" << "\n\n";

    double time_insert = endTimer(start);
    std::cout << "time_insert: " << time_insert << "\n";

    start = startTimer();
    int min = head->data;
    double time_min = endTimer(start);
    std::cout << "min: " << min << "\n";
    std::cout << "time_min: " << time_min << "\n";

    start = startTimer();
    int max = curr->data;
    double time_max = endTimer(start);
    std::cout << "max: " << max << "\n";
    std::cout << "time_max: " << time_max << "\n";

    start = startTimer();
    int medI = size / 2;
    bool needAverage = false;
    if (size % 2 == 0) {
        needAverage = true;
    }
    curr = head;
    for(int k = 0; k < medI - 1; k++) {
        curr = curr->next;
    }
    double med = 0.0;
    if(size == 1) {
        med = curr->data;
    } else {
        med = (double) curr->next->data;
        if(needAverage) {
            double prev = (double) curr->data;
            med = (double) (prev+med) / 2;
        }
    }
    double time_med = endTimer(start);
    std::cout << "med: " << med << "\n";
    std::cout << "time_med: " << time_med << "\n";
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
