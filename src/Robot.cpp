#include "Robot.h"

using namespace CORE;

CORE2017* Robot = nullptr;

CORE2017::CORE2017() :
		driveSubsystem(),
		hopperSubsystem(),
		climberSubsystem(),
		gearSubsystem(),
		driveTeleController(),
		driveGyroController(),
		intakeController(),
		driverJoystick(0),
		operatorJoystick(1)
{
	Robot = this;
}

void CORE2017::robotInit() {
	setLoopTime(1/60.0);

}

void CORE2017::teleopInit() {

	if(driveWaypointController == nullptr){
		driveWaypointController = new DriveWaypointController();
	}

	driveSubsystem.setController(&driveTeleController);
	driveTeleController.enable();

}

void CORE2017::teleop(){

//	testMotor.Set(0);
//	CORELog::logInf//o("m_encoder Pos: " + to_string(testMotor.m_encoder->GetEncPos()));
//	CORELog::logInfo("m_encoder Vel: " + to_string(testMotor.m_encoder->GetEncVel()));
//	CORELog::logInfo("m_encoder Accel: " + to_string(testMotor.m_encoder->GetEncAccel()));

}


#ifdef __arm__
START_ROBOT_CLASS(CORE2017)
#else
START_SIMULATED_ROBOT_CLASS(CORE2017)
#endif
