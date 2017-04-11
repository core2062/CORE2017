#include "VisionAlignGearAction.h"
#include "Robot.h"

VisionAlignGearAction::VisionAlignGearAction(double maxAccel, bool gradualStop, bool continuousUpdate) /*: m_driveForward()*/ {
	m_maxAccel = maxAccel;
	m_gradualStop = gradualStop;
	m_continuousUpdate = continuousUpdate;
}

void VisionAlignGearAction::actionInit() {
	Robot->visionSubsystem.calculatePath();
	Robot->driveSubsystem.setFrame(Robot->visionSubsystem.getFrame());
	Robot->visionSubsystem.calculatePath();
	Robot->driveSubsystem.followPath(*Robot->visionSubsystem.getPath(), true, m_maxAccel, 0.25, m_gradualStop);
}

COREAutonAction::actionStatus VisionAlignGearAction::action() {
	if(!Robot->driveSubsystem.pathDone()){
		if (m_continuousUpdate){
			Robot->visionSubsystem.calculatePath();
			Robot->driveSubsystem.followPath(*Robot->visionSubsystem.getPath(), true, 99999999.9, 0.25, false);
		}
		return COREAutonAction::CONTINUE;
	}
	std::cout << "Waypoint Action Done" << std::endl;
	return COREAutonAction::END;
}

void VisionAlignGearAction::actionEnd() {
	Robot->driveSubsystem.setController(nullptr);
}
