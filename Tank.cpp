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

void Tank::moveForward() {
    previousPosition = position;
    position = position.move(direction, 1); // move 1 step in current direction
}

void Tank::moveBackward() {
    previousPosition = position;
    position = position.move(opposite(direction), 1); // move 1 step backward
}

void Tank::rotateRight8() {
    rotateR8(direction); // turn 1/8 right
}

void Tank::rotateLeft8() {
    rotateL8(direction); // turn 1/8 left
}

void Tank::rotateRight4() {
    rotateR4(direction); // turn 1/4 right (2 steps)
}

void Tank::rotateLeft4() {
    rotateL4(direction); // turn 1/4 left (2 steps)
}

void Tank::cancelMove() {
    position = previousPosition;
}

void Tank::setDirection(Direction newDir) {
    direction = newDir;
}

// void Tank::queueAction(TankAction action) {
//     actionQueue.push(action);
// }



// TankAction Tank::nextAction() {
//     if (actionQueue.empty()) return TankAction::None;
//     TankAction action = actionQueue.front();
//     actionQueue.pop();
//     return action;
// }

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

bool Tank::isAlive() const {
    return !destroyed;
}

void Tank::destroy() {
    destroyed = true;
}


std::string Tank::toString() const {
    std::ostringstream oss;
    oss << "Tank(P" << playerId << ", ID " << tankId << ") at (" << position.x << "," << position.y << ")";
    return oss.str();
}
