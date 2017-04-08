#include "LoadGearOntoPegAction.h"
#include <Robot.h>

LoadGearOntoPegAction::LoadGearOntoPegAction(){
	m_punchIsOut = false;
}

void LoadGearOntoPegAction::actionInit(){
	std::cout << "Punch Out" << std::endl;
#ifdef GEAR_PICKUP
	Robot->gearSubsystem.placeGear();
	m_endTimer.Reset();
	m_endTimer.Start();
#else
	Robot->gearSubsystem.punchOut();
#endif
}

COREAutonAction::actionStatus LoadGearOntoPegAction::action() {
#ifdef GEAR_PICKUP
	if(m_endTimer.Get() > 1.5){
		Robot->gearSubsystem.holdIn();
		return COREAutonAction::actionStatus::END;
	}
//	if(Robot->gearSubsystem.getState() == GearPickupState::HOLDING){
//		return COREAutonAction::actionStatus::END;
//	}
#else
	if(Robot->gearSubsystem.checkPunchShouldClose()){
		Robot->gearSubsystem.punchIn();
		return COREAutonAction::actionStatus::END;
	}
#endif

	return COREAutonAction::actionStatus::CONTINUE;


}

void LoadGearOntoPegAction::actionEnd() {
}
