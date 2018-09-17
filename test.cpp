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

    a.state.execute_move("P 4 4", 2);
    a.state.execute_move("P 0 0", 1);
    a.state.execute_move("P 3 11", 2);
    a.state.execute_move("P 1 0", 1);
    a.state.execute_move("P 1 3", 2);
    a.state.execute_move("P 1 1", 1);
    a.state.execute_move("P 4 2", 2);
    a.state.execute_move("P 1 2", 1);
    a.state.execute_move("P 2 9", 2);
    a.state.execute_move("P 1 4", 1);
    a.state.execute_move("S 4 2 M 2 4", 2);
    a.state.execute_move("S 0 0 M 1 5", 1);
    a.state.execute_move("S 2 4 M 3 10", 2);
    a.state.execute_move("S 1 5 M 2 11", 1);
    a.state.execute_move("S 3 11 M 5 19", 2);
    a.state.execute_move("S 2 11 M 3 17", 1);
    a.state.execute_move("S 2 9 M 2 8", 2);
    a.state.execute_move("S 3 17 M 4 23", 1);
    a.state.execute_move("S 5 19 M 4 15", 2);
    a.state.execute_move("S 4 23 M 5 29", 1);
    a.state.execute_move("S 4 15 M 4 14", 2);
    a.state.execute_move("S 5 29 M 4 0 RE 1 5 RS 5 29 X 1 4", 1);
    a.state.execute_move("S 3 10 M 3 12", 2);

    string move = a.get_next_move();
    return 0;
}