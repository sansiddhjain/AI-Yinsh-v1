#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include "Board.h"
#include "Agent.h"

using namespace std;

// Sample C++ Code
//int main(int argc, char** argv) {
//
//    int player_id, board_size, time_limit;
//    string move;
//    // Get input from server about game specifications
//    cin >> player_id >> board_size >> time_limit;
//    cerr << player_id << " " << board_size << " " << time_limit << endl;
//    Agent a(player_id, board_size, time_limit, 'o', 'b');
//
//    if(player_id == 2) {
//        // Get other player's move
//        while(move.empty()) {
//            getline(cin, move);
//        }
////        cerr << "MOve " << move << endl;
//        a.execute_move(move, 2);
//
////        cerr << "1 " << move << "\n";
//        while(true) {
////            cerr << "Reached here" << endl;
//            move = a.get_next_move();
////            a.execute_move(move, 1);
//            cout << move << endl;
//            move.clear();
//            while(move == "") {
//                getline(cin, move);
//            }
//            a.execute_move(move, 2);
////            cerr << "2 " << move << "\n";
//        }
//    }
//    else if(player_id == 1) {
//        while(true) {
//            move = a.get_next_move();
////            a.execute_move(move, 1);
//            move.clear();
//            while(move == "") {
//                getline(cin, move);
//            }
//            a.execute_move(move, 2);
////            cerr << "3 " << move << "\n";
//        }
//    }
//    return 0;
//}

int main(int argc, char ** argv){

    Agent a(1, 5, 120, 'b', 'o');

    a.state.place_piece('r', 'b', pair<int,int>{0,0});
    a.state.place_piece('r', 'b', pair<int,int>{0,1});
    a.state.place_piece('r', 'b', pair<int,int>{1,1});
    a.state.place_piece('r', 'b', pair<int,int>{-1,-1});
    a.state.place_piece('r', 'b', pair<int,int>{0,2});

    a.state.place_piece('r', 'o', pair<int,int>{-1,0});
    a.state.place_piece('r', 'o', pair<int,int>{1,0});
    a.state.place_piece('r', 'o', pair<int,int>{0,-1});
    a.state.place_piece('r', 'o', pair<int,int>{1,-1});
    a.state.place_piece('r', 'o', pair<int,int>{-1,1});

    auto b = a.state.successors(pair<int,int>(0,0));
    string move = a.get_next_move();
    return 0;

}
