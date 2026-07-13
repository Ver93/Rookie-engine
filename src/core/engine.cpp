#include "engine.h"

namespace Engine {
    State state;

    void initialize() {
        Magics::initialize();
        Evaluate::initialize();
        TranspositionTable::initTT(64);
        Zobrist::init();
        Utils::loadFen(state, Const::STARTING_FEN);
    }

    void reset(){
        Utils::loadFen(state, Const::STARTING_FEN);
    }
    
    void setPosition(const std::string& fen){
        Utils::printBoard(state);
        Utils::loadFen(state, fen);
        Utils::printBoard(state);
    }

    void makeMove(const Move& move){
        Undo undo;
        MoveExec::makeMove(state, move, undo);
        MoveExec::switchTurn(state);
        ThreatGen::updateThreats(state);
    }

    void go(int depth){
        Move legalMoves = Search::findBestMove(state, depth);
        Utils::printUCIMove(legalMoves);
    }

    void perft(int depth){
        Perft::dividePerft(depth, state);
    }

    void applyMoves(const std::string& token) {
        std::pair<int, int> pos = Utils::parseMoveString(token);
        auto pseudoMoves = MoveGen::generatePseudoMoves(state);

        for (auto& move : pseudoMoves) {
            if (move.from == pos.first && move.to == pos.second) {

                bool isWhite = state.turn == Const::PC_WHITE;

                if ((move.movingType == Const::MT_PROMOTION ||
                    move.movingType == Const::MT_PROMOTION_CAPTURE) &&
                    token.length() == 5) {
                    char pp = token[4];
                    int promotionPiece = Utils::charToPieceIndex(pp, isWhite);
                    move.promotionPiece = promotionPiece;
                }

                makeMove(move);
                break;
            }
        }
    }
}