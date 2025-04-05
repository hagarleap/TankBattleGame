#include "Tank.h"
#include <sstream>

Tank::Tank(int playerId, int tankId, Position startPos, Direction startDir)
    : playerId(playerId), tankId(tankId), position(startPos), direction(startDir) {}

int Tank::getPlayerId() const {
    return playerId;
}

int Tank::getTankId() const {
    return tankId;
}

Position Tank::getPosition() const {
    return position;
}

Direction Tank::getDirection() const {
    return direction;
}

void Tank::setPosition(Position newPos) {
    position = newPos;
}

void Tank::setDirection(Direction newDir) {
    direction = newDir;
}

void Tank::queueAction(Action action) {
    actionQueue.push(action);
}

Action Tank::nextAction() {
    if (actionQueue.empty()) return Action::None;
    Action action = actionQueue.front();
    actionQueue.pop();
    return action;
}

bool Tank::canShoot() const {
    return shootCooldown == 0 && shellsLeft > 0;
}

void Tank::onShoot() {
    if (canShoot()) {
        shootCooldown = 4;
        --shellsLeft;
    }
}

void Tank::tickCooldown() {
    if (shootCooldown > 0) --shootCooldown;
}

int Tank::getShellsLeft() const {
    return shellsLeft;
}

std::string Tank::toString() const {
    std::ostringstream oss;
    oss << "Tank(P" << playerId << ", ID " << tankId << ") at (" << position.x << "," << position.y << ")";
    return oss.str();
}
