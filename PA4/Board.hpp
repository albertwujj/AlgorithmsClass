//
//  Board.hpp
//  DSA_Xcode
//
//  Created by Albert Wu on 10/15/18.
//

#ifndef Board_hpp
#define Board_hpp

#include <iostream>
#include <stdio.h>
#include <set>
#include <map>
#include <cmath>
#include <iterator>
#include "Player.hpp"

using std::cout;
using std::endl;

class Board {
public:
    Board(int m);
    bool insert(int id, int x, int y);
    bool remove(int id);
    bool find(int id);
    bool moveTo(int id, int x_new, int y_new);
    void printByID();

private:
    int m;
    int n;
    std::map<int, std::map<int, int> > xmap; // key is x, value is ymap
    //ymap is a map from y to id

    std::map<int, Player> idmap; //key is id, value is player
};


#endif /* Board_hpp */
