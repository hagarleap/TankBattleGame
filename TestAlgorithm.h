#pragma once
#include "common/ActionRequest.h"
#include "Tank.h"
#include "Board.h"
#include <vector>

class TestAlgorithm {
public:
    static ActionRequest getNextAction(const Tank& self);
};
