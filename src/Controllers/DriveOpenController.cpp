#include "DriveOpenController.h"
#include "Robot.h"

DriveOpenController::DriveOpenController() : COREController(){
}

void DriveOpenController::robotInitTask() {
	 Robot->driverJoystick.registerButton(COREJoystick::LEFT_BUTTON);
	 Robot->driverJoystick.registerAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	 Robot->driverJoystick.registerAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_X);
}

void DriveOpenController::enabledLoop() {

//	std::cout << "Gyro Angle: " << Robot->driveSubsystem.getGyroAngle().getDegrees() << std::endl;
//	std::cout << "Gyro Update Rate: " << Robot->driveSubsystem.getGyro()->GetActualUpdateRate() << std::endl;
//	std::pair<double, double> vels = Robot->driveSubsystem.getEncoderSpeed();
//	std::cout << "Left Speed: " << vels.first << std::endl;
//	std::cout << "Right Speed: " << vels.second << std::endl;


	if(Robot->driverJoystick.getRisingEdge(COREJoystick::LEFT_BUTTON)){
		if(Robot->driveSubsystem.getHighGear()){
			Robot->driveSubsystem.setLowGear();
		} else {
			Robot->driveSubsystem.setHighGear();
		}
	}

	double mag = -Robot->driverJoystick.getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	double rot = Robot->driverJoystick.getAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_X);

	VelocityPair speeds = COREEtherDrive::calculate(mag, rot, .1);
	Robot->driveSubsystem.setMotorSpeed(speeds.left, speeds.right);
}
