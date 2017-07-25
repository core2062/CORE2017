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
			Robot->driveSubsystem.m_swerveDrive->tank(1, 1);
			return actionStatus::CONTINUE;
		}
		else{
			Robot->driveSubsystem.m_swerveDrive->tank(0, 0);
		}
	break;
	case GearPosition::LOW_GEAR:
		if(Robot->driveSubsystem.getDistanceInInches(DriveSide::BOTH) != 120){
			Robot->driveSubsystem.m_swerveDrive->tank(1, 1);
				return actionStatus::CONTINUE;
		}
		else{
			Robot->driveSubsystem.m_swerveDrive->tank(1, 1);
		}
	break;
	default:
		if(Robot->driveSubsystem.getDistanceInInches(DriveSide::BOTH) != 120){
				Robot->driveSubsystem.m_swerveDrive->tank(1, 1);
				return actionStatus::CONTINUE;
		}
		else{
			Robot->driveSubsystem.m_swerveDrive->tank(0, 0);
		}
	break;
	};
	return actionStatus::END;
}

void DriveForwardWithoutPathAction::actionEnd() {
	Robot->driveSubsystem.m_swerveDrive->tank(0, 0);
}

