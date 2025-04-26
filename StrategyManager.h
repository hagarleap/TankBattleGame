#ifndef STRATEGYMANAGER_H
#define STRATEGYMANAGER_H

#include "Algorithm.h"
#include <memory>
#include <unordered_map>
#include <iostream>


class StrategyManager {
    private:
        std::unordered_map<int, std::shared_ptr<Algorithm>> strategies;
        bool useCommonSense = true;
    
    public:
        StrategyManager(bool useCommonSense = true) : useCommonSense(useCommonSense) {}
    
        void assignAlgorithm(int tankId, std::shared_ptr<Algorithm> algo);
        TankAction getAction(int tankId, const Tank& tank, const Board& board, const std::vector<Shell>& shells);
    };

#endif // STRATEGYMANAGER_H