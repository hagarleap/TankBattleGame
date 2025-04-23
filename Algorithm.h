// Algorithm.h
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "TankAction.h"
#include "Tank.h"
#include "Board.h"
#include "Shell.h"
#include <vector>

class Algorithm {
public:
    virtual TankAction decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) = 0;
    virtual ~Algorithm() = default;
};

#endif // ALGORITHM_H