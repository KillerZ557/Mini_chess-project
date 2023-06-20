#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move MINIMAX::get_move(State *state, int depth){
    if(!state->legal_actions.size())
        state->get_legal_actions();
    
    auto actions = state->legal_actions;
    Move choosen;
    
    // int value = -9999999,target;
    // for (auto it: actions){
    //     State* new_s = state->next_state(it);
    //     if (state->player == 0) target = minimax_recur(new_s, depth - 1, false);
    //     else target = minimax_recur(new_s, depth - 1, true);
    //     if (value < target){
    //         value = target;
    //         choosen = it;
    //     }
    // }
    if (state->player == 0){
        int value = -9999999,target;
        for (auto it: actions){
            State* new_s = state->next_state(it);
            target = minimax_recur(new_s, depth - 1, false);
            if (value < target){
                value = target;
                choosen = it;
            }
        }
    }else{
        int value = 9999999;
        for (auto it: actions){
            State* new_s = state->next_state(it);
            int target = minimax_recur(new_s, depth - 1, true);
            if (value > target){
                value = target;
                choosen = it;
            }
        }
    }
    
    return choosen;
}

int MINIMAX::minimax_recur(State *state, int depth, bool MaxOrMin){                  //1 -> MAX ~~~~~~~~~ 0 -> MIN
    
    //if (state->game_state == WIN) return 999999;
    if (depth <= 0 || state->game_state == WIN){
        return state->evaluate();
    }
    if(!state->legal_actions.size()) state->get_legal_actions();
    auto actions = state->legal_actions;
    if (MaxOrMin){
        int value = -9999999;
        for (auto it : actions){
            State* new_s = state->next_state(it);
            int target = minimax_recur(new_s, depth - 1, false);
            if (value < target){
                value = target;
            }
        }
        return value;
    }
    else{
        int value = 9999999;
        for (auto it : actions){
            State* new_s = state->next_state(it);
            int target = minimax_recur(new_s, depth - 1, true);
            if (value > target){
                value = target;
            }
        }
        return value;
    }
}