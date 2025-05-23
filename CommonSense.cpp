#include "Algorithm.h"
#include <cmath>

bool isDangerousPosition(const Position& pos, const Board& board, const std::vector<Shell>& shells, const Tank& self) {
    for (const Shell& shell : shells) {
        Position sPos = shell.getPosition();
        Direction dir = shell.getDirection();
        for (int i = 1; i <= 4; ++i) {
            Position next = board.wrapPosition(sPos.move(dir, i));
            if (next == pos) return true;
            if (board.getTile(next).isWall()) break;
        }
    }
    
    const Tile& tile = board.getTile(board.wrapPosition(pos));
    if (tile.isMine()) return true;

    // Ignore self
    if (tile.isTank1() && self.getPlayerId() == 1) return false;
    if (tile.isTank2() && self.getPlayerId() == 2) return false;

    return tile.isOccupied();
}

Direction directionTo(const Position& from, const Position& to, int width, int height) {
    int dxRaw = to.x - from.x;
    int dyRaw = to.y - from.y;

    int dx = (std::abs(dxRaw) <= width / 2) ? dxRaw : -std::copysign(width - std::abs(dxRaw), dxRaw);
    int dy = (std::abs(dyRaw) <= height / 2) ? dyRaw : -std::copysign(height - std::abs(dyRaw), dyRaw);

    if (dx > 0 && dy > 0) return Direction::DR;
    if (dx > 0 && dy < 0) return Direction::UR;
    if (dx < 0 && dy > 0) return Direction::DL;
    if (dx < 0 && dy < 0) return Direction::UL;
    if (dx > 0) return Direction::R;
    if (dx < 0) return Direction::L;
    if (dy > 0) return Direction::D;
    return Direction::U;
}


ActionRequest rotateToward(Direction current, Direction target) {
    int cur = static_cast<int>(current);
    int tgt = static_cast<int>(target);
    int diff = (tgt - cur + 8) % 8;
    if (diff == 0) return ActionRequest::DoNothing;
    if (diff == 1 || diff == 2) return ActionRequest::RotateRight45;
    if (diff == 7 || diff == 6) return ActionRequest::RotateLeft45;
    return (diff <= 4) ? ActionRequest::RotateRight90 : ActionRequest::RotateLeft90;
}

ActionRequest applyCommonSense(const Tank& tank, const Board& board, const std::vector<Shell>& shells, ActionRequest proposed, std::string& reason) {
    Position pos = tank.getPosition();
    Direction dir = tank.getDirection();
    Position forward = pos.move(dir);
    Position backward = pos.move(opposite(dir));

    bool dangerHere = isDangerousPosition(pos, board, shells, tank);
    bool dangerForward = isDangerousPosition(forward, board, shells, tank);
    bool dangerBackward = isDangerousPosition(backward, board, shells, tank);

    if ((proposed == ActionRequest::DoNothing || proposed == ActionRequest::RotateLeft45 || proposed == ActionRequest::RotateRight45 || proposed == ActionRequest::RotateLeft90 || proposed == ActionRequest::RotateRight90) && dangerHere) {
        if (!dangerForward) {
            reason = "Rotating/standing still is fatal, moving forward is safe";
            return ActionRequest::MoveForward;
        }
        reason = "Rotating/standing still is fatal, shooting as last resort";
        return ActionRequest::Shoot;
    }

    if ((proposed == ActionRequest::MoveForward && dangerForward) || (proposed == ActionRequest::MoveBackward && dangerBackward)) {

    // Check if the obstacle is the other tank — don't override, let shooting logic decide
    Position checkPos = (proposed == ActionRequest::MoveForward) ? pos.move(dir) : pos.move(opposite(dir));
    checkPos = board.wrapPosition(checkPos);
    const Tile& obstacle = board.getTile(checkPos);

    if ((tank.getPlayerId() == 1 && obstacle.isTank2()) || (tank.getPlayerId() == 2 && obstacle.isTank1())) {
        // Allow shooting logic to take over
    } 
    else if (!dangerHere) {
        reason = "Proposed move is dangerous, staying put is safer";
        return ActionRequest::DoNothing;
    } 
    else {
        reason = "Move leads to death, shooting as last resort";
        return ActionRequest::Shoot;
    }
}

    if (proposed == ActionRequest::Shoot && dangerHere) {
        if (!dangerForward) {
            reason = "Shooting while staying here is fatal, moving forward instead";
            return ActionRequest::MoveForward;
        }
        reason = "Shooting while staying here is fatal, rotate to reposition";
        return ActionRequest::RotateRight45;
    }

    // Final layer: shoot if close and aligned, or rotate toward enemy
    if (proposed != ActionRequest::Shoot && tank.canShoot()) {
        for (int y = 0; y < board.getHeight(); ++y) {
            for (int x = 0; x < board.getWidth(); ++x) {
                const Tile& t = board.getTile(x, y);
                if ((tank.getPlayerId() == 1 && t.isTank2()) || (tank.getPlayerId() == 2 && t.isTank1())) {
                    Position enemy = {x, y};
    
                    // 📏 Wraparound-aware distance
                    int dx = std::min(std::abs(enemy.x - pos.x), board.getWidth()  - std::abs(enemy.x - pos.x));
                    int dy = std::min(std::abs(enemy.y - pos.y), board.getHeight() - std::abs(enemy.y - pos.y));
                    int dist = std::max(dx, dy);
    
                    Direction toEnemy = directionTo(pos, enemy, board.getWidth(), board.getHeight());
                    if (dist <= 2) {
                        if (dir == toEnemy) {
                            reason = "Enemy is in range and aligned, override to shoot";
                            return ActionRequest::Shoot;
                        } else {
                            reason = "Enemy is close but not aligned, rotate toward them";
                            return rotateToward(dir, toEnemy);
                        }
                    }
                }
            }
        }
    }
    

    reason = "Proposed action deemed safe and reasonable";
    return proposed;
}