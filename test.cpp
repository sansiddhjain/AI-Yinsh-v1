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

    a.state.execute_move("P 0 0", 2);
    a.state.execute_move("P 1 0", 1);
    a.state.execute_move("P 1 1", 2);
    a.state.execute_move("P 1 2", 1);
    a.state.execute_move("P 1 3", 2);
    a.state.execute_move("P 1 4", 1);
    a.state.execute_move("P 2 0", 2);
    a.state.execute_move("P 2 1", 1);
    a.state.execute_move("P 2 2", 2);
    a.state.execute_move("P 2 3", 1);
    a.state.execute_move("S 0 0 M 1 5", 2);
    a.state.execute_move("S 1 0 M 2 11", 1);
    a.state.execute_move("S 1 5 M 2 10", 2);
    a.state.execute_move("S 2 11 M 3 16", 1);
    a.state.execute_move("S 1 3 M 2 6", 2);
    a.state.execute_move("S 1 4 M 2 5", 1);
    a.state.execute_move("S 2 10 M 3 15", 2);
    a.state.execute_move("S 2 5 M 2 4", 1);
    a.state.execute_move("S 2 6 M 2 7", 2);
    a.state.execute_move("S 1 2 M 3 8", 1);
    a.state.execute_move("S 3 15 M 4 20", 2);
    a.state.execute_move("S 2 4 M 3 10", 1);
    a.state.execute_move("S 2 0 M 3 9", 2);
    a.state.execute_move("S 3 16 M 3 17", 1);
    a.state.execute_move("S 4 20 M 3 6 RS 2 6 RE 2 0 X 2 2", 2);
    a.state.execute_move("S 2 1 M 1 0", 1);
    a.state.execute_move("S 2 7 M 2 8", 2);
    a.state.execute_move("S 3 17 M 4 23", 1);
    a.state.execute_move("S 2 8 M 0 0", 2);
    a.state.execute_move("S 4 23 M 5 29", 1);
    a.state.execute_move("S 0 0 M 1 3", 2);
    a.state.execute_move("S 5 29 M 4 0 RS 1 5 RE 5 29 X 2 3", 1);
    a.state.execute_move("S 3 6 M 4 8", 2);
    a.state.execute_move("S 3 8 M 2 6", 1);
    a.state.execute_move("S 1 1 M 3 1", 2);
    a.state.execute_move("S 2 6 M 3 5", 1);
    a.state.execute_move("S 3 9 M 3 7 RS 3 8 RE 2 1 X 3 7", 2);
    a.state.execute_move("S 4 0 M 4 23", 1);
    a.state.execute_move("S 1 3 M 1 2", 2);
    a.state.execute_move("S 3 5 M 2 3", 1);
    a.state.execute_move("S 1 2 M 2 5", 2);
    a.state.execute_move("S 4 23 M 3 17", 1);
    a.state.execute_move("S 4 8 M 4 7", 2);
    a.state.execute_move("S 2 3 M 3 11", 1);
    a.state.execute_move("S 2 5 M 1 1", 2);

//    Board b(a.state);
//    b.execute_move("S 0 0 M 3 13", 2);

    string move = a.get_next_move();
    return 0;
}