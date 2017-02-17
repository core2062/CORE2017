#include "Robot.h"

using namespace CORE;

CORE2017* Robot = nullptr;

CORE2017::CORE2017() :testMotor(78),
		driveSubsystem(),
		//hopperSubsystem(),
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
	testMotor.getCurrent();
	//TestSubsystem.teleop();
//	cout << testMotor.Encoder.get() << endl;
//	cout << testMotor.getName()  << endl;
}


//shared_ptr<DriveSubsystem> Robot::driveSubsystem = make_shared<DriveSubsystem>();
//shared_ptr<HopperSubsystem> Robot::hopperSubsystem = make_shared<HopperSubsystem>();
//shared_ptr<ClimberSubsystem> Robot::climberSubsystem = make_shared<ClimberSubsystem>();
//shared_ptr<GearSubsystem> Robot::gearSubsystem = make_shared<GearSubsystem>();
////testSubsystem TestSubsystem;
//
//shared_ptr<COREJoystick> CORE2017::driverJoystick = make_shared<COREJoystick>(0);
//shared_ptr<COREJoystick> CORE2017::operatorJoystick = make_shared<COREJoystick>(1);


#ifdef __arm__
START_ROBOT_CLASS(CORE2017)
#else
START_SIMULATED_ROBOT_CLASS(CORE2017)
#endif
