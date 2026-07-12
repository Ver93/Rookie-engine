#pragma once

#include <future>
#include <vector>
#include <cstring>
#include <memory>
#include <iostream>
#include <mutex>

#include "state.h"
#include "move_counter.h"
#include "threat_gen.h"
#include "move_gen.h"
#include "move_exec.h"
#include "move_val.h"
#include "move.h"
#include "undo.h"
#include "const.h"
#include "utils.h"

using PerftOutput = std::pair<long long, MoveCounter>;

namespace Perft {
    void countMoveType(const Move& move, MoveCounter& counter);
    void countCheckAndCheckmate(State& state, MoveCounter& counter);
    void dividePerft(int depth, State& state);
    int perft(int depth, State& state, MoveCounter& counters);
    PerftOutput perftTask(int depth, State& originalState, const Move& move);
}