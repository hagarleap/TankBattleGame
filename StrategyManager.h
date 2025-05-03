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
        bool verbose = false; // for debugging purposes, if you want to see the common sense algorithm in action, set this to true
    
    public:
        StrategyManager(bool useCommonSense = true, bool verbose = false) : useCommonSense(useCommonSense), verbose(verbose) {}
        void assignAlgorithm(int tankId, std::shared_ptr<Algorithm> algo);
        ActionRequest getAction(int tankId, const Tank& tank, const Board& board, const std::vector<Shell>& shells);
        void notifyMapChangedAll();
    };

#endif // STRATEGYMANAGER_H