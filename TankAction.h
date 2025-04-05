#ifndef TANK_ACTION_H
#define TANK_ACTION_H

#include <string_view>

enum class TankAction {
    None,             // No action
    MoveForward,      // 1 game step
    MoveBackward,     // Wait 2 steps, move on 3rd (unless canceled)
    RotateLeft_1_8,   // 1 game step
    RotateRight_1_8,  // 1 game step
    RotateLeft_1_4,   // 1 game step
    RotateRight_1_4,  // 1 game step
    Shoot             // 1 game step, 4-step cooldown after
};

// Optional: for debug/logging
constexpr std::string_view to_string(TankAction action) {
    switch (action) {
        case TankAction::None: return "None";
        case TankAction::MoveForward: return "Move Forward";
        case TankAction::MoveBackward: return "Move Backward";
        case TankAction::RotateLeft_1_8: return "Rotate Left 1/8";
        case TankAction::RotateRight_1_8: return "Rotate Right 1/8";
        case TankAction::RotateLeft_1_4: return "Rotate Left 1/4";
        case TankAction::RotateRight_1_4: return "Rotate Right 1/4";
        case TankAction::Shoot: return "Shoot";
        default: return "Unknown";
    }
}

#endif // TANK_ACTION_H
