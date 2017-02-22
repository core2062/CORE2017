#include "Robot.h"
#include "SetLiftPositionAction.h"



SetLiftPositionAction::SetLiftPositionAction(bool setLiftTop, bool setLiftBottom): m_setLiftTop(setLiftTop),
											m_setLiftBottom(setLiftBottom) {
}

void SetLiftPositionAction::actionInt() {
	Robot->hopperSubsystem.setLiftBottom();
}

COREAutonAction::actionStatus SetLiftPositionAction::action() {
	if (Robot->hopperSubsystem.hopperIsDown == true){
		Robot->hopperSubsystem.setLiftTop();
	}else{
		Robot->hopperSubsystem.setLiftBottom();
	}
}

void SetLiftPositionAction::actionEnd() {
}
