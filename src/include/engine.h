#pragma once

#include "magics.h"
#include "perft.h"
#include "utils.h"
#include "state.h"
#include "search.h"

namespace Engine {
    void initialize();
    void reset();
    void setPosition(const std::string& fen);
    void makeMove();
    void findBestMove();
    void go(int depth);
    void perft(int depth);
    void applyMoves(const std::string& moves);
}