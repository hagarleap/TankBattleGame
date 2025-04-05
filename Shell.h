#ifndef SHELL_H
#define SHELL_H

#include "Position.h"
#include "Direction.h"

class Shell {
public:
    Shell(Position pos, Direction dir);

    void advance();  // moves 2 squares per step
    Position getPosition() const;
    bool isActive() const;

private:
    Position position;
    Direction direction;
    bool active;
};

#endif // SHELL_H