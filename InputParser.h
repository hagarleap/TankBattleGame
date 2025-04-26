#pragma once

#include <string>
#include <vector>
#include <utility>
#include "Board.h"
#include "Tank.h"

class InputParser {
public:
    static std::pair<int, int> getBoardDimensions(const std::string& filename);
    
    static bool parseFile(
        const std::string& filename,
        Board& board,
        std::vector<Tank>& player1Tanks,
        std::vector<Tank>& player2Tanks,
        std::vector<std::string>& inputErrors
    );
};
