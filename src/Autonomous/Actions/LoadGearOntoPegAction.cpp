#include "LoadGearOntoPegAction.h"
#include <Robot.h>

LoadGearOntoPegAction::LoadGearOntoPegAction(){
	m_punchIsOut = false;
}

void LoadGearOntoPegAction::actionInit(){
	Robot->gearSubsystem.autoPlaceGear();
}

COREAutonAction::actionStatus LoadGearOntoPegAction::action() {
	return COREAutonAction::actionStatus::END;
}

void LoadGearOntoPegAction::actionEnd() {
}
