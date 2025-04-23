#include "TestAlgorithm.h"
#include <iostream>


TankAction TestAlgorithm::getNextAction(const Tank& self) {
    // Example:
    // P1 tanks move forward forever
    // P2 tanks shoot every 5 steps (cooldown permitting)
if (self.canShoot()){
    return TankAction::Shoot;
}
else{
    return TankAction::None;
}


}
