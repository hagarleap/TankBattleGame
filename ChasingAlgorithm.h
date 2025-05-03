#ifndef CHASINGALGORITHM_H
#define CHASINGALGORITHM_H

#include "Algorithm.h"

class ChasingAlgorithm : public Algorithm {
    private:
        Position lastTarget{-1, -1};
        bool mapChanged = true;
        Direction cachedDirection = Direction::U; // fallback arbitrary
    public:
        ActionRequest decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) override;
        void notifyMapChanged();
    };

#endif // CHASINGALGORITHM_H