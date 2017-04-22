#include "VisionPathAction.h"

#include "Robot.h"

VisionPathAction::VisionPathAction(bool continuousUpdate) /*: m_driveForward()*/ {
	m_continuousUpdate = continuousUpdate;
}

void VisionPathAction::actionInit() {
	Robot->visionSubsystem.calculatePath();
	Robot->driveSubsystem.setFrame(Robot->visionSubsystem.getFrame());
	Robot->driveSubsystem.followPath(*Robot->visionSubsystem.getPath(), true, 150.0);
}

COREAutonAction::actionStatus VisionPathAction::action() {
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

void VisionPathAction::actionEnd() {
	Robot->driveSubsystem.setFrame(nullptr);
	Robot->driveSubsystem.setController(nullptr);
}
