#include "GearSubsystem.h"
#include "Robot.h"

GearSubsystem::GearSubsystem() : CORESubsystem("Gear"),
								m_punchSolenoid(PUNCH_SOLENOID_OPEN_PORT, PUNCH_SOLENOID_CLOSE_PORT),
								m_gearFlapMotor(GEAR_FLAP_MOTOR_PORT){

}

void GearSubsystem::robotInit() {
	Robot::operatorJoystick->registerButton(COREJoystick::X_BUTTON);
	//robot::operatorJoystick->registerButton();
	m_gearFlapMotor.setReversed(false);
}

void GearSubsystem::teleopInit() {

}

void GearSubsystem::teleop(){
	if (Robot::operatorJoystick->getButtonState(COREJoystick::X_BUTTON) == COREJoystick::RISING_EDGE) {
		if (flapIsOpen()){
			closeFlap();
		}else{
			openFlap();
		}
	}

}
void GearSubsystem::openFlap(){
	m_gearFlapMotor.Set(1.0);
}

void GearSubsystem::closeFlap(){
	m_gearFlapMotor.Set(0.0);
}


bool GearSubsystem::flapIsOpen(){
	if (m_gearFlapMotor.Get() == 1.0)
		return true;
	else
		 return false;
}
