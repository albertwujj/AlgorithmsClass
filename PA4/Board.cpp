//
//  Board.cpp
//  DSA_Xcode
//
//  Created by Albert Wu on 10/15/18.
//

#include "Board.hpp"

Board::Board(int m): xmap(), idmap() {
    this->m = m;
    this->n = 0;
}

bool Board::insert(int id, int x, int y) {
    if (x > m || y > m || x <= 0 || y <= 0) {
        cout << "Error: out of bounds" << endl;
        return false;
    }
    if (this->n == this->m) {
        cout << "Error: n would exceed m" << endl;
        return false;
    }
    if (this->idmap.count(id)) { //if idmap contains id
        cout << "Error: id " << id << " already exists" << endl;
        return false;
    }

    //insert in position if unoccupied
    if (this->xmap[x].count(y)) {
        cout << "Error: position already occupied for insert id: " << id << endl;
        return false;
    } else {
        this->xmap[x][y] = id;
    }
    Player player(id, x, y);
    this->idmap[id] = player;
    this->n++;
    return true;
}

bool Board::remove(int id) {
    if(!this->idmap.count(id)) {
        cout << "Error: id " << id << " not found" << endl;
        return false;
    }

    Player player = idmap[id];
    int x = player.x;
    int y = player.y;
    this->xmap[x].erase(y);
    int i = this->idmap.erase(id);
    this->n--;
    return true;
}

bool Board::find(int id) {
    return this->idmap.count(id);
}

bool Board::moveTo(int id, int x_new, int y_new) {
    if(!this->idmap.count(id)) {
        cout << "Error: id " << id << " not found" << endl;
        return false;
    }
    Player player = idmap[id];
    int x = player.x;
    int y = player.y;
    if (x > m || y > m || x <= 0 || y <= 0)  {
        cout << "Error: out of bounds" << endl;
        return false;
    }
    //check for move along row, column, or diagonal
    if (x != x_new && y != y_new && std::abs( (int) (x-x_new)) !=  std::abs((int) (y-y_new))) {
        cout << "Error: invalid movement for id " << id << endl;
        return false;
    }

    //remove previous item in new position (if any)
    if (this->xmap[x_new].count(y_new)) { //if ymap contains y
        int prev_id = xmap[x_new][y_new];
        this->idmap.erase(prev_id);
        this->xmap[x_new].erase(y_new);
        this->n--;
    }

    //remove and insert into new position
    this->remove(id);
    this->insert(id, x_new, y_new);

    return true;
}

void Board::printByID() {
    cout << "Printing by ID:" << endl;
    for (std::map<int, Player>::iterator i = this->idmap.begin(); i != this->idmap.end(); i++) {
        int id = i->first;
        Player player = i->second;
        int x = player.x;
        int y = player.y;
        cout << "ID: " << id << "\n(x,y): (" << x << "," << y << ")\n\n";
    }
}
