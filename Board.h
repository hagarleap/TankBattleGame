#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <vector>
#include <string>

class Board {
public:
    Board(int width, int height);
    
    bool loadFromFile(const std::string& filename, std::vector<Position>& tankPositionsP1, std::vector<Position>& tankPositionsP2);
    
    int getWidth() const;
    int getHeight() const;
    
    Tile& getTile(int x, int y);
    const Tile& getTile(int x, int y) const;

    void print() const;

private:
    int width;
    int height;
    std::vector<std::vector<Tile>> tiles;

    void initEmpty();
};

#endif // BOARD_H
