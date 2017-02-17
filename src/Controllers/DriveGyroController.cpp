#include "DriveGyroController.h"
#include "Robot.h"

DriveGyroController::DriveGyroController(double target, double tolerance, bool relative) {
	init(target, tolerance, relative);
}

void DriveGyroController::init(double target, double tolerance, bool relative) {
	if(relative){
		m_target = Robot::driveSubsystem->getGyroAngle().rotateBy(Rotation2d::fromDegrees(target));
	} else {
		m_target = Rotation2d::fromDegrees(target);
	}
	m_tolerance = tolerance;
}

void DriveGyroController::postLoopTask() {
	if(isEnabled()){
		enabledLoop();
	}
}

void DriveGyroController::enabledLoop() {
	double errorA =  m_target.getDegrees() - Robot::driveSubsystem->getGyroAngle().getDegrees();
	double errorB =  m_target.opposite().getDegrees() - Robot::driveSubsystem->getGyroAngle().opposite().getDegrees();
	if(errorA <= errorB){
		m_error = errorA;
	} else {
		m_error = errorB;
	}

	double output = m_error * Robot::driveSubsystem->driveTurnProportional.Get();
	Robot::driveSubsystem->setMotorSpeed(output, -output);
}

bool DriveGyroController::isDone() {
	return (abs(m_error) < m_tolerance);
}
