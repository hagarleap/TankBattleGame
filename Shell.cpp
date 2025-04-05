#include "Shell.h"

Shell::Shell(Position pos, Direction dir)
    : position(pos), direction(dir), active(true) {}

void Shell::advance() {
    if (!active) return;

    // Move by ±2 units in x/y depending on direction
    // Dummy implementation — you’ll replace this with real logic
    switch (direction) {
        case Direction::R: position.x += 2; break;
        case Direction::L: position.x -= 2; break;
        // Add other directions...
        default: break;
    }
}

Position Shell::getPosition() const {
    return position;
}

bool Shell::isActive() const {
    return active;
}
