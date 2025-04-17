#include "Shell.h"

Shell::Shell(Position pos, Direction dir)
    : position(pos), direction(dir), active(true) {}

void Shell::advance() {
    if (!active) return;

    // Move by ±2 units in x/y depending on direction
    switch (direction) {
        case Direction::R: position.x += 1; break;
        case Direction::L: position.x -= 1; break;
        case Direction::U: position.y += 1; break;
        case Direction::D: position.y -= 1; break;
        case Direction::UL: position.x -= 1; position.y += 1; break;
        case Direction::UR: position.x += 1; position.y +=1; break;
        case Direction::DL: position.x -= 1; position.y -= 1; break;
        case Direction:: DR: position.x += 1; position.y -= 1; break;
        default: break;
    }
}

Position Shell::getPosition() const {
    return position;
}

bool Shell::isActive() const {
    return active;
}
