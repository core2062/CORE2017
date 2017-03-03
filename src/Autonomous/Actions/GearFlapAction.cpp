#include "Robot.h"
#include "GearFlapAction.h"
#include "Constants.h"

GearFlapAction::GearFlapAction(ActuationType actuationType) {
	m_actuationType = actuationType;
}
void GearFlapAction::actionInit() {
	Robot->gearSubsystem.closeFlap();
}
COREAutonAction::actionStatus GearFlapAction::action() {
	//TODO: Have arguments for opening, closing and toggle
	switch(m_actuationType){
	case ActuationType::OPEN:
		Robot->gearSubsystem.openFlap();
		break;
	case ActuationType::CLOSE:
		Robot->gearSubsystem.closeFlap();
		break;
	case ActuationType::TOGGLE:
		if (Robot->gearSubsystem.flapIsOpen() == true){
			Robot->gearSubsystem.closeFlap();
		}else{
			Robot->gearSubsystem.openFlap();
		}
		break;
	}
	return COREAutonAction::END;
}

void GearFlapAction::actionEnd() {

}
