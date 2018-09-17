//
// Created by karthik on 13/9/18.
//

#include <string>
#include <cmath>
#include <algorithm>
#include "Agent.h"
#include <iostream>

using namespace std;

void Agent::execute_move(string move, int playerID) {
    state.execute_move(move, playerID);
}

// Copy state to state_tree
void Agent::copy_board() {
    // = operator copies maps and copies vectors
    state_tree.game_board = state.game_board;
    state_tree.num_rings_on_board = state.num_rings_on_board;
    state_tree.num_opp_rings_on_board = state.num_opp_rings_on_board;
    state_tree.rings_vector = state.rings_vector;
    state_tree.opp_rings_vector = state.opp_rings_vector;

}

// Simple scoring function based on Slovenian guy recommendation #2
double Agent::score_function(vector<pair<pair<int, int>, pair<int, int> > > vec) {
    vector<pair<pair<int, int>, pair<int, int> > >::iterator ptr;

    double result = 0;
    for (ptr = vec.begin(); ptr < vec.end(); ptr++) {
        pair<pair<int, int>, pair<int, int> > tuple = *ptr;
        pair<int, int> start = tuple.first;
        pair<int, int> end = tuple.second;
        if (start.first == end.first) // x coordinate same case
            result += pow(3.0, (fabs(end.second - start.second) + 1)) - 1;
        else if (start.second == end.second) // y coordinate same case
            result += pow(3.0, (fabs(end.first - start.first) + 1)) - 1;
        else // x - y = k
            result += pow(3.0, (fabs(end.first - start.first) + 1)) - 1;
        // Can think of combining else and else if
    }
    return 0.5 * result;
}

// Calculate score of player, subtract score of opponent
double Agent::calculate_score(Board board) {
    vector<pair<pair<int, int>, pair<int, int> > > player_markers = board.get_marker_rows(1, board.player_color);
    vector<pair<pair<int, int>, pair<int, int> > > opp_markers = board.get_marker_rows(1, board.other_color);
    double score = score_function(player_markers) - score_function(opp_markers);
    vector<pair<pair<int, int>, pair<int, int> > > five_or_more = state.get_marker_rows(5, state.player_color);
    if (!five_or_more.empty())
      score += 100000;
    five_or_more = state.get_marker_rows(5, state.other_color);
    if (!five_or_more.empty())
      score += -100000;
}

// Recursively construct tree normally
void Agent::recursive_construct_tree(Board board, Node *node, int depth, int maxDepth) {
    // node->score = calculate_score(board);
    // if (depth == 0) { node->move = nullptr;}
//  cerr << "Entered fn" << endl;
    if (depth < maxDepth) //Can tune this 4 parameter
    {
        node->isLeaf = false;
        vector<pair<pair<int, int>, pair<int, int> > > succ_all;
        if (depth % 2 == 0) //Self player is playing
        {
//        cerr << "self" << endl;
            node->type = 'M';
            for (int i = 0; i < state.num_rings_on_board; i++) {
                pair<pair<int,int>,pair<int,int>> temp = make_pair(make_pair(-1,-1), make_pair(-1,0));
                vector<pair<pair<int, int>, pair<int, int> > > succ_ring = board.successors(board.rings_vector.at(i));
                succ_all.reserve(succ_all.size() + succ_ring.size());
//          cerr << "successors of ring # " << i + 1 << " - " << succ_ring.size() << '\n';
//          cerr << "all successors seen till now - " << succ_all.size() << '\n';
                succ_all.insert(succ_all.end(), succ_ring.begin(), succ_ring.end());
            }
        }
        else //Opponent is playing
        {
//            cerr << "opp" << endl;
            node->type = 'm';
            for (int i = 0; i < state.num_opp_rings_on_board; i++) {
                vector<pair<pair<int, int>, pair<int, int> > > succ_ring = board.successors(board.opp_rings_vector.at(i));
                succ_all.reserve(succ_all.size() + succ_ring.size());
                succ_all.insert(succ_all.end(), succ_ring.begin(), succ_ring.end());
            }
        }
//    cerr << "Reached here, depth = " << depth << endl;
        node->children = new Node *[succ_all.size()];
//    std::cerr << "created node->children" << '\n';
        vector<pair<pair<int, int>, pair<int, int> > >::iterator ptr;
//    std::cerr << "created iterator" << '\n';
        int idx = 0;
//    std::cerr << "going inside loop for all children" << '\n';
        for (ptr = succ_all.begin(); ptr != succ_all.end(); ptr++) {
            pair<pair<int, int>, pair<int, int> > move = *ptr;
//      std::cerr << move.first.first << ", " << move.first.second << "; " << move.second.first << ", " << move.second.second << '\n';
//      std::cerr << "Entered loop" << '\n';
            node->children[idx] = new Node;
            node->children[idx]->move = move;
//      std::cerr << "assigned child " << idx << "its corresponding move" << '\n';
            Board b(board);
            bool c = b.move_ring(move.first, move.second);
//      std::cerr << "performed move" << '\n';
            if (c) {
                recursive_construct_tree(b, node->children[idx], depth + 1, maxDepth);
//                c = board.move_ring(move.second, move.first);
            }
            idx++;
        }
    }
    else {
        node->isLeaf = true;
        node->score = calculate_score(board);
    }
}

