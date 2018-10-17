//
//  test_board.cpp
//  DSA_Xcode
//
//  Created by Albert Wu on 10/16/18.
//

#include "test_board.hpp"



int main() {

    Board b(1000000);    // specifies that the game board size is 1000000 x 1000000

    // the following is a sequence of calls to board class methods assuming
    //     the input example (m=10,n=8) given in the programming assignment.

    b.insert(1,3,2);    // assumed syntax: insert(ID, x, y)
    b.insert(2,4,3);
    b.insert(3,4,6);
    b.insert(4,5,7);
    b.insert(5,6,3);
    b.insert(6,8,2);
    b.insert(7,9,3);
    b.insert(8,9,8);

    b.insert(3,7,6);    // should fail because player 3 is already there

    b.insert(10,9,8);    // should fail because 9,8 is occupied already

    b.moveTo(4,9,3);    //assumed syntax: moveTo(ID,x,y) // removes 7 in the process
    b.printByID();

    b.moveTo(4,9,8);    // removes 8
    b.printByID();

    b.moveTo(4,6,3); // should fail because move to 6,3 is from 4's current position is not valid
    b.printByID();

    b.moveTo(2,3,3);
    b.printByID();

    b.moveTo(4,3,2);    // removes 1
    b.printByID();

    b.moveTo(4,8,2);    // removes 6
    b.printByID();

    b.moveTo(5,3,3);    // removes 2
    b.printByID();

    b.moveTo(4,4,6);    // removes 3
    b.printByID();

    b.moveTo(5,4,3);
    b.printByID();

    b.moveTo(4,4,3);    // removes 5
    b.printByID();

    // the code should print only one player at this stage which is player 4 @ (4,3)

}
