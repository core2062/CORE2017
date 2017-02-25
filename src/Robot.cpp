#include "Robot.h"

using namespace CORE;

//shared_ptr<CORE2017> Robot = nullptr;
CORE2017 * Robot = nullptr;

CORE2017::CORE2017() :
		driveSubsystem(),
		climberSubsystem(),
		hopperSubsystem(),
		gearSubsystem(),
		intakeController(),
		driverJoystick(0),
		operatorJoystick(1) {
//	Robot.shared_ptr(this);
	Robot = this;
}

void CORE2017::robotInit() {
	setLoopTime(.0125);

}

void CORE2017::teleopInit() {



}

void CORE2017::teleop(){

//	testMotor.Set(0);
//	CORELog::logInf//o("m_encoder Pos: " + to_string(testMotor.m_encoder->GetEncPos()));
//	CORELog::logInfo("m_encoder Vel: " + to_string(testMotor.m_encoder->GetEncVel()));
//	CORELog::logInfo("m_encoder Accel: " + to_string(testMotor.m_encoder->GetEncAccel()));

}

void CORE2017::test(){
	//Lift Test Code
		double liftVal = 0.0;
		if(operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::DPAD_N)){
			liftVal += .25;
		}
		if(operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::DPAD_S)){
			liftVal -=.25;
		}
		double oldLiftVal = liftVal;
		double liftDeltaEnc = hopperSubsystem.getLiftSpeed();
		if(abs(((liftDeltaEnc > 0) - (liftDeltaEnc < 0)) - ((oldLiftVal > 0) - (oldLiftVal < 0))) == 2){
			std::cout << "Encoder speed and power don't match!" << std::endl;
		}
		hopperSubsystem.setLift(liftVal);

		//Servo Flap Code
		if(operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::A_BUTTON)){
			hopperSubsystem.openFlap();
		} else {
			hopperSubsystem.closeFlap();
		}

		//Pneumatic Flap Code
		if(operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::B_BUTTON)){
			gearSubsystem.openFlap();
		} else {
			gearSubsystem.closeFlap();
		}

		//Intake Code
		if(operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::LEFT_BUTTON)){
			hopperSubsystem.setIntake(.5);
		} else if(operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)){
			hopperSubsystem.setIntake(-.5);
		} else {
			hopperSubsystem.turnOffIntake();
		}

		//Climber Code
		double climbUpVal = abs(operatorJoystick.getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y));
		double climbDownVal = abs(operatorJoystick.getAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y));
		climbUpVal *= .25;
		climbDownVal *= .25;
		climberSubsystem.setClimber(climbUpVal - climbDownVal);

		double left = -driverJoystick.getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
		double right = -driverJoystick.getAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y);

		double oldLeft = left;
		double oldRight = right;
		std::pair<double, double> driveSpeed = driveSubsystem.getEncoderSpeed();


		if(abs(((driveSpeed.first > 0) - (driveSpeed.first < 0)) - ((oldLeft > 0) - (oldLeft < 0))) == 2){
			std::cout << "Left Drive Encoder speed and power don't match!" << std::endl;
		}
		if(abs(((driveSpeed.second > 0) - (driveSpeed.second < 0)) - ((oldRight > 0) - (oldRight < 0))) == 2){
			std::cout << "Right Drive Encoder speed and power don't match!" << std::endl;
		}

	driveSubsystem.setMotorSpeed(left, right);
}

CORE2017::~CORE2017() {
//	Robot.reset();
	delete Robot;
	Robot = nullptr;
}

#ifdef __arm__
START_ROBOT_CLASS(CORE2017)
#else
START_SIMULATED_ROBOT_CLASS(CORE2017)
#endif
