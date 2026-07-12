#pragma once

#include <vector>

#include "move.h"
#include "undo.h"
#include "state.h"
#include "move_gen.h"
#include "move_val.h"
#include "move_exec.h"
#include "threat_gen.h"
#include "evaluate.h"
#include "engine.h"
#include "move_order.h"
#include "legal_move.h"
#include "utils.h"

namespace Search {
    int alphaBeta(State& state, int depth, int alpha, int beta);
    Move findBestMove(State& state, int depth);
    // std::vector<Move> findBestMove(State& state, int depth);
}