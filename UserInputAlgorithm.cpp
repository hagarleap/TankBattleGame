#include "UserInputAlgorithm.h"
#include <iostream>
#include "Tile.h"

TankAction UserInputAlgorithm::decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) {
    (void)shells;
    std::cout << std::endl;
    std::cout << "+" << std::string(board.getWidth(), '-') << "+" << std::endl;
    for (int y = 0; y < board.getHeight(); ++y) {
        std::cout << "|";
        for (int x = 0; x < board.getWidth(); ++x) {
            const Tile& tile = board.getTile(x, y);
            switch (tile.getType()) {
                case TileType::WALL: std::cout << "#"; break;
                case TileType::MINE: std::cout << "@"; break;
                case TileType::TANK1: std::cout << "1"; break;
                case TileType::TANK2: std::cout << "2"; break;
                case TileType::SHELL: std::cout << "*"; break;
                default: std::cout << " ";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "+" << std::string(board.getWidth(), '-') << "+" << std::endl;

    std::cout << "\n[UserInput] Tank P" << tank.getPlayerId() << " ID " << tank.getTankId() << ": Enter action (f=forward, b=backward, l=left8, r=right8, L=left4, R=right4, s=shoot, n=none): ";
    char c;
    std::cin >> c;

    static const std::unordered_map<char, TankAction> map = {
        {'f', TankAction::MoveForward},
        {'b', TankAction::MoveBackward},
        {'l', TankAction::RotateLeft8},
        {'r', TankAction::RotateRight8},
        {'L', TankAction::RotateLeft4},
        {'R', TankAction::RotateRight4},
        {'s', TankAction::Shoot},
        {'n', TankAction::None}
    };

    auto it = map.find(c);
    if (it != map.end()) return it->second;
    std::cout << "Invalid input, doing nothing.\n";
    return TankAction::None;
}