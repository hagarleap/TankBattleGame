#include "StrategyManager.h"
#include "Algorithm.h"
#include "ChasingAlgorithm.h"


void StrategyManager::assignAlgorithm(int tankId, std::shared_ptr<Algorithm> algo) {
    strategies[tankId] = algo;
}

void StrategyManager::notifyMapChangedAll() {
    for (auto& [id, algo] : strategies) {
        if (auto chase = std::dynamic_pointer_cast<ChasingAlgorithm>(algo)) {
            chase->notifyMapChanged();
        }
    }
}

ActionRequest StrategyManager::getAction(int tankId, const Tank& tank, const Board& board, const std::vector<Shell>& shells) {
    if (strategies.count(tankId)) {
        if (verbose) std::cout << tank.toString() << std::endl;
        ActionRequest rawAction = strategies[tankId]->decideAction(tank, board, shells);
        if (verbose) std::cout << to_string(rawAction) << std::endl; 

        if (useCommonSense) {
            std::string debug;
            ActionRequest adjusted = applyCommonSense(tank, board, shells, rawAction, debug);
            if (verbose) std::cout << to_string(adjusted) << std::endl; 
            return adjusted;
        } else {
            return rawAction;
        }
    }
    return ActionRequest::DoNothing;
}
