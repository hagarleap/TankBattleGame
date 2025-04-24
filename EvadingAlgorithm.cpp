#include "EvadingAlgorithm.h"
#include <cmath>

TankAction EvadingAlgorithm::decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) {
    (void)board;
    Position myPos = tank.getPosition();
    for (const Shell& shell : shells) {
        Position sPos = shell.getPosition();
        if (std::abs(sPos.x - myPos.x) <= 2 && std::abs(sPos.y - myPos.y) <= 2) {
            return TankAction::MoveBackward;
        }
    }
    return TankAction::None;
}
