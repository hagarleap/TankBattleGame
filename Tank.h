#ifndef TANK_H
#define TANK_H

#include "Position.h"
#include "Direction.h"
#include "Action.h"
#include <queue>
#include <string>

class Tank {
public:
    Tank(int playerId, int tankId, Position startPos, Direction startDir);

    int getPlayerId() const;
    int getTankId() const;

    Position getPosition() const;
    Direction getDirection() const;

    void setPosition(Position newPos);
    void setDirection(Direction newDir);

    void queueAction(Action action);
    Action nextAction();

    bool canShoot() const;
    void onShoot();
    void tickCooldown();

    int getShellsLeft() const;

    std::string toString() const;

private:
    int playerId;
    int tankId;

    Position position;
    Direction direction;

    std::queue<Action> actionQueue;
    int shootCooldown = 0;
    int shellsLeft = 16;
};

#endif // TANK_H
