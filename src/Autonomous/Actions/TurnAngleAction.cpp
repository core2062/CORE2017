#include "TurnAngleAction.h"
#include "Robot.h"

TurnAngleAction::TurnAngleAction(Rotation2d target, double tolerance): m_target(target), m_tolerance(tolerance){

}

void TurnAngleAction::actionInit() {
	Robot->driveSubsystem.setLowGear(true);
    Robot->driveSubsystem.teleopInit();
}

COREAutonAction::actionStatus TurnAngleAction::action() {
	Position2d pos = TankTracker::GetInstance()->getLatestFieldToVehicle();
	double error = m_target.rotateBy(pos.getRotation().inverse()).getDegrees();
	if(fabs(error) < m_tolerance){
		Robot->driveSubsystem.setMotorSpeed(0,0);
		return COREAutonAction::END;
	} else {
		double rot = error * Robot->driveSubsystem.driveTurnkP.Get();
		VelocityPair speeds = COREEtherDrive::calculate(0, rot, .01);
		Robot->driveSubsystem.setMotorSpeed(speeds.left, speeds.right);
	}

    return COREAutonAction::CONTINUE;
}

void TurnAngleAction::actionEnd() {
}
