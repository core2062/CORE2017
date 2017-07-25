#include "Robot.h"

using namespace CORE;

Aergia * Robot = nullptr;

Aergia::Aergia() :
		driveSubsystem(),
		climberSubsystem(),
		hopperSubsystem(),
		gearSubsystem(),
		visionSubsystem(),
		driverJoystick(0),
		operatorJoystick(1),
		driveForwardAuton(0,0),
		gearAuton(StartingPosition::CENTER),
		gearBoilerAuton(),
		gearHopperBoilerAuton()
	{
	Robot = this;
}

void Aergia::robotInit() {
	setLoopTime(.025);
	m_positionChooser.AddDefault("Center", new StartingPosition(StartingPosition::CENTER));
	m_positionChooser.AddObject("Boiler", new StartingPosition(StartingPosition::BOILER));
	m_positionChooser.AddObject("Feeder", new StartingPosition(StartingPosition::FEEDER));
	SmartDashboard::PutData("Starting Position", &m_positionChooser);
	SmartDashboard::PutBoolean("Auto Cross Field", false);
	SmartDashboard::PutBoolean("Use Vision", false);
	SmartDashboard::PutBoolean("Two Gear Boiler", false);
	SmartDashboard::PutBoolean("Vision Set Heading", false);
	SmartDashboard::PutBoolean("Tele Init Drive", false);
}


void Aergia::autonInit() {
	driveSubsystem.setFrame(nullptr);
	driveSubsystem.softResetYaw();

	StartingPosition * pos = m_positionChooser.GetSelected();
	switch(*pos){
	case (StartingPosition::BOILER):
		driveSubsystem.setPos(Position2d(Translation2d(-19,236 * CORERobot::getAlliance()), Rotation2d::fromDegrees(0)));
		break;
	case (StartingPosition::CENTER):
		driveSubsystem.setPos(Position2d(Translation2d(-19,162 * CORERobot::getAlliance()), Rotation2d::fromDegrees(0)));
		break;
	case (StartingPosition::FEEDER):
		driveSubsystem.setPos(Position2d(Translation2d(-19,102 * CORERobot::getAlliance()), Rotation2d::fromDegrees(0)));
		break;
	}
}

void Aergia::teleopInit() {


}

void Aergia::teleop(){
//	testMotor.Set(0);
//	CORELog::logInf//o("m_encoder Pos: " + to_string(testMotor.m_encoder->GetEncPos()));
//	CORELog::logInfo("m_encoder Vel: " + to_string(testMotor.m_encoder->GetEncVel()));
//	CORELog::logInfo("m_encoder Accel: " + to_string(testMotor.m_encoder->GetEncAccel()));

}

void Aergia::test(){
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

	driveSubsystem.setMotors();

}


Aergia::~Aergia() {
	delete Robot;
	Robot = nullptr;
	CORELog::logInfo("Robot successfully deleted");
}

#ifdef __arm__
START_ROBOT_CLASS(Aergia)
#else
START_SIMULATED_ROBOT_CLASS(Aergia)
#endif
