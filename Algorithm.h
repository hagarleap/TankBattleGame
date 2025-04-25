#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "TankAction.h"
#include "Tank.h"
#include "Board.h"
#include "Shell.h"
#include <vector>
#include <string>
#include <iostream>
#include <optional>

class Algorithm {
public:
    virtual TankAction decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) = 0;
    virtual ~Algorithm() = default;
};

TankAction applyCommonSense(const Tank& tank, const Board& board, const std::vector<Shell>& shells, TankAction proposed, std::string& reason);
bool isDangerousPosition(const Position& pos, const Board& board, const std::vector<Shell>& shells);
bool canShootOpponent(const Tank& tank, const Board& board);
Direction directionTo(const Position& from, const Position& to, int width, int height);
TankAction rotateToward(Direction current, Direction target);
std::optional<Direction> findSafeDirection(const Position& from, const Board& board, const std::vector<Shell>& shells, const Tank& tank);

#endif // ALGORITHM_H