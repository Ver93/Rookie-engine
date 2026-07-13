#pragma once

#include <cstdint>
#include <string>

namespace Const {

    constexpr int MAX_SQUARES                   = 1ULL << 6;
    constexpr int MAX_BISHOP_ENTRIES            = 1ULL << 13;
    constexpr int MAX_ROOK_ENTRIES              = 1ULL << 14;
    constexpr int TRIVIAL_MAGIC                 = 0xFF;
    constexpr int NO_VALUE                      = -1;

    constexpr int SLIDING_MOVES[8][2]           { {-1, +0}, {+1, +0}, {+0, -1}, {+0, +1}, {-1, -1}, {-1, +1}, {+1, -1}, {+1, +1} };

    constexpr int PT_PAWN                       = 0;
    constexpr int PT_KNIGHT                     = 1;
    constexpr int PT_BISHOP                     = 2;
    constexpr int PT_ROOK                       = 3;
    constexpr int PT_QUEEN                      = 4;
    constexpr int PT_KING                       = 5;

    constexpr int PC_WHITE                      = 0;
    constexpr int PC_BLACK                      = 1;

    constexpr int W_PAWN                        = PT_PAWN;
    constexpr int W_KNIGHT                      = PT_KNIGHT;
    constexpr int W_BISHOP                      = PT_BISHOP;
    constexpr int W_ROOK                        = PT_ROOK;
    constexpr int W_QUEEN                       = PT_QUEEN;
    constexpr int W_KING                        = PT_KING;

    constexpr int B_PAWN                        = PT_PAWN + 6;
    constexpr int B_KNIGHT                      = PT_KNIGHT + 6;
    constexpr int B_BISHOP                      = PT_BISHOP + 6;
    constexpr int B_ROOK                        = PT_ROOK + 6;
    constexpr int B_QUEEN                       = PT_QUEEN + 6;
    constexpr int B_KING                        = PT_KING + 6;

    constexpr int MT_QUIET                      = 0;
    constexpr int MT_CAPTURE                    = 1;
    constexpr int MT_DOUBLEPUSH                 = 2;
    constexpr int MT_ENPASSANT                  = 3;
    constexpr int MT_CASTLE                     = 4;
    constexpr int MT_PROMOTION                  = 5;
    constexpr int MT_PROMOTION_CAPTURE          = 6;

    constexpr int SINGLE_PUSH                   = 8;
    constexpr int DOUBLE_PUSH                   = 16;

    constexpr int C_QUEEN_SIDE                  = 0;
    constexpr int C_KING_SIDE                   = 1;

    enum SQUARE : int {
        A1, B1, C1, D1, E1, F1, G1, H1,
        A2, B2, C2, D2, E2, F2, G2, H2,
        A3, B3, C3, D3, E3, F3, G3, H3,
        A4, B4, C4, D4, E4, F4, G4, H4,
        A5, B5, C5, D5, E5, F5, G5, H5,
        A6, B6, C6, D6, E6, F6, G6, H6,
        A7, B7, C7, D7, E7, F7, G7, H7,
        A8, B8, C8, D8, E8, F8, G8, H8,
    };

    constexpr uint64_t W_CASTLE_BLOCKER_QS =
        (1ULL << SQUARE::B1) |
        (1ULL << SQUARE::C1) |
        (1ULL << SQUARE::D1);

    constexpr uint64_t W_CASTLE_BLOCKER_KS =
        (1ULL << SQUARE::F1) |
        (1ULL << SQUARE::G1);

    constexpr uint64_t B_CASTLE_BLOCKER_QS =
        (1ULL << SQUARE::B8) |
        (1ULL << SQUARE::C8) |
        (1ULL << SQUARE::D8);

    constexpr uint64_t B_CASTLE_BLOCKER_KS =
        (1ULL << SQUARE::F8) |
        (1ULL << SQUARE::G8);

    constexpr uint64_t W_CASTLE_THREAT_QS =
        (1ULL << SQUARE::C1) |
        (1ULL << SQUARE::D1) |
        (1ULL << SQUARE::E1);

    constexpr uint64_t W_CASTLE_THREAT_KS =
        (1ULL << SQUARE::E1) |
        (1ULL << SQUARE::F1) |
        (1ULL << SQUARE::G1);

    constexpr uint64_t B_CASTLE_THREAT_QS =
        (1ULL << SQUARE::C8) |
        (1ULL << SQUARE::D8) |
        (1ULL << SQUARE::E8);

    constexpr uint64_t B_CASTLE_THREAT_KS =
        (1ULL << SQUARE::E8) |
        (1ULL << SQUARE::F8) |
        (1ULL << SQUARE::G8);

    constexpr int NUM_PROMOTION_PIECES = 4;

    constexpr int W_PROMOTION_PIECES[] = {
        W_KNIGHT,
        W_BISHOP,
        W_ROOK,
        W_QUEEN
    };

    constexpr int B_PROMOTION_PIECES[] = {
        B_KNIGHT,
        B_BISHOP,
        B_ROOK,
        B_QUEEN
    };

