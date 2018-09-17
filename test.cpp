//
// Created by karthik on 17/9/18.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include "Board.h"
#include "Agent.h"

using namespace std;

int main(int argc, char ** argv){

    Agent a(1, 5, 120, 'b', 'o');

    a.state.execute_move("P 4 0", 2);
    a.state.execute_move("P 0 0", 1);
    a.state.execute_move("P 5 27", 2);
    a.state.execute_move("P 1 0", 1);
    a.state.execute_move("P 2 0", 2);
    a.state.execute_move("P 1 1", 1);
    a.state.execute_move("P 5 24", 2);
    a.state.execute_move("P 1 2", 1);
    a.state.execute_move("P 3 1", 2);
    a.state.execute_move("P 1 3", 1);
    a.state.execute_move("S 2 0 M 2 2", 2);
    a.state.execute_move("S 0 0 M 1 5", 1);
    a.state.execute_move("S 5 27 M 5 26", 2);
    a.state.execute_move("S 1 5 M 2 11", 1);
    a.state.execute_move("S 2 2 M 2 4", 2);
    a.state.execute_move("S 2 11 M 3 17", 1);
    a.state.execute_move("S 5 24 M 5 21", 2);
    a.state.execute_move("S 3 17 M 4 23", 1);
    a.state.execute_move("S 2 4 M 2 3", 2);
    a.state.execute_move("S 4 23 M 5 29", 1);
    a.state.execute_move("S 4 0 M 4 2", 2);
    a.state.execute_move("S 5 29 M 1 4", 1);
    a.state.execute_move("S 3 1 M 5 7", 2);
    a.state.execute_move("S 1 4 M 2 7", 1);
    a.state.execute_move("S 2 3 M 4 5", 2);
    a.state.execute_move("S 2 7 M 3 10", 1);
    a.state.execute_move("S 5 7 M 5 6", 2);
    a.state.execute_move("S 3 10 M 4 13", 1);
    a.state.execute_move("S 5 6 M 4 3", 2);
    a.state.execute_move("S 4 13 M 5 16", 1);
    a.state.execute_move("S 4 5 M 4 6", 2);
    a.state.execute_move("S 5 16 M 5 17 RS 5 16 RE 1 4 X 1 3", 1);
    a.state.execute_move("S 5 26 M 5 19", 2);
    a.state.execute_move("S 5 17 M 4 14", 1);
    a.state.execute_move("S 4 2 M 3 2", 2);
    a.state.execute_move("S 4 14 M 3 11", 1);
    a.state.execute_move("S 4 6 M 4 4", 2);
    a.state.execute_move("S 3 11 M 2 8", 1);
    a.state.execute_move("S 4 3 M 3 3", 2);
    a.state.execute_move("S 2 8 M 2 9", 1);
    a.state.execute_move("S 5 21 M 3 13", 2);
    a.state.execute_move("S 2 9 M 2 10 RS 5 17 RE 2 9 X 1 2", 1);
    a.state.execute_move("S 3 3 M 5 12", 2);
    a.state.execute_move("S 2 10 M 3 16", 1);
    a.state.execute_move("S 5 12 M 2 6", 2);
    a.state.execute_move("S 3 16 M 4 22", 1);
    a.state.execute_move("S 2 6 M 3 10", 2);
    a.state.execute_move("S 4 22 M 5 28", 1);
    a.state.execute_move("S 5 19 M 5 18", 2);
    a.state.execute_move("S 5 28 M 2 9", 1);
    a.state.execute_move("RS 2 10 RE 4 2 X 3 13 S 5 18 M 4 14", 2);


//    Board b(a.state);
//    b.execute_move("S 3 12 M 3 13", 2);

    string move = a.get_next_move();
    return 0;
}