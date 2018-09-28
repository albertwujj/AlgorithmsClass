
//
//  TestVectorMyJosephus.cpp
//
//
//  Created by Albert Wu on 9/27/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "VectorMyJosephus.h"

void testVector(int N, int M) {
    VectorMyJosephus l(N, M);
    vector<Person> elimSeq;
    // eliminate until 1 player left
    while(l.currentSize() > 1) {
        elimSeq.push_back(l.eliminateNext());
        cout << "Players left: ";
        l.printAll();
    }
    cout << "Elim sequence: ";
    for (auto p: elimSeq) {
        cout << p.getID() << " ";
    }
    cout << "Winner: ";
    l.printAll();
    cout << endl;
}
