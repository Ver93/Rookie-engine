#pragma once
#include <cstdint>
#include "state.h"

namespace Zobrist {

    extern uint64_t pieceKeys[12][64];
    extern uint64_t sideKey;
    extern uint64_t castleKeys[16];
    extern uint64_t epKeys[8];

    void init();
    uint64_t hash(const State& s);
}
