#include "Robot.h"

using namespace CORE;

CORE2017* Robot = nullptr;

CORE2017::CORE2017() :
		driveSubsystem(),
		hopperSubsystem(),
		climberSubsystem(),
		gearSubsystem(),
		driverJoystick(0),
		operatorJoystick(1) {
	Robot = this;
}

void CORE2017::robotInit() {

}

void CORE2017::teleopInit() {

}

void CORE2017::teleop(){

}


#ifdef __arm__
START_ROBOT_CLASS(CORE2017)
#else
START_SIMULATED_ROBOT_CLASS(CORE2017)
#endif
