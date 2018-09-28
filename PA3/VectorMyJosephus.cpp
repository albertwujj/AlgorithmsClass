//
//  VectorMyJosephus.cpp
//  
//
//  Created by Albert Wu on 9/13/18.
//

#include "VectorMyJosephus.h"

VectorMyJosephus::VectorMyJosephus(int N, int M) : circ() {
    int i = 0;
    for(i; i < N; i++) {
        circ.push_back(Person(i));
    }
    this->curr = circ.begin();
    this->N = N;
    this->M = M;
}

//no need for destructor as all member variables declared on stack.

void VectorMyJosephus::clear() {
    this->circ.clear();
}

int VectorMyJosephus::currentSize() {
    return this->circ.size();
}

bool VectorMyJosephus::isEmpty() {
    return !this->circ.size();
}

Person VectorMyJosephus::eliminateNext() {
    int i = 0;
    for(i = 0; i < M; i++) {
        this->curr++;
        if (this->curr == this->circ.end()) {
            this->curr = this->circ.begin(); // reset to beginning if past end of list
        }
    }
    Person temp = *this->curr;

    this->curr = this->circ.erase(this->curr); // erase() will return the ele. after deleted ele.
    if (this->curr == this->circ.end()) {
        this->curr = this->circ.begin();
    }
    return temp;
}

void VectorMyJosephus::printAll() {
    vector<Person>::iterator minID = this->circ.begin();
    vector<Person>::iterator i = this->circ.begin()++;
    // find min ID (orig. position)
    while (i != this->circ.end()) {
        if (i->getID() < minID->getID()) {
            minID = i;
        }
        i++;
    }

    // print all starting from minID
    i = minID;
    do {
        cout << i->getID() << " ";
        i++;
        if (i == this->circ.end()) {
            i = this->circ.begin();
        }
    } while (i->getID() != minID->getID());
    cout << endl;
}
