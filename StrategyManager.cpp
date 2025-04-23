#include "StrategyManager.h"
#include "Algorithm.h"

void StrategyManager::assignAlgorithm(int tankId, std::shared_ptr<Algorithm> algo) {
    strategies[tankId] = algo;
}

TankAction StrategyManager::getAction(int tankId, const Tank& tank, const Board& board, const std::vector<Shell>& shells) {
    if (strategies.count(tankId)) {
        TankAction rawAction = strategies[tankId]->decideAction(tank, board, shells);
        std::string debug;
        TankAction adjusted = applyCommonSense(tank, board, shells, rawAction, debug);
        return adjusted;
    }
    return TankAction::None;
}