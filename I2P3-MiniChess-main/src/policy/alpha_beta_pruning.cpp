#include <cstdlib>
#include <iostream>
#include <fstream>

#include "../state/state.hpp"
#include "./alpha_beta_pruning.hpp"

using namespace std;

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move ALPHA_BETA_PRUNING::get_move(State *state, int alpha, int beta, int depth){
    //std::ofstream debugg("ehe.txt");
    if(!state->legal_actions.size())
        state->get_legal_actions();
    
    auto actions = state->legal_actions;
    Move choosen;
    
    // int value = -9999,target;
    // for (auto it: actions){
    //     State* new_s = state->next_state(it);
    //     /*if (state->player == 0)*/ target = minimax_recur(new_s, alpha, beta,depth - 1, false,state->player);
    //     //else target = minimax_recur(new_s, alpha, beta, depth - 1, true, state->player);
    //     if (value < target){
    //         value = target;
    //         choosen = it;
    //     }
    //     //debugg << value << endl;
        
    // }
    //------------------------------------------------------------------------------------------------------------------
    int value = -9999, target;
    for (auto it: actions){
        State* new_s = state->next_state(it);
        target = minimax_recur(new_s, alpha, beta,depth - 1, false,state->player);
        if (value < target){
            value = target;
            choosen = it;
        }
        if (alpha < value) alpha = value;

        
    }
    //-------------------------------------------------------------------------------------------------------------------
    // if (state->player == 0){
    //     int value = -9999,target;
    //     for (auto it: actions){
    //         State* new_s = state->next_state(it);
    //         target = minimax_recur(new_s, alpha, beta, depth - 1, false, state->player);
    //         if (value < target){
    //             value = target;
    //             choosen = it;
    //         }
    //     }     
    // }else{
    //     int value = 9999;
    //     for (auto it: actions){
    //         State* new_s = state->next_state(it);
    //         int target = minimax_recur(new_s, alpha, beta, depth - 1, true, state->player);
    //         if (value > target){
    //             value = target;
    //             choosen = it;
    //         }
    //     }
    // }
    
    return choosen;
}

int ALPHA_BETA_PRUNING::minimax_recur(State *state, int alpha, int beta, int depth, bool MaxOrMin, int MyPlayer){                  //1 -> MAX ~~~~~~~~~ 0 -> MIN

    
    auto actions = state->legal_actions;
    if (MaxOrMin){
        if (depth == 0){
            // if (MyPlayer) return -state->evaluate();
            // else return (state->evaluate());
            return state->evaluate();
        }
        if (state->game_state == WIN){
            return state->evaluate() + 900;
        }
        int value = -9999;
        for (auto it : actions){
            State* new_s = state->next_state(it);
            int target = minimax_recur(new_s, alpha, beta , depth - 1, !MaxOrMin, MyPlayer);
            value = max(value, target);
            // if (value < target){
            //     value = target;
            // }
            if (alpha < value) alpha = value;
            if (beta <= alpha) break;
        }
        return value;
    }
    else{
        if (depth == 0){
            // if (MyPlayer) return -state->evaluate();
            // else return (state->evaluate());
            State* new_s = new State(state->board, !state->player);
            return new_s->evaluate();
        }
        if (state->game_state == WIN){
            return state->evaluate() - 900;
        }
        int value = 9999;
        for (auto it : actions){
            State* new_s = state->next_state(it);
            int target = minimax_recur(new_s, alpha, beta, depth - 1, !MaxOrMin, MyPlayer);
            value = min(value, target);
            // if (value > target){
            //     value = target;
            // }
            if (beta > value) beta = value;
            if (beta <= alpha) break;
        }
        return value;
    }
}