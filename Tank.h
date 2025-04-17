#ifndef TANK_H
#define TANK_H

#include "Position.h"
#include "Direction.h"
#include "TankAction.h"
#include <queue>
#include <string>

class Tank {
public:
    Tank(int playerId, int tankId, Position startPos, Direction startDir);

    int getPlayerId() const;
    int getTankId() const;

    Position getPosition() const;
    Direction getDirection() const;

    void setPosition(const Position& newPos);
    void setDirection(Direction newDir);

    void queueAction(TankAction action);
    TankAction nextAction();

    bool canShoot() const;
    void onShoot();
    void moveForward();
    void rotateRight4();
    void rotateRight8();
    void rotateLeft4();
    void rotateLeft8();
    void moveBackward();
    void cancelMove();
    void tickCooldown();

    int getShellsLeft() const;

    bool isAlive() const;
    void destroy();


    std::string toString() const;

private:
int tankId;
int playerId;
Position position;
Position previousPosition; 
Direction direction;
int shellsLeft = 16;
int shootCooldown = 0;
bool destroyed = false;
int backwardState = 0;
};

#endif // TANK_H
