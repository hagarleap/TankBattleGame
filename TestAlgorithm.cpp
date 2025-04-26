#include "TestAlgorithm.h"
#include <iostream>


TankAction TestAlgorithm::getNextAction(const Tank& self) {
    // Example:
    // P1 tanks move forward forever
    // P2 tanks shoot every 5 steps (cooldown permitting)
    if (self.getPlayerId() == 1) return TankAction::MoveBackward;
    return TankAction::None;
    
    
    

}
