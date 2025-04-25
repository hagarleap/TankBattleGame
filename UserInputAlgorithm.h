#ifndef USERINPUTALGORITHM_H
#define USERINPUTALGORITHM_H

#include "Algorithm.h"
#include <unordered_map>

class UserInputAlgorithm : public Algorithm {
public:
    TankAction decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) override;
};

#endif // USERINPUTALGORITHM_H