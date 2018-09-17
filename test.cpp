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
    a.state.execute_move("P 4 10", 2);
    a.state.execute_move("P 1 1", 1);
    a.state.execute_move("P 4 4", 2);
    a.state.execute_move("P 1 2", 1);
    a.state.execute_move("P 5 29", 2);
    a.state.execute_move("P 1 3", 1);
    a.state.execute_move("P 3 15", 2);
    a.state.execute_move("P 1 4", 1);
    a.state.execute_move("S 3 15 M 1 5", 2);
    a.state.execute_move("S 1 1 M 2 2", 1);
    a.state.execute_move("S 4 10 M 5 9", 2);
    a.state.execute_move("S 2 2 M 3 3", 1);
    a.state.execute_move("S 4 4 M 4 2", 2);
    a.state.execute_move("S 3 3 M 4 3", 1);
    a.state.execute_move("S 4 2 M 2 0", 2);



//    Board b(a.state);
//    b.execute_move("S 3 12 M 3 13", 2);

    string move = a.get_next_move();
    return 0;
}