#include "threat_gen.h"

namespace ThreatGen {
    void updateThreats(State& state) {
        state.threatMap[Const::PC_WHITE] = 0ULL;
        state.threatMap[Const::PC_BLACK] = 0ULL;

        uint64_t occ = state.occupancy;

        for (int color = 0; color <= 1; ++color) {
            uint64_t pieces = state.turnOccupancy[color];

            uint64_t temp = pieces;
            while (temp) {
                int sq = Utils::popLSB(temp);
                int pieceIndex = state.squareToPieceIndex[sq];
                int pieceType = Const::getPieceType(pieceIndex);
                bool isWhitePiece = (pieceIndex < 6);

                switch (pieceType) {
                    case Const::PT_PAWN:state.threatMap[color] |= AttackTables::getPawnTable(*AttackGlobals::ad, sq, isWhitePiece); break;
                    case Const::PT_KNIGHT: state.threatMap[color] |= AttackTables::getKnightTable(*AttackGlobals::ad, sq); break;
                    case Const::PT_BISHOP: state.threatMap[color] |= AttackTables::getBishopTable(*AttackGlobals::ad, sq, occ); break;
                    case Const::PT_ROOK: state.threatMap[color] |= AttackTables::getRookTable(*AttackGlobals::ad, sq, occ); break;
                    case Const::PT_QUEEN:state.threatMap[color] |= AttackTables::getBishopTable(*AttackGlobals::ad, sq, occ) | AttackTables::getRookTable(*AttackGlobals::ad, sq, occ); break;
                    case Const::PT_KING: state.threatMap[color] |= AttackTables::getKingTable(*AttackGlobals::ad, sq); break;
                    default: break;
                }
            }
        }
    }
}