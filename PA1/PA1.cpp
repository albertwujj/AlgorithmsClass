//
//  PA1.cpp
//  PA1
//
//  Created by Albert Wu on 8/26/18.
//

#include "PA1.hpp"

using std::cout;

struct Node {
    int data;
    Node *next;
};

int main(void){
    Node *head = NULL;

    std::ifstream input("input.txt");

    timespec start = startTimer();

    int size = 0;

    std::vector<int> vector;
    std::string line;
    Node *curr = head;
    while(std::getline(input, line)) {
        int num = 0;
        std::istringstream iss(line);
        iss >> num;
        Node* newNode = new Node;
        newNode->data = num;
        curr = head;
        while (curr->next != NULL && curr->next->data < num) {
            curr = curr->next;
        }
        Node* temp = curr->next;
        curr->next = newNode;
        newNode->next = temp;
        size++;
        if (size % 100 == 0) {
            cout << "Integers inserted: " << size << "\n";
        }
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

void swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
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
