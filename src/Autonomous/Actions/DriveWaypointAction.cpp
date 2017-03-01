#include "DriveWaypointAction.h"
#include "Robot.h"
#include "CORERobotLib.h"

DriveWaypointAction::DriveWaypointAction(Path* path, bool reversed,
		double tolerance, double maxAccel) {
	m_path = path;
	m_reversed = reversed;
	m_tolerance = tolerance;
	m_maxAccel = maxAccel;
}

void DriveWaypointAction::actionInit() {
	Robot->driveSubsystem.followPath(*m_path, m_reversed, m_maxAccel, m_tolerance);
}

DriveWaypointAction::actionStatus DriveWaypointAction::action() {
	if(!Robot->driveSubsystem.pathDone()){
		return actionStatus::CONTINUE;
	}
	return actionStatus::END;
}

void DriveWaypointAction::actionEnd() {
	Robot->driveSubsystem.setController(nullptr);
}
