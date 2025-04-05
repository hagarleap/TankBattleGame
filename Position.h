#ifndef POSITION_H
#define POSITION_H

struct Position {
    int x;
    int y;

    bool operator==(const Position& other) const = default;
};

#endif // POSITION_H
