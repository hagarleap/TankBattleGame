#ifndef SHOOTINGALGORITHM_H
#define SHOOTINGALGORITHM_H

#include "Algorithm.h"

class ShootingAlgorithm : public Algorithm {
public:
    ActionRequest decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) override;
};

#endif // SHOOTINGALGORITHM_H