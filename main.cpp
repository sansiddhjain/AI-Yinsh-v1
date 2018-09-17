#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include "Board.h"
#include "Agent.h"

using namespace std;

// Sample C++ Code
int main(int argc, char** argv) {

    int player_id, board_size, time_limit;
    string move;
    // Get input from server about game specifications
    cin >> player_id >> board_size >> time_limit;
    Agent a(player_id, board_size, time_limit, 'o', 'b');

    if(player_id == 2) {
        // Get other player's move
        while(move == "") {
            getline(cin, move);
        }
        a.execute_move(move, 2);

//        cerr << "1 " << move << "\n";
        while(true) {
            move = a.get_next_move();
            a.execute_move(move, 1);
            cout << move << endl;
            move.clear();
            while(move == "") {
                getline(cin, move);
            }
            a.execute_move(move, 2);
//            cerr << "2 " << move << "\n";
        }
    }
    else if(player_id == 1) {
        while(true) {
            move = a.get_next_move();
            a.execute_move(move, 1);
            move.clear();
            while(move == "") {
                getline(cin, move);
            }
            a.execute_move(move, 2);
//            cerr << "3 " << move << "\n";
        }
    }
    return 0;
}

//int main(int argc, char ** argv){
//
//    Agent a(1, 5, 120, 'o', 'b');
////    cout << a.state.game_board.at(0).at(0).is_piece() << "\n";
////    // a.state.execute_move("S 1 2 M 4 5 RS 3 4 RE 7 6");
//////    bool x1 = a.state.place_piece('r', make_pair(0,3));
//////    bool x2 = a.state.place_piece('r', make_pair(0, 3));
//////    bool x3 = a.state.place_piece('r', make_pair(0, 0));
//////    bool x4 = a.state.remove_piece(make_pair(0,0));
//////
//////    a.state.move_ring(make_pair(0,3), make_pair(1,3), false);
//////    a.state.move_ring(make_pair(1,3), make_pair(2,3), false);
//////    a.state.move_ring(make_pair(2,3), make_pair(3,3), false);
//////    a.state.move_ring(make_pair(3,3), make_pair(4,3), false);
//////    a.state.move_ring(make_pair(4,3), make_pair(4,2), false);
////
////    a.state.place_piece('r', make_pair(1, -1));
////
////
//////    bool x7 = a.state.move_ring(make_pair(0,2), make_pair(2,2), false);
////
//////    a.state.delete_row(pair<int,int> (0,3), pair<int,int> (4,3));
////
////    vector<pair<int,int>> succ = a.state.successors(make_pair(1,3));
////    auto y1 = a.state.hex_to_xy(make_pair(5,18));
////    auto y2 = a.state.xy_to_hex(make_pair(4,3));
//
//    a.state.place_piece('m', 'o', make_pair(0,0));
//    a.state.place_piece('m', 'o', make_pair(0,1));
//    a.state.place_piece('m', 'o', make_pair(0,2));
//    a.state.place_piece('m', 'o', make_pair(0,3));
//    a.state.place_piece('m', 'o', make_pair(0,4));
//    a.state.place_piece('m', 'o', make_pair(0,-1));
//
//    a.state.place_piece('m', 'o', make_pair(-1,-1));
//    a.state.place_piece('m', 'o', make_pair(1,1));
//    a.state.place_piece('m', 'o', make_pair(2,2));
//    a.state.place_piece('m', 'o', make_pair(3,3));
//
//    a.state.place_piece('m', 'o', make_pair(-5,-4));
//    a.state.place_piece('m', 'o', make_pair(-4,-4));
//    a.state.place_piece('m', 'o', make_pair(-3,-4));
//    a.state.place_piece('m', 'o', make_pair(-2,-4));
//    a.state.place_piece('m', 'o', make_pair(-1,-4));
//
//
//    vector<pair<pair<int,int>, pair<int,int>>> rows = a.state.get_marker_rows(4);
//
//
//
//
//
//
//
//
//
//    return 0;
//}
