#include "LoadGearOntoPegAction.h"
#include <Robot.h>

LoadGearOntoPegAction::LoadGearOntoPegAction(){
	m_punchIsOut = false;
}

void LoadGearOntoPegAction::actionInit(){
}

COREAutonAction::actionStatus LoadGearOntoPegAction::action() {
	//If the solenoid is not deployed, then punch the solenoid
	if (m_punchIsOut == false){
		Robot->gearSubsystem.punchOut();
		m_punchIsOut = true;
	}
	//Else if solenoid is deployed, then pull back punch solenoid
	if (m_punchIsOut == true){
		if(Robot->gearSubsystem.checkPunchShouldClose() == true){
			Robot->gearSubsystem.punchIn();
			m_punchIsOut = false;
		}
	}

	return COREAutonAction::actionStatus::END;

}

void LoadGearOntoPegAction::actionEnd() {
}
