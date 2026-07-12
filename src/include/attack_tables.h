#pragma once

#include <cstdint>

#include "const.h"

namespace AttackTables {
    
    struct AttackData {
        uint64_t bishopAttackTable[64][Const::MAX_BISHOP_ENTRIES];
        uint64_t rookAttackTable[64][Const::MAX_ROOK_ENTRIES];

        uint64_t bishopBlockerMasks[64];
        uint64_t bishopShiftAmount[64];
        uint64_t bishopMagics[64];
        int bishopBits[64];

        uint64_t rookBlockerMasks[64];
        uint64_t rookShiftAmount[64];
        uint64_t rookMagics[64];
        int rookBits[64];

        uint64_t whitePawnMoveTable[64];
        uint64_t blackPawnMoveTable[64];
        uint64_t whitePawnAttackTable[64];
        uint64_t blackPawnAttackTable[64];
        uint64_t knightAttackTable[64];
        uint64_t kingAttackTable[64];
    };

    inline uint64_t getPawnTable(AttackTables::AttackData& data, int square, bool isWhite){
        return (isWhite) ? data.whitePawnAttackTable[square] : data.blackPawnAttackTable[square];
    };

    inline uint64_t getKnightTable(AttackTables::AttackData& data, int square){
        return data.knightAttackTable[square];
    };

    inline uint64_t getKingTable(AttackTables::AttackData& data, int square){
        return data.kingAttackTable[square];
    };

    inline uint64_t getBishopTable(AttackTables::AttackData& data, int square, uint64_t occ){
        uint64_t blockers = occ & data.bishopBlockerMasks[square];
        uint64_t index = (blockers * data.bishopMagics[square]) >> data.bishopShiftAmount[square];
        return data.bishopAttackTable[square][index];
    }

    inline uint64_t getRookTable(AttackTables::AttackData& data, int square, uint64_t occ){
        uint64_t blockers = occ & data.rookBlockerMasks[square];
        uint64_t index = (blockers * data.rookMagics[square]) >> data.rookShiftAmount[square];
        return data.rookAttackTable[square][index];
    }
}