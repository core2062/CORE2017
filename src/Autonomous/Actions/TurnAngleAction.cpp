#include "TurnAngleAction.h"
#include "Robot.h"

TurnAngleAction::TurnAngleAction(Rotation2d target, double tolerance, int required): m_target(target), m_tolerance(tolerance), m_required(required){

}

void TurnAngleAction::actionInit() {
    Robot->driveSubsystem.teleopInit();
}

COREAutonAction::actionStatus TurnAngleAction::action() {
	Position2d pos = TankTracker::GetInstance()->getLatestFieldToVehicle();
	double error = m_target.rotateBy(pos.getRotation().inverse()).getDegrees();
	if(fabs(error) < m_tolerance){
		m_seen++;
		if(m_seen >= m_required){
			Robot->driveSubsystem.setMotorSpeed(0,0);
			return COREAutonAction::END;
		}
	} else {
		m_seen = 0;
	}

	double rot = error * Robot->driveSubsystem.driveTurnkP.Get();
	VelocityPair speeds = COREEtherDrive::calculate(0, rot, .01);
	Robot->driveSubsystem.setMotorSpeed(speeds.left, speeds.right);

    return COREAutonAction::CONTINUE;
}

void TurnAngleAction::actionEnd() {
}
