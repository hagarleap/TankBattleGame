#pragma once

#include <string>
#include <vector>
#include "Board.h"
#include "Tank.h"

class InputParser {
public:
    static bool parseFile(
        const std::string& filename,
        Board& board,
        std::vector<Tank>& player1Tanks,
        std::vector<Tank>& player2Tanks,
        std::vector<std::string>& inputErrors
    );
};
