#include "StrategyManager.h"

void StrategyManager::assignAlgorithm(int tankId, std::shared_ptr<Algorithm> algo) {
    strategies[tankId] = algo;
}

TankAction StrategyManager::getAction(int tankId, const Tank& tank, const Board& board, const std::vector<Shell>& shells) {
    if (strategies.count(tankId)) {
        return strategies[tankId]->decideAction(tank, board, shells);
    }
    return TankAction::None;
}
