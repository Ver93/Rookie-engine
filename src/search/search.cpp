#include "search.h"

namespace Search {

    int alphaBeta(State& state, int depth, int alpha, int beta){
        if(depth == 0){
            return Evaluate::evaluate(state);
        }

        std::vector<Move> legal = LegalMove::generate(state);
        Undo undo;

        if (legal.empty()) {
            if (MoveVal::isKingInCheckBeforeMove(state)) {
                // std::cout << "[alphaBeta] CHECKMATE at depth " << depth << "\n";
                return -Const::INF + depth;
            } else {
                // std::cout << "[alphaBeta] STALEMATE at depth " << depth << "\n";
                return 0;
            }
        }


        MoveOrder::scoreMoves(state, legal);
        MoveOrder::sortMoves(legal);

        for (auto& move : legal) {
            MoveExec::makeMove(state, move, undo);
            MoveExec::switchTurn(state);
            ThreatGen::updateThreats(state);

            int score = -alphaBeta(state, depth - 1, -beta, -alpha);

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

    Move findBestMove(State& state, int depth){
        State test{};
        test = state;

        Move bestMove{};
        Undo undo{};
        int bestScore = -Const::INF;

        std::vector<Move> legal = LegalMove::generate(test);


        if (legal.empty())
            return bestMove;


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