#include "PickupGearAction.h"
#include <Robot.h>

PickupGearAction::PickupGearAction(bool up){
	m_up = up;
	m_punchIsOut = false;
}

void PickupGearAction::actionInit(){
	if(m_up){
		Robot->gearSubsystem.safePickup();
	} else {
		Robot->gearSubsystem.pickupGear();
	}

}

COREAutonAction::actionStatus PickupGearAction::action() {

	return COREAutonAction::actionStatus::END;
}

void PickupGearAction::actionEnd() {
}
