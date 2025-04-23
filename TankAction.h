
#ifndef TANK_ACTION_H
#define TANK_ACTION_H

//#include <string_view>

enum class TankAction {
    None,             // No action
    MoveForward,      // 1 game step
    MoveBackward,     // Wait 2 steps, move on 3rd (unless canceled)
    RotateLeft8,   // 1 game step
    RotateRight8,  // 1 game step
    RotateLeft4,   // 1 game step
    RotateRight4,  // 1 game step
    Shoot             // 1 game step, 4-step cooldown after
};

// Optional: for debug/logging
inline const char* to_string(TankAction action) {
    switch (action) {
        case TankAction::None: return "None";
        case TankAction::MoveForward: return "Move Forward";
        case TankAction::MoveBackward: return "Move Backward";
        case TankAction::RotateLeft8: return "Rotate Left 1/8";
        case TankAction::RotateRight8: return "Rotate Right 1/8";
        case TankAction::RotateLeft4: return "Rotate Left 1/4";
        case TankAction::RotateRight4: return "Rotate Right 1/4";
        case TankAction::Shoot: return "Shoot";
        default: return "Unknown";
    }
}

#endif // TANK_ACTION_H
