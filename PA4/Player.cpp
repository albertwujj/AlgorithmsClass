//
//  Player.cpp
//  DSA_Xcode
//
//  Created by Albert Wu on 10/16/18.
//

#include "Player.hpp"

Player::Player() {
    this->id = 0;
    this->x = 0;
    this->y = 0;
}

Player::Player(int id, int x, int y) {
    this->id = id;
    this->x = x;
    this->y = y;
}

Player & Player::operator=(const Player & copy) {
    this->id = copy.id;
    this->x = copy.x;
    this->y = copy.y;
    return *this;
}
