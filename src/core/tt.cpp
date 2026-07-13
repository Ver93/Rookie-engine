#include "tt.h"

namespace TranspositionTable {

    TTEntry* TT = nullptr;
    size_t TT_SIZE = 0;

    void initTT(size_t sizeMB) {
        TT_SIZE = (sizeMB * 1024 * 1024) / sizeof(TTEntry);
        TT = new TTEntry[TT_SIZE];

        for (size_t i = 0; i < TT_SIZE; i++) {
            TT[i].key = 0;
            TT[i].depth = -1;
            TT[i].score = 0;
            TT[i].flag = EXACT;
            TT[i].bestMove = Move{};
        }
    }

    TTEntry* probeTT(uint64_t key) {
        return &TT[key % TT_SIZE];
    }

    void storeTT(uint64_t key, int depth, int score, int flag, Move bestMove) {
        TTEntry* e = probeTT(key);

        if (depth >= e->depth) {
            e->key = key;
            e->depth = depth;
            e->score = score;
            e->flag = flag;
            e->bestMove = bestMove;
        }
    }
}
