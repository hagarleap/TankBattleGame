#ifndef EVADINGALGORITHM_H
#define EVADINGALGORITHM_H

#include "Algorithm.h"

class EvadingAlgorithm : public Algorithm {
public:
    TankAction decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) override;
};

#endif // EVADINGALGORITHM_H