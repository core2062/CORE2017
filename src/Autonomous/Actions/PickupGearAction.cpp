#include "PickupGearAction.h"
#include <Robot.h>

PickupGearAction::PickupGearAction(){
	m_punchIsOut = false;
}

void PickupGearAction::actionInit(){
	Robot->gearSubsystem.pickupGear();
	m_endTimer.Reset();
	m_endTimer.Start();

}

COREAutonAction::actionStatus PickupGearAction::action() {
	if(m_endTimer.Get() > 3.5){
		Robot->gearSubsystem.safePickup();
		return COREAutonAction::actionStatus::END;
	}

	return COREAutonAction::actionStatus::CONTINUE;
}

void PickupGearAction::actionEnd() {
}
