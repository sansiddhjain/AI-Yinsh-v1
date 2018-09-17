//
// Created by karthik on 13/9/18.
//

#include <string>
#include <cmath>
#include <algorithm>
#include "Agent.h"

using namespace std;

void Agent::execute_move(string move, int playerID) {
    state.execute_move(move, playerID);
}

// Copy state to state_tree
void Agent::copy_board()
{
  // = operator copies maps and copies vectors
  state_tree.game_board = state.game_board;
  state_tree.num_rings_on_board = state.num_rings_on_board;
  state_tree.num_opp_rings_on_board = state.num_opp_rings_on_board;
  state_tree.rings_vector = state.rings_vector;
  state_tree.opp_rings_vector = state.opp_rings_vector;

}

// Simple scoring function based on Slovenian guy recommendation #2
int Agent::score_function(vector< pair< pair<int,int>, pair<int,int> > > vec)
{
  vector< pair< pair<int,int>, pair<int,int> > >::iterator ptr;

  double result = 0;
  for (ptr = vec.begin(); ptr < vec.end(); ptr++)
  {
    pair< pair<int,int>, pair<int,int> > tuple = *ptr;
    pair<int, int> start = tuple.first;
    pair<int, int> end = tuple.second;
    if (start.first == end.first) // x coordinate same case
      result += pow(3.0, (fabs(end.second - start.second) + 1) ) - 1;
    else if (start.second == end.second) // y coordinate same case
      result += pow(3.0, (fabs(end.first - start.first) + 1) ) - 1;
    else // x - y = k
      result += pow(3.0, (fabs(end.first - start.first) + 1) ) - 1;
    // Can think of combining else and else if
  }
  return 0.5*result;
}

// Calculate score of player, subtract score of opponent
int Agent::calculate_score(Board board)
{
  vector< pair< pair<int,int>, pair<int,int> > > player_markers = board.get_marker_rows(1, board.player_color);
  vector< pair< pair<int,int>, pair<int,int> > > opp_markers = board.get_marker_rows(1, board.other_color);
  return score_function(player_markers) - score_function(opp_markers);
}

// Recursively construct tree normally
void Agent::recursive_construct_tree(Board board, Node* node, int depth, int maxDepth)
{
  // node->score = calculate_score(board);
  // if (depth == 0) { node->move = nullptr;}
  if (depth < maxDepth) //Can tune this 4 parameter
  {
    node->isLeaf = false;
    vector< pair< pair<int,int>, pair<int,int> > > succ_all;
    if (depth % 2 == 0) //Self player is playing
    {
      node->type = 'M';
      for (int i = 0; i < state.num_rings_on_board; i++)
      {
          vector< pair< pair<int,int>, pair<int,int> > > succ_ring = board.successors(board.rings_vector.at(i));
          succ_all.insert(succ_all.end(), succ_ring.begin(), succ_ring.end());
      }
    }
    else //Opponent is playing
    {
      node->type = 'm';
      for (int i = 0; i < state.num_opp_rings_on_board; i++)
      {
          vector< pair< pair<int,int>, pair<int,int> > > succ_ring = board.successors(board.opp_rings_vector.at(i));
          succ_all.insert(succ_all.end(), succ_ring.begin(), succ_ring.end());
      }
    }
    node->children = new Node*[succ_all.size()];
    vector< pair< pair<int,int>, pair<int,int> > >::iterator ptr;
    int idx = 0;
    for (ptr = succ_all.begin(); ptr < succ_all.end(); ptr++)
    {
      pair< pair<int,int>, pair<int,int> > move = *ptr;
      node->children[idx]->move = move;
      bool b = board.move_ring(move.first, move.second);
      if (b)
      {
        recursive_construct_tree(board, node->children[idx], depth+1, maxDepth);
        b = board.move_ring(move.second, move.first);
      }
      idx++;
    }
  }
  else{
    node->isLeaf = true;
    node->score = calculate_score(board);
  }
}

// Recursively construct tree with history heuristic
// Node* Agent::recursive_construct_tree_hh(Board board, int depth){}


string Agent::get_next_move() {
    // IMPORTANT - Also executes next move
    if ((state->num_rings_on_board < state.return_m()) & (state->num_markers == 0))
    {
      // Perform placement of ring
      return "P _ _";
    }
    copy_board();
    Node* tree;
    recursive_construct_tree(state_tree, tree, 0, 4);
    int trash = minimax(tree);
    pair< pair<int, int>, pair<int, int> > move = tree->children[tree->gotoidx]->move;
    bool b = state.move_ring(move.first, move.second);
    // convert to string to send to server
    vector< pair< pair<int,int>, pair<int,int> > > five_or_more = state.get_marker_rows(5, state.player_color);
    move.first = state.xy_to_hex(move.first);
    move.second = state.xy_to_hex(move.second);
    if (five_or_more.size() == 0)
    {
      string output = "S";
      output += " " + to_string(move.first.first);
      output += " " + to_string(move.first.second);
      output += " M";
      output += " " + to_string(move.second.first);
      output += " " + to_string(move.second.second);
      return output;
    }
    else
    {
      pair< pair<int,int>, pair<int,int> > tuple = five_or_more.at(1);
      pair<int, int> start = tuple.first;
      pair<int, int> end = tuple.second;
      if (start.first == end.first) // x coordinate same case
      {
        if (end.second > start.second)
          end.second = start.second+4;
        else
          end.second = start.second-4;
      }
      else if (start.second == end.second) // y coordinate same case
      {
        if (end.first > start.first)
          end.first = start.first+4;
        else
          end.second = start.first-4;
      }
      else // x - y = k
      {
        if ((end.first > start.first) & (end.second > start.second))
        {
          end.first = start.first+4;
          end.second = start.second+4;
        }
        else if ((end.first > start.first) & (end.second < start.second))
        {
          end.first = start.first+4;
          end.second = start.second-4;
        }
        else if ((end.first < start.first) & (end.second < start.second))
        {
          end.first = start.first-4;
          end.second = start.second-4;
        }
        else
        {
          end.first = start.first-4;
          end.second = start.second+4;
        }
      }
      // Output string waala part
      string output = "S";
      output += " " + to_string(move.first.first);
      output += " " + to_string(move.first.second);
      output += " M";
      output += " " + to_string(move.second.first);
      output += " " + to_string(move.second.second);
      output += " RE";
      output += " " + to_string(start.first);
      output += " " + to_string(start.second);
      output += " RS";
      output += " " + to_string(end.first);
      output += " " + to_string(end.second);
      output += " X";
      pair<int, int> ring = state.rings_vector.at(state.num_rings_on_board-1);
      bool b = state.remove_piece(ring);
      output += " " + to_string(ring.first);
      output += " " + to_string(ring.second);
      return output;
    }
}

// Vanilla minimax
int Agent::minimax(Node* node) {
    if (node->isLeaf) { return node->score;}
    if (node->type == 'M') // MAX node
    {
        int max_score = 0;
        int max_idx = 0;
        size_t n = sizeof(node->children)/sizeof(node->children[0]);
        for (int i = 0; i < n; i++)
        {
          if ( minimax(node->children[i]) > max_score )
          {
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
        int min_score = node->children[0]->score;
        int min_idx = 0;
        size_t n = sizeof(node->children)/sizeof(node->children[0]);
        for (int i = 0; i < n; i++)
        {
          if ( minimax(node->children[i]) < min_score )
          {
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

bool Agent::check_won(){
    return state.num_rings_on_board == (state.return_m() - state.return_l());
}
