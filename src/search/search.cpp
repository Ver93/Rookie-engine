#include <vector>
#include <cstdint>

#include "state.h"
#include "move.h"
#include "undo.h"
#include "const.h"
#include "evaluate.h"
#include "legal_move.h"
#include "move_exec.h"
#include "move_order.h"
#include "threat_gen.h"
#include "move_val.h"
#include "zobrist.h"
#include "tt.h"

namespace Search {

    int alphaBeta(State& state, int depth, int alpha, int beta) {

        // ---------------------------
        // Transposition Table probe
        // ---------------------------
        uint64_t key = Zobrist::hash(state);
        TranspositionTable::TTEntry* entry = TranspositionTable::probeTT(key);

        int originalAlpha = alpha;
        Move ttBestMove{};

        if (entry->key == key && entry->depth >= depth) {

            if (entry->flag == TranspositionTable::EXACT)
                return entry->score;

            if (entry->flag == TranspositionTable::LOWERBOUND && entry->score > alpha)
                alpha = entry->score;

            if (entry->flag == TranspositionTable::UPPERBOUND && entry->score < beta)
                beta = entry->score;

            if (alpha >= beta)
                return entry->score;

            ttBestMove = entry->bestMove;
        }

        // ---------------------------
        // Leaf node → evaluation
        // ---------------------------
        if (depth == 0) {
            return Evaluate::evaluate(state);
        }

        // ---------------------------
        // Generate legal moves
        // ---------------------------
        std::vector<Move> legal = LegalMove::generate(state);
        Undo undo;

        if (legal.empty()) {
            if (MoveVal::isKingInCheckBeforeMove(state)) {
                // Checkmate: losing side
                return -Const::INF + depth;
            } else {
                // Stalemate
                return 0;
            }
        }

        // ---------------------------
        // Move ordering (TT move boosted)
        // ---------------------------
        MoveOrder::scoreMoves(state, legal);

        if (ttBestMove.isValid()) {
            for (auto& m : legal) {
                if (m == ttBestMove) {
                    m.score += 1000000; // prioritize TT move
                    break;
                }
            }
        }

        MoveOrder::sortMoves(legal);

        // ---------------------------
        // Alpha-beta search
        // ---------------------------
        Move bestMove{};
        for (auto& move : legal) {

            MoveExec::makeMove(state, move, undo);
            MoveExec::switchTurn(state);
            ThreatGen::updateThreats(state);

            int score = -alphaBeta(state, depth - 1, -beta, -alpha);

            MoveExec::switchTurn(state);
            MoveExec::undoMove(state, undo);
            ThreatGen::updateThreats(state);

            if (score >= beta) {
                // Fail-high → LOWERBOUND
                TranspositionTable::storeTT(key, depth, score,
                                            TranspositionTable::LOWERBOUND,
                                            move);
                return beta;
            }

            if (score > alpha) {
                alpha = score;
                bestMove = move;
            }
        }

        // ---------------------------
        // Store in TT
        // ---------------------------
        int flag;
        if (alpha <= originalAlpha)
            flag = TranspositionTable::UPPERBOUND;
        else if (alpha >= beta)
            flag = TranspositionTable::LOWERBOUND;
        else
            flag = TranspositionTable::EXACT;

        TranspositionTable::storeTT(key, depth, alpha, flag, bestMove);

        return alpha;
    }

    Move findBestMove(State& state, int depth) {
        State test = state;

        Move bestMove{};
        Undo undo{};
        int bestScore = -Const::INF;

        std::vector<Move> legal = LegalMove::generate(test);

        if (legal.empty())
            return bestMove;

        // Basic move ordering
        MoveOrder::scoreMoves(test, legal);
        MoveOrder::sortMoves(legal);

        for (auto& move : legal) {

            MoveExec::makeMove(test, move, undo);
            MoveExec::switchTurn(test);
            ThreatGen::updateThreats(test);

            int score = -alphaBeta(test, depth - 1, -Const::INF, Const::INF);

            MoveExec::switchTurn(test);
            MoveExec::undoMove(test, undo);
            ThreatGen::updateThreats(test);

            if (score > bestScore) {
                bestScore = score;
                bestMove = move;
                bestMove.score = score;
            }
        }

        return bestMove;
    }
}
