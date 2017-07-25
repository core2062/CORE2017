#include "PickupGearWithVisionAction.h"
#include "Robot.h"

using namespace CORE;

PickupGearWithVisionAction::PickupGearWithVisionAction(double pixelViewRange, double ultraDistance,
		double secondsAfterPickupIsDown):
	m_cameraStabilizationInterval(){
	m_pixelViewRange = pixelViewRange;
	m_ultraDistance = ultraDistance;
	m_secondsAfterPickupIsDown = secondsAfterPickupIsDown;

}

void PickupGearWithVisionAction::actionInit(){
	Robot->visionSubsystem.visionTable->PutBoolean("disableVision", false);
	Robot->driveSubsystem.setLowGear(true);
	Robot->driveSubsystem.m_swerveDrive->tank(.75, .75);
	Robot->gearSubsystem.safePickup();
	m_cameraStabilizationInterval.Reset();
	m_cameraStabilizationInterval.Start();

}

COREAutonAction::actionStatus PickupGearWithVisionAction::action(){
	double elapsed = m_cameraStabilizationInterval.Get();
	if (elapsed > m_secondsAfterPickupIsDown){
		if(abs(Robot->visionSubsystem.getGearX() - 208) < m_pixelViewRange){
			Robot->driveSubsystem.m_swerveDrive->tank(0.5, 0.5);
		} else if(Robot->visionSubsystem.getGearX() > 208) {
			Robot->driveSubsystem.m_swerveDrive->tank(.75, .5);
		} else {
			Robot->driveSubsystem.m_swerveDrive->tank(0.5, 0.75);
		}
	}
	if (Robot->visionSubsystem.getUltraDist() < m_ultraDistance){
		Robot->driveSubsystem.m_swerveDrive->tank(0, 0);
		return COREAutonAction::actionStatus::END;
	}
	return COREAutonAction::actionStatus::CONTINUE;
}

void PickupGearWithVisionAction::actionEnd(){
	Robot->visionSubsystem.visionTable->PutBoolean("disableVision", true);
	Robot->driveSubsystem.m_swerveDrive->tank(0, 0);
}
//Width of 416 total if on right, turn  5-10 degrees, if on left turn right 5-10 degrees
