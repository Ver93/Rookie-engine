#include "uci_commands.h"
#include "engine.h"
#include "perft.h"
#include <iostream>
#include <sstream>

namespace UCI_Commands {

    void handlePosition(const std::string& cmd) {
        std::istringstream ss(cmd);
        std::string token;

        ss >> token;
        ss >> token;

        if (token == "startpos") {
            Engine::reset();

            ss >> token;

            while (ss >> token) {
                Engine::applyMoves(token);
            }

            return;
        }

        if (token == "fen") {
            std::string fen;
            std::getline(ss >> std::ws, fen);
            Engine::setPosition(fen);
            return;
        }
    }




    void execute(const std::string& cmd) {

        if (cmd == "uci") {
            std::cout << "id name Rookie!\n";
            std::cout << "id author Victor Rotman!\n";
            std::cout << "uciok\n";
        }

        else if (cmd == "isready") {
            std::cout << "readyok\n";
        }

        else if (cmd.rfind("position", 0) == 0) {
            handlePosition(cmd);
        }

        else if (cmd.rfind("go", 0) == 0) {

            std::istringstream ss(cmd);
            std::string token;
            int depth = 4;

            ss >> token;

            while (ss >> token) {
                if (token == "depth") {
                    ss >> depth;
                }
            }

            if (depth < 1)
                depth = 1;

            if (depth > 5)
                depth = 5;

            std::cout << "Searching depth: " << depth << "\n";

            Engine::go(depth);
        }


        else if (cmd.rfind("perft", 0) == 0) {

            std::istringstream ss(cmd);
            std::string token;
            int depth = 0;

            ss >> token;
            ss >> depth;

            if (depth <= 0 || depth >= 7) {
                std::cout << "Only perft depth 7 allowed\n";
                return;
            }

            Engine::perft(depth);
        }


        else if (cmd.rfind("reset", 0) == 0) {
            Engine::reset();
        }

        else if (cmd.rfind("quit", 0) == 0) {
            exit(0);
        }

        else if (cmd.rfind("setoption", 0) == 0){
            
        }

        else if (cmd == "") {
            std::cout << "Available commands:\n";
            std::cout << "  uci - Identify the engine\n";
            std::cout << "  isready - Check if the engine is ready\n";
            std::cout << "  position <startpos|fen> [<moves>...] - Set the position\n";
            std::cout << "  go - Start searching for the best move\n";
            std::cout << "  perft <depth> - Run perft test\n";
            std::cout << "  reset - Reset the engine\n";
            std::cout << "  quit - Exit the engine\n";
        }
    }
}
