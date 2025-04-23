#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "TankAction.h"
#include "Tank.h"
#include "Board.h"
#include "Shell.h"
#include <vector>
#include <string>

class Algorithm {
public:
    virtual TankAction decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) = 0;
    virtual ~Algorithm() = default;
};

TankAction applyCommonSense(const Tank& tank, const Board& board, const std::vector<Shell>& shells, TankAction proposed, std::string& reason);
bool isDangerousPosition(const Position& pos, const Board& board, const std::vector<Shell>& shells);
bool canShootOpponent(const Tank& tank, const Board& board);
Direction directionTo(const Position& from, const Position& to);
TankAction rotateToward(Direction current, Direction target);

#endif // ALGORITHM_H