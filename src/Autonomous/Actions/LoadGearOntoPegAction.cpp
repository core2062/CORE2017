#include "LoadGearOntoPegAction.h"
#include <Robot.h>

LoadGearOntoPegAction::LoadGearOntoPegAction(){
	m_punchIsOut = false;
}

void LoadGearOntoPegAction::actionInit(){
	std::cout << "Punch Out" << std::endl;
	Robot->gearSubsystem.punchOut();
}

COREAutonAction::actionStatus LoadGearOntoPegAction::action() {
	if(Robot->gearSubsystem.checkPunchShouldClose()){
		Robot->gearSubsystem.punchIn();
		return COREAutonAction::actionStatus::END;
	}

	return COREAutonAction::actionStatus::CONTINUE;


}

void LoadGearOntoPegAction::actionEnd() {
}
