#include "ShootingAlgorithm.h"
#include <cmath>

ActionRequest ShootingAlgorithm::decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) {
    (void)shells; // Ignore shells for this algorithm
    Position myPos = tank.getPosition();
    Direction dir = tank.getDirection();

    Position closestEnemy;
    int minDist = board.getWidth() + board.getHeight(); // Max possible
    bool enemyFound = false;

    for (int y = 0; y < board.getHeight(); ++y) {
        for (int x = 0; x < board.getWidth(); ++x) {
            const Tile& t = board.getTile(x, y);
            if ((tank.getPlayerId() == 1 && t.isTank2()) || (tank.getPlayerId() == 2 && t.isTank1())) {
                Position enemy = {x, y};
                int dx = std::min(std::abs(enemy.x - myPos.x), board.getWidth()  - std::abs(enemy.x - myPos.x));
                int dy = std::min(std::abs(enemy.y - myPos.y), board.getHeight() - std::abs(enemy.y - myPos.y));
                int dist = std::max(dx, dy);

                if (dist < minDist) {
                    minDist = dist;
                    closestEnemy = enemy;
                    enemyFound = true;
                }
            }
        }
    }

    if (enemyFound) {
        Direction toEnemy = directionTo(myPos, closestEnemy, board.getWidth(), board.getHeight());
        if (dir == toEnemy && tank.canShoot()) return ActionRequest::Shoot;
        if (dir != toEnemy) return rotateToward(dir, toEnemy);
    }

    return ActionRequest::DoNothing;
}
