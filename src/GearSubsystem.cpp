#include "GearSubsystem.h"
#include "Robot.h"

GearSubsystem::GearSubsystem() : CORESubsystem("Gear"),
								PunchSolenoid(PUNCH_SOLENOID_OPEN_PORT, PUNCH_SOLENOID_CLOSE_PORT),
								FlapMotor(GEAR_FLAP_MOTOR_PORT){

}

void GearSubsystem::robotInit(){
Robot::operatorJoystick->registerButton(X_BUTTON);
//robot::operatorJoystick->registerButton();
}

void GearSubsystem::teleopInit(){

}

void GearSubsystem::teleop(){

}
