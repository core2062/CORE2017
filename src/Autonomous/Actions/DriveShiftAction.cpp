#include "DriveShiftAction.h"
#include "Constants.h"
#include "Robot.h"

DriveShiftAction::DriveShiftAction(GearPosition gearPosition) {
	m_gearPosition = gearPosition;
}

void DriveShiftAction::actionInit(){
}

COREAutonAction::actionStatus DriveShiftAction::action() {
	switch (m_gearPosition){
	case GearPosition::LOW_GEAR:
		std::cout << "Set low gear position" << std::endl;
		Robot->driveSubsystem.setLowGear(true);
		break;
	case GearPosition::HIGH_GEAR:
		std::cout << "Set high gear position" << std::endl;
		Robot->driveSubsystem.setHighGear(true);
		break;
	default:
		Robot->driveSubsystem.setLowGear(false);
	}
	return COREAutonAction::END;
}
void DriveShiftAction::actionEnd(){

}
