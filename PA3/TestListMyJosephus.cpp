//
//  TestListMyJosephus.cpp
//  
//
//  Created by Albert Wu on 9/25/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "ListMyJosephus.h"

void testList(int N, int M) {
    ListMyJosephus l(N, M);
    list<Person> elimSeq;
    // eliminate until 1 player left
    while(l.currentSize() > 1) {
        elimSeq.push_back(l.eliminateNext());
        cout << "Players left: ";
        l.printAll();
    }
    cout << "Elim sequence: ";
    for (auto it = elimSeq.begin(); it != elimSeq.end(); ++it) {
        cout << it->getID() << " ";
    }
    cout << "Winner: ";
    l.printAll();
    cout << endl;
}
