#include "GearSubsystem.h"
#include "Robot.h"

using namespace CORE;

GearSubsystem::GearSubsystem() : CORESubsystem("Gear"),
								m_punchSolenoid(PUNCH_SOLENOID_OPEN_PORT, PUNCH_SOLENOID_CLOSE_PORT){

}

void GearSubsystem::robotInit() {
	Robot->operatorJoystick.registerButton(COREJoystick::X_BUTTON);
	//m_gearFlapMotor.setReversed(false);
}

void GearSubsystem::teleopInit() {

}

void GearSubsystem::teleop(){
	if (Robot->operatorJoystick.getButtonState(COREJoystick::X_BUTTON) == COREJoystick::RISING_EDGE) {
		if (flapIsOpen()){
			closeFlap();
		}else{
			openFlap();
		}
	}

}
void GearSubsystem::openFlap(){
	//m_gearFlapPID.setPos(m_gearFlapBottomPos.Get());
}

void GearSubsystem::closeFlap(){
	//m_gearFlapPID.setPos(m_gearFlapTopPos.Get());
}


bool GearSubsystem::flapIsOpen(){
//	if (m_gearFlapMotor.Get() == 1.0)
//		return true;
//	else
//		 return false;
}