// Recursively construct tree with history heuristic
// Node* Agent::recursive_construct_tree_hh(Board board, int depth){}

string Agent::initial_move() {
    //todo: change strategy, also executes_move
    // for now just place near centre, first move on centremost hexagons going clockwise
    string move;
    if (!state.game_board.at(0).at(0).is_piece()) {
        state.place_piece('r', state.player_color, pair<int, int>(0, 0));
        return "P 0 0 ";
    }
    for (int j = 0; j < n; j++) {
        pair<int, int> pos_xy = state.hex_to_xy(pair<int, int>(1, j));
        if (!state.game_board.at(pos_xy.first).at(pos_xy.second).is_piece()) {
            state.place_piece('r', state.player_color, pair<int, int>(pos_xy.first, pos_xy.second));
            return "P 1 " + to_string(j);
        }
    }
    for (int j = 0; j < 2 * n; j++) {
        pair<int, int> pos_xy = state.hex_to_xy(pair<int, int>(2, j));
        if (!state.game_board.at(pos_xy.first).at(pos_xy.second).is_piece()) {
            state.place_piece('r', state.player_color, pair<int, int>(pos_xy.first, pos_xy.second));
            return "P 2 " + to_string(j);
        }
    }
}


string Agent::get_next_move() {
    // IMPORTANT - Also executes next move
    if ((state.num_rings_on_board < state.return_m()) & (state.num_markers == 0)) {
        // Perform placement of ring
        state.num_moves_played++;
        return initial_move();
    }
    state_tree = Board(state);
    Node *tree = new Node;
    tree->type = 'M';
//    cerr << "22@" << endl;
    if (state.num_moves_played < 16) {
//        cerr << "DEPTH 2" << endl;
        minimax_ab(state_tree, tree, 0, -INFINITY, INFINITY, 2);
//        recursive_construct_tree(state_tree, tree, 0, 2);

    }
    else if (state.num_moves_played < 22) {
//        cerr << "DEPTH 3" << endl;
        minimax_ab(state_tree, tree, 0, -INFINITY, INFINITY, 3);
//        recursive_construct_tree(state_tree, tree, 0, 3);
    }
    else {
//        cerr << "DEPTH 4" << endl;
        minimax_ab(state_tree, tree, 0, -INFINITY, INFINITY, 4);
//        recursive_construct_tree(state_tree, tree, 0,4);
    }
//    cerr << "111" <<endl;
//    int trash = minimax(tree);
    pair<pair<int, int>, pair<int, int> > move = tree->children[tree->gotoidx]->move;
    std::cerr << move.first.first << ", " << move.first.second << "; " << move.second.first << ", "
              << move.second.second << '\n';
    bool b = state.move_ring(move.first, move.second);
    // convert to string to send to server
    vector<pair<pair<int, int>, pair<int, int> > > five_or_more = state.get_marker_rows(5, state.player_color);
    move.first = state.xy_to_hex(move.first);
    move.second = state.xy_to_hex(move.second);
    if (five_or_more.empty()) {
        string output = "S";
        output += " " + to_string(move.first.first);
        output += " " + to_string(move.first.second);
        output += " M";
        output += " " + to_string(move.second.first);
        output += " " + to_string(move.second.second);
        state.num_moves_played++;
        return output;
    }
    else {
        // todo: determine strategy to remove markers if multiple are formed
        pair<pair<int, int>, pair<int, int> > tuple = five_or_more.at(0);
        pair<int, int> start = tuple.first;
        pair<int, int> end = tuple.second;
        if (start.first == end.first) // x coordinate same case
        {
            if (end.second > start.second)
                end.second = start.second + 4;
            else
                end.second = start.second - 4;
        }
        else if (start.second == end.second) // y coordinate same case
        {
            if (end.first > start.first)
                end.first = start.first + 4;
            else
                end.second = start.first - 4;
        }
        else // x - y = k
        {
            if ((end.first > start.first) & (end.second > start.second)) {
                end.first = start.first + 4;
                end.second = start.second + 4;
            }
            else if ((end.first > start.first) & (end.second < start.second)) {
                end.first = start.first + 4;
                end.second = start.second - 4;
            }
            else if ((end.first < start.first) & (end.second < start.second)) {
                end.first = start.first - 4;
                end.second = start.second - 4;
            }
            else {
                end.first = start.first - 4;
                end.second = start.second + 4;
            }
        }
        bool trash = state.delete_row(start, end);
        start = state.xy_to_hex(start);
        end = state.xy_to_hex(end);
        // Output string waala part
        string output = "S";
        output += " " + to_string(move.first.first);
        output += " " + to_string(move.first.second);
        output += " M";
        output += " " + to_string(move.second.first);
        output += " " + to_string(move.second.second);
        output += " RS";
        output += " " + to_string(start.first);
        output += " " + to_string(start.second);
        output += " RE";
        output += " " + to_string(end.first);
        output += " " + to_string(end.second);
        output += " X";
        //todo: figure out which ring to removes
        pair<int, int> ring = state.rings_vector.at(state.num_rings_on_board - 1);
        bool b = state.remove_piece(ring);
        ring = state.xy_to_hex(ring);
        output += " " + to_string(ring.first);
        output += " " + to_string(ring.second);
        state.num_moves_played++;
        return output;
    }
}

