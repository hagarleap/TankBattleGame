#pragma once
#include "TankAction.h"
#include "Tank.h"
#include "Board.h"
#include <vector>

class TestAlgorithm {
public:
    static TankAction getNextAction(const Tank& self);
};
