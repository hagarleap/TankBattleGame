#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "common/ActionRequest.h"
#include "Tank.h"
#include "Board.h"
#include "Shell.h"
#include <vector>
#include <string>
#include <iostream>
#include <optional>

class Algorithm {
public:
    virtual ActionRequest decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) = 0;
    virtual ~Algorithm() = default;
};

ActionRequest applyCommonSense(const Tank& tank, const Board& board, const std::vector<Shell>& shells, ActionRequest proposed, std::string& reason);
bool isDangerousPosition(const Position& pos, const Board& board, const std::vector<Shell>& shells);
bool canShootOpponent(const Tank& tank, const Board& board);
Direction directionTo(const Position& from, const Position& to, int width, int height);
ActionRequest rotateToward(Direction current, Direction target);

#endif // ALGORITHM_H