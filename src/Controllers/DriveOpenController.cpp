#include "DriveOpenController.h"
#include "Robot.h"
#include "CORERobotLib.h"

DriveOpenController::DriveOpenController() : COREController(){
}

void DriveOpenController::robotInitTask() {
	 Robot->driverJoystick.registerButton(COREJoystick::LEFT_BUTTON);
	 Robot->driverJoystick.registerAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	 Robot->driverJoystick.registerAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_X);
	 Robot->driverJoystick.registerButton(CORE::COREJoystick::START_BUTTON);
}

void DriveOpenController::enabledLoop() {

//	std::cout << "Gyro Angle: " << Robot->driveSubsystem.getGyroAngle().getDegrees() << std::endl;
	SmartDashboard::PutNumber("Gyro Yaw", Robot->driveSubsystem.getGyroAngle().getDegrees());
//	std::cout << "Gyro Update Rate: " << Robot->driveSubsystem.getGyro()->GetActualUpdateRate() << std::endl;
//	std::pair<double, double> vels = Robot->driveSubsystem.getEncoderSpeed();
//	std::cout << "Left Speed: " << vels.first << std::endl;
//	std::cout << "Right Speed: " << vels.second << std::endl;
//	SmartDashboard::PutNumber("Left Speed", vels.first);
//	SmartDashboard::PutNumber("Right Speed", vels.second);

	if(Robot->driverJoystick.getRisingEdge(COREJoystick::START_BUTTON)){
		Robot->driveSubsystem.hardResetYaw();
	}

	double mag = -Robot->driverJoystick.getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	double rot = Robot->driverJoystick.getAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_X);

	if((SmartDashboard::GetBoolean("Auto Cross Field", false) && SmartDashboard::GetBoolean("Tele Init Drive", false))){
		if(fabs(mag) < .1 && fabs(rot) < .1){
			mag = -1.0;
		} else {
			SmartDashboard::PutBoolean("Tele Init Drive", false);
		}
	}

	if(Robot->driverJoystick.getButton(CORE::COREJoystick::RIGHT_BUTTON)){
		mag *=.5;
		rot *=.5;
	}

	VelocityPair speeds = COREEtherDrive::calculate(mag, rot, .1);
	Robot->driveSubsystem.setMotors();
}

void DriveOpenController::autonEndTask() {
}

void DriveOpenController::teleopEndTask() {
}
