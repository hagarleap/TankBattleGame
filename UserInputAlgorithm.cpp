#include "UserInputAlgorithm.h"
#include <iostream>
#include "Tile.h"

TankAction UserInputAlgorithm::decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) {
    (void)shells;
    (void)board;
    std::cout << std::endl;
    std::cout << "Current direction: ";

    switch (tank.getDirection()) {
        case Direction::U:  std::cout << "U"; break;
        case Direction::UR: std::cout << "UR"; break;
        case Direction::R:  std::cout << "R"; break;
        case Direction::DR: std::cout << "DR"; break;
        case Direction::D:  std::cout << "D"; break;
        case Direction::DL: std::cout << "DL"; break;
        case Direction::L:  std::cout << "L"; break;
        case Direction::UL: std::cout << "UL"; break;
    }
    std::cout << std::endl;

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