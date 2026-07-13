#include "zobrist.h"
#include <random>

namespace Zobrist {

    uint64_t pieceKeys[12][64];
    uint64_t sideKey;
    uint64_t castleKeys[16];
    uint64_t epKeys[8];

    void init() {
        std::mt19937_64 rng(0xABCDEF123456789ULL);

        for (int p = 0; p < 12; p++)
            for (int sq = 0; sq < 64; sq++)
                pieceKeys[p][sq] = rng();

        sideKey = rng();

        for (int i = 0; i < 16; i++)
            castleKeys[i] = rng();

        for (int i = 0; i < 8; i++)
            epKeys[i] = rng();
    }

    uint64_t hash(const State& s) {
        uint64_t h = 0;

        for (int sq = 0; sq < 64; sq++) {
            int piece = s.squareToPieceIndex[sq];
            if (piece >= 0 && piece < 12)
                h ^= pieceKeys[piece][sq];
        }

        if (s.turn == 1)
            h ^= sideKey;

        int rights = 0;
        if (!s.kingMoved[0]) {
            if (!s.rooksMoved[0][0]) rights |= 1;
            if (!s.rooksMoved[0][1]) rights |= 2;
        }
        if (!s.kingMoved[1]) {
            if (!s.rooksMoved[1][0]) rights |= 4;
            if (!s.rooksMoved[1][1]) rights |= 8;
        }

        h ^= castleKeys[rights];

        if (s.enPassantSquare != Const::NO_VALUE)
            h ^= epKeys[s.enPassantSquare % 8];

        return h;
    }
}
