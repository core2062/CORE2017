#include "DriveWaypointAction.h"
#include "Robot.h"

DriveWaypointAction::DriveWaypointAction(Path path, bool reversed,
		double tolerance, double maxAccel) {
	m_path = path;
	m_reversed = reversed;
	m_tolerance = tolerance;
	m_maxAccel = maxAccel;
}

void DriveWaypointAction::actionInit() {
	if(Robot->driveWaypointController != nullptr){
		Robot->driveWaypointController->startPath(m_path, m_reversed, m_maxAccel, m_tolerance);
		Robot->driveSubsystem.setController(Robot->driveWaypointController);
	}
}

DriveWaypointAction::actionStatus DriveWaypointAction::action() {
	if(Robot->driveWaypointController != nullptr){
		if(!Robot->driveWaypointController->isDone()){
			return actionStatus::CONTINUE;
		}
	}
	return actionStatus::END;
}

void DriveWaypointAction::actionEnd() {
	Robot->driveSubsystem.setController(nullptr);
}
