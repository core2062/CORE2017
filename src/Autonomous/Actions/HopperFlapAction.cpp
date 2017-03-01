#include "HopperFlapAction.h"
#include "Robot.h"

HopperFlapAction::HopperFlapAction() {

}
void HopperFlapAction::actionInit() {
	Robot->hopperSubsystem.closeFlap();
}
COREAutonAction::actionStatus HopperFlapAction::action() {
	if (Robot->hopperSubsystem.flapIsOpen() == true){
		Robot->hopperSubsystem.closeFlap();
	}else {
		Robot->hopperSubsystem.openFlap();
	}
	return COREAutonAction::END;
}
void HopperFlapAction::actionEnd() {

}




