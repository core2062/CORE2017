#include "DriveGyroController.h"
#include "Robot.h"

DriveGyroController::DriveGyroController(double target, double tolerance, bool relative) {
	if(relative){
		m_target = Robot->driveSubsystem.getGyroAngle().rotateBy(Rotation2d::fromDegrees(target));
	} else {
		m_target = Rotation2d::fromDegrees(target);
	}
	m_tolerance = tolerance;
	m_error = 999999;
}

void DriveGyroController::init(double target, double tolerance, bool relative) {
	if(relative){
		m_target = Robot->driveSubsystem.getGyroAngle().rotateBy(Rotation2d::fromDegrees(target));
	} else {
		m_target = Rotation2d::fromDegrees(target);
	}
	m_tolerance = tolerance;
	m_error = getError();
}

void DriveGyroController::postLoopTask() {
	if(isEnabled() && (Robot->getMode() == CORERobot::gameMode::AUTON)){
		enabledLoop();
	}
}

void DriveGyroController::enabledLoop() {
	m_error = getError();

	double output = m_error * Robot->driveSubsystem.driveTurnkP.Get();
	Robot->driveSubsystem.setMotorSpeed(output, -output);
}

bool DriveGyroController::isDone() {
	return (abs(m_error) < m_tolerance);
}

double DriveGyroController::getError() {
	double errorA =  m_target.getDegrees() - Robot->driveSubsystem.getGyroAngle().getDegrees();
	double errorB =  m_target.opposite().getDegrees() - Robot->driveSubsystem.getGyroAngle().opposite().getDegrees();
	double bestError;
	if(errorA <= errorB){
		bestError = errorA;
	} else {
		bestError = errorB;
	}
	return bestError;
}
