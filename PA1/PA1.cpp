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

int main(void){
    Node *head = NULL;
    Node *curr = NULL;
    std::ifstream input("input.txt");
    std::unordered_set<int> alreadyChosen;

    clock_t t;
    t = clock();

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

    std::cout << "\n" << "All times are in seconds" << "\n\n";

    float time_insert = (float) (clock() - t) / CLOCKS_PER_SEC;
    std::cout << "time_insert: " << time_insert << "\n";
    t = clock();
    
    int min = head->data;
    float time_min = (float) (clock() - t) / CLOCKS_PER_SEC;
    std::cout << "min: " << min << "\n";
    std::cout << "time_min: " << time_min << "\n";
    t = clock();

    int max = curr->data;
    float time_max = (float) (clock() - t) / CLOCKS_PER_SEC;
    std::cout << "max: " << max << "\n";
    std::cout << "time_max: " << time_max << "\n";
    t = clock();

    int medI = size / 2;
    bool needAverage = false;
    if (size % 2 != 0) {
        needAverage = true;
    }
    curr = head;
    for(int k = 0; k < medI; k++) {
        curr = curr->next;
    }
    int med = curr->data;
    if(needAverage) {
        med = (curr->next->data + med) / 2;
    }
    float time_med = (float) (clock() - t) / CLOCKS_PER_SEC;
    std::cout << "med: " << med << "\n";
    std::cout << "time_med: " << time_med << "\n";
}