    constexpr uint64_t EXCLUDE_A_FILE           = 0xfefefefefefefefeULL;
    constexpr uint64_t EXCLUDE_B_FILE           = 0xfdfdfdfdfdfdfdfdULL;
    constexpr uint64_t EXCLUDE_G_FILE           = 0xbfbfbfbfbfbfbfbfULL;
    constexpr uint64_t EXCLUDE_H_FILE           = 0x7f7f7f7f7f7f7f7fULL;

    constexpr uint64_t EXCLUDE_AB_FILE          = EXCLUDE_A_FILE & EXCLUDE_B_FILE;
    constexpr uint64_t EXCLUDE_GH_FILE          = EXCLUDE_G_FILE & EXCLUDE_H_FILE;

    constexpr uint64_t RANK_1                   = 0x00000000000000FFULL;
    constexpr uint64_t RANK_2                   = 0x000000000000FF00ULL;
    constexpr uint64_t RANK_7                   = 0x00FF000000000000ULL;
    constexpr uint64_t RANK_8                   = 0xFF00000000000000ULL;

    constexpr uint64_t NO_MASK                  = 0x00ULL;

    constexpr uint64_t SQUARE_MASK[64] = {
        1ULL << 0,  1ULL << 1,  1ULL << 2,  1ULL << 3,  1ULL << 4,  1ULL << 5,  1ULL << 6,  1ULL << 7,
        1ULL << 8,  1ULL << 9,  1ULL << 10, 1ULL << 11, 1ULL << 12, 1ULL << 13, 1ULL << 14, 1ULL << 15,
        1ULL << 16, 1ULL << 17, 1ULL << 18, 1ULL << 19, 1ULL << 20, 1ULL << 21, 1ULL << 22, 1ULL << 23,
        1ULL << 24, 1ULL << 25, 1ULL << 26, 1ULL << 27, 1ULL << 28, 1ULL << 29, 1ULL << 30, 1ULL << 31,
        1ULL << 32, 1ULL << 33, 1ULL << 34, 1ULL << 35, 1ULL << 36, 1ULL << 37, 1ULL << 38, 1ULL << 39,
        1ULL << 40, 1ULL << 41, 1ULL << 42, 1ULL << 43, 1ULL << 44, 1ULL << 45, 1ULL << 46, 1ULL << 47,
        1ULL << 48, 1ULL << 49, 1ULL << 50, 1ULL << 51, 1ULL << 52, 1ULL << 53, 1ULL << 54, 1ULL << 55,
        1ULL << 56, 1ULL << 57, 1ULL << 58, 1ULL << 59, 1ULL << 60, 1ULL << 61, 1ULL << 62, 1ULL << 63
    };

    const std::string STARTING_FEN              = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    constexpr int INF                           = 1000000000;

    constexpr int PV_PAWN                       = 100;
    constexpr int PV_KNIGHT                     = 320;
    constexpr int PV_BISHOP                     = 350;
    constexpr int PV_ROOK                       = 500;
    constexpr int PV_QUEEN                      = 900;
    constexpr int PV_KING                       = INF;

    constexpr int getPieceType(int pieceIndex) {
        return (pieceIndex >= 6) ? pieceIndex - 6 : pieceIndex;
    }

    constexpr int getPieceIndex(int pieceType) {
        return (pieceType >= 6) ? pieceType + 6 : pieceType;
    }

    constexpr const int* getPromotionPieces(bool isWhite) {
        return isWhite ? W_PROMOTION_PIECES : B_PROMOTION_PIECES;
    }

    constexpr int PIECE_VALUES[] = {
        PV_PAWN,
        PV_KNIGHT,
        PV_BISHOP,
        PV_ROOK,
        PV_QUEEN,
        PV_KING
    };

    constexpr int getPieceValue(int pieceType){
        return PIECE_VALUES[pieceType];
    }


    constexpr uint64_t FILE_MASKS[8] = {
        0x0101010101010101ULL, // File A
        0x0202020202020202ULL, // File B
        0x0404040404040404ULL, // File C
        0x0808080808080808ULL, // File D
        0x1010101010101010ULL, // File E
        0x2020202020202020ULL, // File F
        0x4040404040404040ULL, // File G
        0x8080808080808080ULL  // File H
    };

    constexpr uint64_t RANK_MASKS[8] = {
        0x00000000000000FFULL, // Rank 1
        0x000000000000FF00ULL, // Rank 2
        0x0000000000FF0000ULL, // Rank 3
        0x00000000FF000000ULL, // Rank 4
        0x000000FF00000000ULL, // Rank 5
        0x0000FF0000000000ULL, // Rank 6
        0x00FF000000000000ULL, // Rank 7
        0xFF00000000000000ULL  // Rank 8
    };

    constexpr uint64_t getPassedPawnFileMask(int sq) {
        int file = sq % 8;
        uint64_t mask = FILE_MASKS[file];
        if (file > 0) mask |= FILE_MASKS[file - 1];
        if (file < 7) mask |= FILE_MASKS[file + 1];

        return mask;
    }

    constexpr uint64_t getCurrentFileMask(int sq) {
        int file = sq % 8;
        uint64_t mask = FILE_MASKS[file];
        return mask;
    }

    constexpr int WT_KNIGHT                 = 4;
    constexpr int WT_BISHOP                 = 3;
    constexpr int WT_ROOK                   = 2;
    constexpr int WT_QUEEN                  = 1;
}