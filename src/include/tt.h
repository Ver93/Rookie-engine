#pragma once
#include <cstdint>
#include "move.h"

namespace TranspositionTable {

    struct TTEntry {
        uint64_t key;
        int depth;
        int score;
        int flag;
        Move bestMove;
    };

    enum TTFlag {
        EXACT,
        LOWERBOUND,
        UPPERBOUND
    };

    extern TTEntry* TT;
    extern size_t TT_SIZE;

    void initTT(size_t sizeMB);
    TTEntry* probeTT(uint64_t key);
    void storeTT(uint64_t key, int depth, int score, int flag, Move bestMove);
}
