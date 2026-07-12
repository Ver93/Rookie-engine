#include "uci.h"
#include "uci_commands.h"
#include <iostream>

namespace UCI {
    void run() {
        std::string cmd;
        while (std::getline(std::cin, cmd)) {
            handleCommand(cmd);
        }
    }

    void handleCommand(const std::string& cmd) {
        UCI_Commands::execute(cmd);
    }
}
