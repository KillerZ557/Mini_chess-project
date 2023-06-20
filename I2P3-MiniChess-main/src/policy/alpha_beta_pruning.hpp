#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class ALPHA_BETA_PRUNING{
public:
  static Move get_move(State *state, int alpha, int beta, int depth);
  static int minimax_recur(State *state, int alpha, int beta, int depth, bool MaxOrMin, int MyPlayer);
};