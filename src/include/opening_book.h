#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace OpeningBook {
    void initialize();
    std::vector<std::string> getMoves(const std::string& fen);
}
