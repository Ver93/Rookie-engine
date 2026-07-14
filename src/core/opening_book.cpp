#include "opening_book.h"
#include <unordered_map>

#include "utils.h"

namespace OpeningBook {

    static std::unordered_map<std::string, std::vector<std::string>> book;

    void initialize() {

        // ========== STARTPOSITION ==========
        book["rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -"] =
            {"e2e4", "d2d4", "c2c4"};

        // ========== SPANSKT ==========
        book["rnbqkbnr/pppp1ppp/8/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq -"] =
            {"f1b5", "d2d4"};

        book["r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq -"] =
            {"f1b5", "c2c3"};

        // ========== ITALIENSKT ==========
        book["rnbqkbnr/pppp1ppp/8/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq -"] =
            {"f1c4", "d2d3"};

        book["r1bqkbnr/pppp1ppp/2n5/4p3/2B1P3/5N2/PPPP1PPP/RNBQK2R b KQkq -"] =
            {"g8f6", "f8c5"};

        // ========== SICILIANSKT ==========
        // Najdorf
        book["rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6"] =
            {"d2d4", "c2c3"};

        // Klassisk
        book["rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq -"] =
            {"d2d4", "b1c3"};

        // Scheveningen
        book["rnbqkb1r/pp1ppppp/5n2/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq -"] =
            {"e4e5", "b1c3"};

        // ========== CARO-KANN ==========
        book["rnbqkbnr/pp1ppppp/2p5/4P3/8/8/PPPP1PPP/RNBQKBNR w KQkq -"] =
            {"d2d4", "c2c4"};

        book["rnbqkbnr/pp1p1ppp/2p5/4p3/3PP3/8/PPP2PPP/RNBQKBNR b KQkq -"] =
            {"d7d5", "g8f6"};

        // ========== FRANSK ==========
        book["rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq -"] =
            {"d2d4", "g1f3"};

        book["rnbqkbnr/ppp2ppp/3p4/4p3/3PP3/5N2/PPP2PPP/RNBQKB1R b KQkq -"] =
            {"c8g4", "g8f6"};

        // ========== SLAVISK ==========
        book["rnbqkbnr/ppp1pppp/8/3p4/3P4/8/PPP1PPPP/RNBQKBNR w KQkq -"] =
            {"c2c4", "g1f3"};

        book["rnbqkbnr/ppp1pppp/8/3p4/2PP4/8/PP2PPPP/RNBQKBNR b KQkq -"] =
            {"c7c6", "g8f6"};

        // ========== ENGELSKT ==========
        book["rnbqkbnr/pppppppp/8/8/2P5/8/PP1PPPPP/RNBQKBNR b KQkq -"] =
            {"e7e5", "c7c5"};

        book["rnbqkbnr/pp1ppppp/2p5/8/2P5/8/PP1PPPPP/RNBQKBNR w KQkq -"] =
            {"g1f3", "b1c3"};

        // ========== KATALANSKT ==========
        book["rnbqkbnr/pppppppp/8/8/3P4/2N5/PPP1PPPP/R1BQKBNR b KQkq -"] =
            {"d7d5", "g8f6"};

        book["rnbqkb1r/ppp1pppp/5n2/3p4/3P4/2N5/PPP1PPPP/R1BQK2R w KQkq -"] =
            {"g2g3", "c1g5"};

        // ========== LONDON ==========
        book["rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR w KQkq -"] =
            {"c1f4", "g1f3"};

        book["rnbqkbnr/pppp1ppp/8/4p3/3P4/5N2/PPP1PPPP/RNBQKB1R b KQkq -"] =
            {"e5e4", "g8f6"};

        // ========== SVART MOT e4 ==========
        book["rnbqkbnr/pppppppp/8/4P3/8/8/PPPP1PPP/RNBQKBNR b KQkq -"] =
            {"c7c5", "e7e5", "g8f6"};

        // ========== SVART MOT d4 ==========
        book["rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq -"] =
            {"d7d5", "g8f6", "e7e6"};

    }

    std::vector<std::string> getMoves(const std::string& fen) {

        // Ta bara de första 4 FEN-fälten
        std::stringstream ss(fen);
        std::string part;
        std::vector<std::string> parts;

        while (ss >> part)
            parts.push_back(part);

        if (parts.size() < 4)
            return {};

        std::string key = parts[0] + " " + parts[1] + " " + parts[2] + " " + parts[3];

        auto it = book.find(key);
        if (it == book.end()) return {};
        return it->second;
    }


}