// Vanilla minimax
double Agent::minimax(Node *node) {
    if (node->isLeaf) { return node->score; }
    if (node->type == 'M') // MAX node
    {
        double max_score = 0;
        int max_idx = 0;
        size_t n = sizeof(node->children) / sizeof(node->children[0]);
        for (int i = 0; i < n; i++) {
            if (minimax(node->children[i]) > max_score) {
                max_score = node->children[i]->score;
                max_idx = i;
            }
        }
        node->score = max_score;
        node->gotoidx = max_idx;
        return max_score;
    }
    else // MIN node
    {
        double min_score = node->children[0]->score;
        int min_idx = 0;
        size_t n = sizeof(node->children) / sizeof(node->children[0]);
        for (int i = 0; i < n; i++) {
            if (minimax(node->children[i]) < min_score) {
                min_score = node->children[i]->score;
                min_idx = i;
            }
        }
        node->score = min_score;
        node->gotoidx = min_idx;
        return min_score;
    }
}
// Minimax with Alpha Beta Pruning
// void minimax_ab() {}


double Agent::minimax_ab(Board board, Node *node, int depth, double alpha, double beta, int maxDepth) {
    if (depth == maxDepth)
        return calculate_score(board);
    else {
        node->isLeaf = false;
        vector<pair<pair<int, int>, pair<int, int> > > succ_all;
        if (depth % 2 == 0) {//Self player is playing
            node->type = 'M';
            for (int i = 0; i < state.num_rings_on_board; i++) {
                vector<pair<pair<int, int>, pair<int, int> > > succ_ring = board.successors(board.rings_vector.at(i));
                succ_all.reserve(succ_all.size() + succ_ring.size());
                succ_all.insert(succ_all.end(), succ_ring.begin(), succ_ring.end());
            }
        }
        else {//Opponent is playing
            node->type = 'm';
            for (int i = 0; i < state.num_opp_rings_on_board; i++) {
                vector<pair<pair<int, int>, pair<int, int> > > succ_ring = board.successors(board.opp_rings_vector.at(i));
                succ_all.reserve(succ_all.size() + succ_ring.size());
                succ_all.insert(succ_all.end(), succ_ring.begin(), succ_ring.end());
            }
        }

        node->children = new Node*[succ_all.size()];

        if(node->type == 'M') {
            double v = -INFINITY;
            for (int i = 0; i < succ_all.size(); i++) {
                node->children[i] = new Node;
                node->children[i]->move = succ_all[i];
                node->children[i]->type == 'm';
                Board temp_board(board);
                temp_board.move_ring(succ_all[i].first, succ_all[i].second);
                double v_prime = minimax_ab(temp_board, node->children[i], depth + 1, v, beta, maxDepth);
                if(v_prime > v){
                    v = v_prime;
                    node->gotoidx = i;
//                    node->children[i]->score = v_prime;
//                    node->gotoidx = i;
                }
                alpha = max(alpha, v);
                if (alpha >= beta)
                    break;
            }
            return v;
        }
        else {
            double v = INFINITY;
            for (int i = 0; i < succ_all.size(); i++) {
                node->children[i] = new Node;
                node->children[i]->move = succ_all[i];
                node->children[i]->type = 'M';
                Board temp_board(board);
                temp_board.move_ring(succ_all[i].first, succ_all[i].second);
                double v_prime = minimax_ab(temp_board, node->children[i], depth + 1, alpha, v, maxDepth);
                if(v_prime < v) {
                    v = v_prime;
//                    node->children[i]->score = v_prime;
                    node->gotoidx = i;
                }
                beta = min(beta, v);
                if (alpha >= beta)
                    break;
            }
            return v;
        }
    }
}

/*
 * function alphabeta(node, α, β, maximizingPlayer)
        if node is a terminal node
            return { value: value of node, node : node}
        if maximizingPlayer
            v = -∞
            bestNode = None
            for each child of node
                localMax = alphabeta(child, α, β, FALSE)
                if localMax.value > v
                    v = localMax.value
                    bestNode = localMax.node

                α = max(α, v)
                if β ≤ α
                    break
            return {value : v, node: bestNode}
 */



/*
 * fun minimax(n: node, d: int, min: int, max: int): int =
   if leaf(n) or depth=0 return evaluate(n)
   if n is a max node
      v := min
      for each child of n
         v' := minimax (child,d-1,v,max)
         if v' > v, v:= v'
         if v > max return max
      return v
   if n is a min node
      v := max
      for each child of n
         v' := minimax (child,d-1,min,v)
         if v' < v, v:= v'
         if v < min return min
      return v
 */




bool Agent::check_won() {
    return state.num_rings_on_board == (state.return_m() - state.return_l());
}
