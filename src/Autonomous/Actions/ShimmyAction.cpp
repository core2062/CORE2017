#include "ShimmyAction.h"
#include "Math.h"
#include "Robot.h"

ShimmyAction::ShimmyAction(double numberOfSeconds, double dir):m_shimmyTimer(){
	m_numberOfSeconds = numberOfSeconds;
	m_dir = dir;
}

void ShimmyAction::actionInit() {
	Robot->driveSubsystem.setLowGear(true);
    Robot->driveSubsystem.teleopInit();
    m_shimmyTimer.Reset();
    m_shimmyTimer.Start();
}

COREAutonAction::actionStatus ShimmyAction::action() {
	double elapsed = m_shimmyTimer.Get();

	double mag = .25 * m_dir;
	double rot = cos(4*elapsed);
	VelocityPair speeds = COREEtherDrive::calculate(mag, rot, .1);

	Robot->driveSubsystem.setMotorSpeed(speeds.left, speeds.right);

	if(elapsed > m_numberOfSeconds){
		Robot->driveSubsystem.setMotorSpeed(0,0);
		return COREAutonAction::actionStatus::END;
	}

	return COREAutonAction::actionStatus::CONTINUE;
}

void ShimmyAction::actionEnd() {
	Robot->driveSubsystem.setMotorSpeed(0.0, 0.0);
}


