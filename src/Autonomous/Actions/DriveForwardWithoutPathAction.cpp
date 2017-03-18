#include "Robot.h"
#include "DriveForwardWithoutPathAction.h"
#include "CORERobotLib.h"

DriveForwardWithoutPathAction::DriveForwardWithoutPathAction(GearPosition gearPosition) {
	m_gearPosition = gearPosition;
}

void DriveForwardWithoutPathAction::actionInit() {

}

COREAutonAction::actionStatus DriveForwardWithoutPathAction::action() {
	switch(m_gearPosition){

	case GearPosition::HIGH_GEAR:
		if(Robot->driveSubsystem.getDistanceInInches(DriveSide::BOTH) != 120){
			Robot->driveSubsystem.setHighGear(true);
			Robot->driveSubsystem.setMotorSpeed(1.0, 1.0);
			return actionStatus::CONTINUE;
		}
		else{
			Robot->driveSubsystem.setMotorSpeed(0.0, 0.0);
		}
	break;
	case GearPosition::LOW_GEAR:
		if(Robot->driveSubsystem.getDistanceInInches(DriveSide::BOTH) != 120){
				Robot->driveSubsystem.setLowGear(true);
				Robot->driveSubsystem.setMotorSpeed(1.0, 1.0);
				return actionStatus::CONTINUE;
		}
		else{
			Robot->driveSubsystem.setMotorSpeed(0.0, 0.0);
		}
	break;
	default:
		if(Robot->driveSubsystem.getDistanceInInches(DriveSide::BOTH) != 120){
				Robot->driveSubsystem.setLowGear(true);
				Robot->driveSubsystem.setMotorSpeed(1.0, 1.0);
				return actionStatus::CONTINUE;
		}
		else{
			Robot->driveSubsystem.setMotorSpeed(0.0, 0.0);
		}
	break;
	};
	return actionStatus::END;
}

void DriveForwardWithoutPathAction::actionEnd() {
	Robot->driveSubsystem.setMotorSpeed(0.0, 0.0);
}

