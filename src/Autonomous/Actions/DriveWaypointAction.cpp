#include "DriveWaypointAction.h"
#include "Robot.h"
#include "CORERobotLib.h"

DriveWaypointAction::DriveWaypointAction(Path* path, bool reversed,
		double tolerance, double maxAccel, bool gradualStop) {
	m_path = path;
	m_reversed = reversed;
	m_tolerance = tolerance;
	m_maxAccel = maxAccel;
	m_gradualStop = gradualStop;
}

void DriveWaypointAction::actionInit() {
	Robot->driveSubsystem.followPath(*m_path, m_reversed, m_maxAccel, m_tolerance, m_gradualStop);
}

DriveWaypointAction::actionStatus DriveWaypointAction::action() {
	if(!Robot->driveSubsystem.pathDone()){
		return actionStatus::CONTINUE;
	}
	std::cout << "Waypoint Action Done" << std::endl;
	return actionStatus::END;
}

void DriveWaypointAction::actionEnd() {
	Robot->driveSubsystem.setController(nullptr);
}
