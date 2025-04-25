#include "StrategyManager.h"
#include "Algorithm.h"

void StrategyManager::assignAlgorithm(int tankId, std::shared_ptr<Algorithm> algo) {
    strategies[tankId] = algo;
}

TankAction StrategyManager::getAction(int tankId, const Tank& tank, const Board& board, const std::vector<Shell>& shells) {
    if (strategies.count(tankId)) {
        std::cout << tank.toString() << std::endl; //TODO: delete
        TankAction rawAction = strategies[tankId]->decideAction(tank, board, shells);
        std::cout << to_string(rawAction) << std::endl; //TODO: delete
        std::string debug;
        TankAction adjusted = applyCommonSense(tank, board, shells, rawAction, debug);
        std::cout << to_string(adjusted) << std::endl; //TODO: delete
        return adjusted;
    }
    return TankAction::None;
}