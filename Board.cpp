#include "Board.h"
#include "TileType.h"
#include <fstream>
#include <iostream>

Board::Board(int width, int height) : width(width), height(height) {
    initEmpty();
}

void Board::initEmpty() {
    tiles.resize(height, std::vector<Tile>(width, Tile(Position{0, 0}, TileType::Empty)));
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            tiles[y][x] = Tile(Position{x, y});
}

bool Board::loadFromFile(const std::string& filename, std::vector<Position>& tankP1, std::vector<Position>& tankP2) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) return false;

    std::string line;
    int row = 0;
    while (std::getline(inFile, line) && row < height) {
        for (int col = 0; col < std::min(width, (int)line.length()); ++col) {
            char c = line[col];
            Position pos{col, row};
            switch (c) {
                case '#': tiles[row][col] = Tile(pos, TileType::Wall); break;
                case '@': tiles[row][col] = Tile(pos, TileType::Mine); break;
                case '1':
                    tiles[row][col] = Tile(pos, TileType::Spawn1);
                    tankP1.push_back(pos);
                    break;
                case '2':
                    tiles[row][col] = Tile(pos, TileType::Spawn2);
                    tankP2.push_back(pos);
                    break;
                default:
                    tiles[row][col] = Tile(pos, TileType::Empty);
            }
        }
        ++row;
    }

    return true;
}

int Board::getWidth() const { return width; }
int Board::getHeight() const { return height; }

Tile& Board::getTile(int x, int y) {
    return tiles[y][x];
}

const Tile& Board::getTile(int x, int y) const {
    return tiles[y][x];
}

void Board::print() const {
    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            switch (tile.getType()) {
                case TileType::Wall: std::cout << "#"; break;
                case TileType::Mine: std::cout << "@"; break;
                case TileType::Spawn1: std::cout << "1"; break;
                case TileType::Spawn2: std::cout << "2"; break;
                default: std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}
