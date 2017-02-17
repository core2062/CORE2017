#include "Robot.h"

shared_ptr<DriveSubsystem> Robot::driveSubsystem = make_shared<DriveSubsystem>();
shared_ptr<HopperSubsystem> Robot::hopperSubsystem = make_shared<HopperSubsystem>();
shared_ptr<ClimberSubsystem> Robot::climberSubsystem = make_shared<ClimberSubsystem>();
shared_ptr<GearSubsystem> Robot::gearSubsystem = make_shared<GearSubsystem>();
shared_ptr<COREJoystick> Robot::driverJoystick = make_shared<COREJoystick>(0);
shared_ptr<COREJoystick> Robot::operatorJoystick = make_shared<COREJoystick>(1);
shared_ptr<DriveOpenController> Robot::driveTeleopController = make_shared<DriveOpenController>();
shared_ptr<DriveGyroController> Robot::driveGyroController = make_shared<DriveGyroController>();
shared_ptr<IntakeController> Robot::intakeController = make_shared<IntakeController>();

Robot::Robot() {

}

void Robot::robotInit() {

}
void Robot::teleopInit() {

}
void Robot::teleop(){

}
void Robot::Test(){

	//Lift Test Code
	double liftVal = 0.0;
	if(operatorJoystick->getButton(CORE::COREJoystick::JoystickButton::DPAD_N)){
		liftVal += .25;
	}
	if(operatorJoystick->getButton(CORE::COREJoystick::JoystickButton::DPAD_S)){
		liftVal -=.25;
	}
	double oldLiftVal = liftVal;
	double liftDeltaEnc = hopperSubsystem->getLiftSpeed();
	if(abs(((liftDeltaEnc > 0) - (liftDeltaEnc < 0)) - ((oldLiftVal > 0) - (oldLiftVal < 0))) == 2){
		std::cout << "Encoder speed and power don't match!" << std::endl;
	}
	hopperSubsystem->setLift(liftVal);

	//Servo Flap Code
	if(operatorJoystick->getButton(CORE::COREJoystick::JoystickButton::A_BUTTON)){
		hopperSubsystem->openFlap();
	} else {
		hopperSubsystem->closeFlap();
	}

	//Pneumatic Flap Code
	if(operatorJoystick->getButton(CORE::COREJoystick::JoystickButton::B_BUTTON)){
		gearSubsystem->openFlap();
	} else {
		gearSubsystem->closeFlap();
	}

	//Intake Code
	if(operatorJoystick->getButton(CORE::COREJoystick::JoystickButton::LEFT_BUTTON)){
		hopperSubsystem->setSweeper(.5);
	} else if(operatorJoystick->getButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)){
		hopperSubsystem->setSweeper(-.5);
	} else {
		hopperSubsystem->turnOffSweeper();
	}

	//Climber Code
	double climbUpVal = abs(operatorJoystick->getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y));
	double climbDownVal = abs(operatorJoystick->getAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y));
	climbUpVal *= .25;
	climbDownVal *= .25;
	climberSubsystem->setClimber(climbUpVal - climbDownVal);

	double left = -driverJoystick->getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	double right = -driverJoystick->getAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y);

	double oldLeft = left;
	double oldRight = right;
	std::pair<double, double> driveSpeed = driveSubsystem->getEncoderSpeed();

	if(abs(((driveSpeed.first > 0) - (driveSpeed.first < 0)) - ((oldLeft > 0) - (oldLeft < 0))) == 2){
		std::cout << "Left Drive Encoder speed and power don't match!" << std::endl;
	}
	if(abs(((driveSpeed.second > 0) - (driveSpeed.second < 0)) - ((oldRight > 0) - (oldRight < 0))) == 2){
		std::cout << "Right Drive Encoder speed and power don't match!" << std::endl;
	}

	driveSubsystem->setMotorSpeed(left, right);

}

#ifdef __arm__
START_ROBOT_CLASS(Robot)
#else
START_SIMULATED_ROBOT_CLASS(offSeasonRobot)
#endif
