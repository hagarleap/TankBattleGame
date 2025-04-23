#ifndef CHASINGALGORITHM_H
#define CHASINGALGORITHM_H

#include "Algorithm.h"

class ChasingAlgorithm : public Algorithm {
public:
    TankAction decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) override;
};

#endif // CHASINGALGORITHM_H