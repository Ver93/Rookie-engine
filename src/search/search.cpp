#include <vector>
#include <cstdint>
#include <chrono>

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

    static Move killerMoves[64][2];
    static int  historyTable[64][64];

    inline void addKiller(int depth, const Move& m) {
        if (depth < 0 || depth >= 64) return;
        if (killerMoves[depth][0] != m) {
            killerMoves[depth][1] = killerMoves[depth][0];
            killerMoves[depth][0] = m;
        }
    }

    inline void addHistory(const Move& m, int depth) {
        if (m.from >= 0 && m.from < 64 && m.to >= 0 && m.to < 64) {
            historyTable[m.from][m.to] += depth * depth;
        }
    }

    // ---------------------------------------------------------
    // QUIESCENCE — captures + mild delta pruning
    // ---------------------------------------------------------
    int qsearch(State& state, int alpha, int beta) {

        int standPat = Evaluate::evaluate(state);

        const int DELTA = 120;
        if (standPat + DELTA < alpha)
            return alpha;

        if (standPat >= beta)
            return beta;

        if (standPat > alpha)
            alpha = standPat;

        std::vector<Move> all = LegalMove::generate(state);
        std::vector<Move> moves;
        for (auto& m : all)
            if (m.capturePiece != Const::NO_VALUE)
                moves.push_back(m);

        Undo undo;

        MoveOrder::scoreMoves(state, moves);
        MoveOrder::sortMoves(moves);

        for (auto& move : moves) {

            MoveExec::makeMove(state, move, undo);
            MoveExec::switchTurn(state);
            ThreatGen::updateThreats(state);

            int score = -qsearch(state, -beta, -alpha);

            MoveExec::switchTurn(state);
            MoveExec::undoMove(state, undo);
            ThreatGen::updateThreats(state);

            if (score >= beta)
                return beta;

            if (score > alpha)
                alpha = score;
        }

        return alpha;
    }

    // ---------------------------------------------------------
    // ALPHA-BETA — fast + stable pruning
    // ---------------------------------------------------------
    int alphaBeta(State& state, int depth, int alpha, int beta) {

        uint64_t key = Zobrist::hash(state);
        auto* entry = TranspositionTable::probeTT(key);

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

        // Mild razoring
        if (depth == 1 && !MoveVal::isKingInCheckBeforeMove(state)) {
            int eval = Evaluate::evaluate(state);
            if (eval + 100 < alpha)
                return qsearch(state, alpha, beta);
        }

        // Leaf → qsearch
        if (depth == 0)
            return qsearch(state, alpha, beta);

        // Mild futility
        if (depth == 1 && !MoveVal::isKingInCheckBeforeMove(state)) {
            int eval = Evaluate::evaluate(state);
            if (eval + 60 <= alpha)
                return eval;
        }

        // Generate moves
        std::vector<Move> legal = LegalMove::generate(state);
        Undo undo;

        if (legal.empty()) {
            if (MoveVal::isKingInCheckBeforeMove(state))
                return -Const::INF + depth;
            return 0;
        }

        MoveOrder::scoreMoves(state, legal);

        // TT move bonus
        if (ttBestMove.isValid()) {
            for (auto& m : legal)
                if (m == ttBestMove)
                    m.score += 1000000;
        }

        // Killer moves
        if (depth < 64) {
            for (auto& m : legal) {
                if (m == killerMoves[depth][0]) m.score += 900000;
                else if (m == killerMoves[depth][1]) m.score += 800000;
            }
        }

        // History
        for (auto& m : legal)
            if (m.capturePiece == Const::NO_VALUE)
                m.score += historyTable[m.from][m.to];

        MoveOrder::sortMoves(legal);

        Move bestMove{};
        int moveIndex = 0;

        for (auto& move : legal) {

            moveIndex++;

            bool isCapture = (move.capturePiece != Const::NO_VALUE);
            bool givesCheck = MoveVal::isKingInCheckAfterMove(state);

            // ⭐ Mild, safe LMP (FAST + STABLE)
            if (depth <= 2 &&
                moveIndex > 8 &&
                !isCapture &&
                !givesCheck &&
                !(move == ttBestMove) &&
                !(move == killerMoves[depth][0]) &&
                !(move == killerMoves[depth][1])) {

                continue;
            }

            MoveExec::makeMove(state, move, undo);
            MoveExec::switchTurn(state);
            ThreatGen::updateThreats(state);

            int score;

            // Mild LMR (stable)
            int reduction = 0;
            if (depth >= 4 && moveIndex > 4 && !isCapture && !givesCheck &&
                !(move == ttBestMove) &&
                !(move == killerMoves[depth][0]) &&
                !(move == killerMoves[depth][1])) {

                reduction = 1;
            }

            if (reduction > 0) {
                score = -alphaBeta(state, depth - 1 - reduction, -beta, -alpha);
                if (score > alpha)
                    score = -alphaBeta(state, depth - 1, -beta, -alpha);
            } else {
                score = -alphaBeta(state, depth - 1, -beta, -alpha);
            }

            MoveExec::switchTurn(state);
            MoveExec::undoMove(state, undo);
            ThreatGen::updateThreats(state);

            if (score >= beta) {

                addKiller(depth, move);
                addHistory(move, depth);

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

        int flag;
        if (alpha <= originalAlpha) flag = TranspositionTable::UPPERBOUND;
        else if (alpha >= beta)    flag = TranspositionTable::LOWERBOUND;
        else                       flag = TranspositionTable::EXACT;

        TranspositionTable::storeTT(key, depth, alpha, flag, bestMove);

        return alpha;
    }

        Move findBestMove(State& state, int maxDepth) {
        using namespace std::chrono;

        for (int d = 0; d < 64; ++d) {
            killerMoves[d][0] = Move{};
            killerMoves[d][1] = Move{};
        }
        for (int f = 0; f < 64; ++f)
            for (int t = 0; t < 64; ++t)
                historyTable[f][t] = 0;

        Move bestMove{};
        int prevScore = 0;

        const int WINDOW = 50;

        auto start = high_resolution_clock::now();

        for (int depth = 1; depth <= maxDepth; depth++) {

            int alpha = prevScore - WINDOW;
            int beta  = prevScore + WINDOW;

            int score = alphaBeta(state, depth, alpha, beta);

            if (score <= alpha)
                score = alphaBeta(state, depth, -Const::INF, Const::INF);
            else if (score >= beta)
                score = alphaBeta(state, depth, -Const::INF, Const::INF);

            prevScore = score;

            uint64_t key = Zobrist::hash(state);
            auto* entry = TranspositionTable::probeTT(key);

            if (entry->key == key && entry->bestMove.isValid()) {
                bestMove = entry->bestMove;
            } else {
                std::vector<Move> legal = LegalMove::generate(state);
                if (!legal.empty())
                    bestMove = legal[0];
            }

            std::cout << "info depth " << depth
                      << " score cp " << score
                      << " pv ";

            if (bestMove.isValid()) {
                std::cout << Utils::squareToString(bestMove.from)
                          << Utils::squareToString(bestMove.to);
            } else {
                std::cout << "(none)";
            }

            std::cout << std::endl;
        }

        auto end = high_resolution_clock::now();
        auto ms = duration_cast<milliseconds>(end - start).count();

        std::cout << "info time " << ms << "ms" << std::endl;

        // std::cout << "info time " << ms << "ms" << std::endl;

        return bestMove;
    }

} // namespace Search

