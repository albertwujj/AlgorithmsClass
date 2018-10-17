//
//  Player.hpp
//  DSA_Xcode
//
//  Created by Albert Wu on 10/16/18.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>

#endif /* Player_hpp */

class Player {
public:
    Player();
    Player(int id, int x, int y);
    Player & operator=(const Player & copy);

private:
    friend class Board;
    int id;
    int x;
    int y;

};
