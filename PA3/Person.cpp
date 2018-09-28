//
//  Person.cpp
//  
//
//  Created by Albert Wu on 9/13/18.
//

#include "Person.h"

Person::Person(int position) {
    this->position = position;
}
int Person::getID() {
    return this->position;
}

