#include "engine.h"

namespace Engine {
    State state;

    void initialize() {
        Magics::initialize();
        Evaluate::initialize();
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
        // Utils::printBoard(state);
        // std::vector<Move> legalMoves = Search::findBestMove(state, GlobalConfig::search_depth);
        Move legalMoves = Search::findBestMove(state, depth);

        // Utils::printUCIMove(legalMoves[0]);
        Utils::printUCIMove(legalMoves);

        // for(const auto& move : legalMoves){
        //     std::cout << Utils::squareToString(move.from) << 
        //     Utils::squareToString(move.to) << 
        //     " | Score: " << move.score << "\n";
        // }
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