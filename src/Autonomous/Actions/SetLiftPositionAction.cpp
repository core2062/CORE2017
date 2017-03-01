#include "Robot.h"
#include "SetLiftPositionAction.h"



SetLiftPositionAction::SetLiftPositionAction(bool setLiftTop, bool setLiftBottom): m_setLiftTop(setLiftTop),
											m_setLiftBottom(setLiftBottom) {
}

void SetLiftPositionAction::actionInit() {
	Robot->hopperSubsystem.setLiftBottom();
}

COREAutonAction::actionStatus SetLiftPositionAction::action() {
	//TODO Change so that it can be given a position value
	if (Robot->hopperSubsystem.hopperIsDown() == true){
		Robot->hopperSubsystem.setLiftTop();
	}else {
		Robot->hopperSubsystem.setLiftBottom();
	}
	return COREAutonAction::END;
}

void SetLiftPositionAction::actionEnd() {
}
