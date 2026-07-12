#pragma once
#include <vector>
#include "move_gen.h"
#include "state.h"
#include "move.h"
#include "utils.h"
#include "undo.h"
#include "const.h"
#include "threat_gen.h"
#include "move_val.h"
#include "move_exec.h"


namespace LegalMove {
    std::vector<Move> generate(State& state);
    std::vector<Move> generateTactical(State& state);
}