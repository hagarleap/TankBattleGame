#include "TestAlgorithm.h"
#include <iostream>


ActionRequest TestAlgorithm::getNextAction(const Tank& self) {
    // Example:
    // P1 tanks move forward forever
    // P2 tanks shoot every 5 steps (cooldown permitting)
    if (self.getPlayerId() == 1) return ActionRequest::MoveBackward;
    return ActionRequest::DoNothing;
    
    
    

}
