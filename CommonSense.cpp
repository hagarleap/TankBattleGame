#include "Algorithm.h"
#include <cmath>

bool isDangerousPosition(const Position& pos, const Board& board, const std::vector<Shell>& shells) {
    for (const Shell& shell : shells) {
        Position sPos = shell.getPosition();
        Direction dir = shell.getDirection();
        for (int i = 1; i <= 3; ++i) {
            Position next = sPos.move(dir, 2 * i);
            if (next == pos) return true;
            if (board.getTile(next).isWall()) break;
        }
    }
    return board.getTile(pos).isMine() || board.getTile(pos).isOccupied();
}

bool canShootOpponent(const Tank& tank, const Board& board) {
    Position pos = tank.getPosition();
    Direction dir = tank.getDirection();
    for (int i = 1; i <= 4; ++i) {
        Position forward = pos.move(dir, i);
        if (forward.x < 0 || forward.y < 0 || forward.x >= board.getWidth() || forward.y >= board.getHeight()) break;
        const Tile& t = board.getTile(forward);
        if (t.isWall()) break;
        if ((tank.getPlayerId() == 1 && t.isTank2()) || (tank.getPlayerId() == 2 && t.isTank1())) return true;
    }
    return false;
}

Direction directionTo(const Position& from, const Position& to) {
    int dxVal = to.x - from.x;
    int dyVal = to.y - from.y;
    if (dxVal > 0 && dyVal > 0) return Direction::DR;
    if (dxVal > 0 && dyVal < 0) return Direction::UR;
    if (dxVal < 0 && dyVal > 0) return Direction::DL;
    if (dxVal < 0 && dyVal < 0) return Direction::UL;
    if (dxVal > 0) return Direction::R;
    if (dxVal < 0) return Direction::L;
    if (dyVal > 0) return Direction::D;
    return Direction::U;
}

TankAction rotateToward(Direction current, Direction target) {
    int cur = static_cast<int>(current);
    int tgt = static_cast<int>(target);
    int diff = (tgt - cur + 8) % 8;
    if (diff == 0) return TankAction::None;
    if (diff == 1 || diff == 2) return TankAction::RotateRight8;
    if (diff == 7 || diff == 6) return TankAction::RotateLeft8;
    return (diff <= 4) ? TankAction::RotateRight4 : TankAction::RotateLeft4;
}

TankAction applyCommonSense(const Tank& tank, const Board& board, const std::vector<Shell>& shells, TankAction proposed, std::string& reason) {
    Position pos = tank.getPosition();
    Direction dir = tank.getDirection();
    Position forward = pos.move(dir);
    Position backward = pos.move(opposite(dir));

    bool dangerHere = isDangerousPosition(pos, board, shells);
    bool dangerForward = isDangerousPosition(forward, board, shells);
    bool dangerBackward = isDangerousPosition(backward, board, shells);

    if ((proposed == TankAction::None || proposed == TankAction::RotateLeft8 || proposed == TankAction::RotateRight8 || proposed == TankAction::RotateLeft4 || proposed == TankAction::RotateRight4) && dangerHere) {
        if (!dangerForward) {
            reason = "Rotating/standing still is fatal, moving forward is safe";
            return TankAction::MoveForward;
        }
        if (!dangerBackward) {
            reason = "Rotating/standing still is fatal, moving backward is safe";
            return TankAction::MoveBackward;
        }
        reason = "Rotating/standing still is fatal, shooting as last resort";
        return TankAction::Shoot;
    }

    if ((proposed == TankAction::MoveForward && dangerForward) || (proposed == TankAction::MoveBackward && dangerBackward)) {
        if (!dangerHere) {
            reason = "Proposed move is dangerous, staying put is safer";
            return TankAction::None;
        }
        reason = "Move leads to death, shooting as last resort";
        return TankAction::Shoot;
    }

    if (proposed == TankAction::Shoot && dangerHere) {
        if (!dangerForward) {
            reason = "Shooting while staying here is fatal, moving forward instead";
            return TankAction::MoveForward;
        }
        reason = "Shooting while staying here is fatal, rotate to reposition";
        return TankAction::RotateRight8;
    }

    // Final layer: shoot if close and aligned, or rotate toward enemy
    if (proposed != TankAction::Shoot && tank.canShoot()) {
        for (int y = 0; y < board.getHeight(); ++y) {
            for (int x = 0; x < board.getWidth(); ++x) {
                const Tile& t = board.getTile(x, y);
                if ((tank.getPlayerId() == 1 && t.isTank2()) || (tank.getPlayerId() == 2 && t.isTank1())) {
                    Position enemy = {x, y};
                    int dist = std::max(std::abs(enemy.x - pos.x), std::abs(enemy.y - pos.y));
                    Direction toEnemy = directionTo(pos, enemy);
                    if (dist <= 4) {
                        if (dir == toEnemy) {
                            reason = "Enemy is in range and aligned, override to shoot";
                            return TankAction::Shoot;
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