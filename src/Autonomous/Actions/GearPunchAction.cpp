#include "GearPunchAction.h"
#include "Robot.h"

GearPunchAction::GearPunchAction() {

}
void GearPunchAction::actionInit(){
	Robot->gearSubsystem.punchIn();
}
COREAutonAction::actionStatus GearPunchAction::action(){
	if (Robot->gearSubsystem.checkPunchShouldClose() == false){
		Robot->gearSubsystem.punchOut();
	}else {
		Robot->gearSubsystem.punchIn();
	}
	return COREAutonAction::END;
}
void GearPunchAction::actionEnd() {

}



