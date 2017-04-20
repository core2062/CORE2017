#include "VisionAlignGearAction.h"
#include "Robot.h"

VisionAlignGearAction::VisionAlignGearAction():
	m_turnMult("Vision Turn Multiplier", 0.0)
{}

void VisionAlignGearAction::actionInit() {
	Robot->driveSubsystem.setLowGear(true);
    Robot->driveSubsystem.teleopInit();
}

COREAutonAction::actionStatus VisionAlignGearAction::action() {
	double magError = Robot->visionSubsystem.getUltraDist() - Robot->visionSubsystem.gearPlaceDist.Get();
//	double rotError = Robot->visionSubsystem.getError().getDegrees();
//	double rot = rotError * Robot->driveSubsystem.driveTurnkP.Get();
	double rot = Robot->visionSubsystem.getErrorPercent() * m_turnMult.Get();
	if(magError < 1){
		Robot->driveSubsystem.setMotorSpeed(0,0);
		return COREAutonAction::END;
	} else {
		double mag = magError * Robot->visionSubsystem.ultrakP.Get();
		if(mag < .2){
			mag = .2;
		}
		VelocityPair speeds = COREEtherDrive::calculate(-mag, rot, .05);
		Robot->driveSubsystem.setMotorSpeed(speeds.left, speeds.right);
	}
	return COREAutonAction::CONTINUE;
}

void VisionAlignGearAction::actionEnd() {

}
