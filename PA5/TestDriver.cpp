//
//  TestDriver.cpp
//  DSA_Xcode
//
//  Created by Albert Wu on 10/21/18.
//

#include "TestDriver.hpp"

int main(void) {
    Scheduler sched(12);
    std::ifstream input("input.txt");
    string line;
    while (std::getline(input, line)) {
        sched.tick(true, line);
    }
    while (!sched.done()) {
        sched.tick(true, ""); //tick without new job
    }
}
