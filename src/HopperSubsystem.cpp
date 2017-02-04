#include "HopperSubsystem.h"
#include "Robot.h"

HopperSubsystem::HopperSubsystem() : CORESubsystem("Hopper"), m_liftMotor(LIFT_MOTOR_PORT),
									m_dumpFlapMotor(DUMP_FLAP_MOTOR_PORT),
									m_liftPID(&m_liftMotor, &m_liftMotor, POS_VEL, 0, 0, 0),
									m_bottomPos("Lift Bottom Position", -1.0),
									m_topPos("Lift Top Position", -1.0),
									m_raiseVel("Lift Raise Velocity", -1.0),
									m_lowerVel("Lift Lower Velocity", -1.0) {

}

void HopperSubsystem::robotInit(){
	Robot::operatorJoystick->registerButton(COREJoystick::A_BUTTON);
	Robot::operatorJoystick->registerButton(COREJoystick::Y_BUTTON);
	Robot::operatorJoystick->registerButton(COREJoystick::B_BUTTON);
}

void HopperSubsystem::teleopInit(){

}

void HopperSubsystem::teleop(){
	if (Robot::operatorJoystick->getButtonState(COREJoystick::B_BUTTON) == COREJoystick::RISING_EDGE){
		if (flapIsOpen()){
			closeFlap();
		} else {
			openFlap();
		}
	}

	if (Robot::operatorJoystick->getButtonState(COREJoystick::A_BUTTON) == COREJoystick::RISING_EDGE){
		setLiftBottom();
	} else if (Robot::operatorJoystick->getButtonState(COREJoystick::Y_BUTTON) == COREJoystick::RISING_EDGE){
		setLiftTop();
	}
}

void HopperSubsystem::setLiftTop(){
	m_liftPID.setPos(m_topPos.Get());
	m_liftPID.setVel(m_raiseVel.Get());

}

void HopperSubsystem::setLiftBottom(){
	m_liftPID.setPos(m_bottomPos.Get());
	m_liftPID.setVel(m_lowerVel.Get());

}

void HopperSubsystem::openFlap(){
	m_dumpFlapMotor.Set(DoubleSolenoid::kForward);
}

void HopperSubsystem::closeFlap(){
	m_dumpFlapMotor.Set(DoubleSolenoid::kReverse);
}


bool HopperSubsystem::flapIsOpen(){
	if (m_dumpFlapMotor.Get() == DoubleSolenoid::kForward)
		return true;
	else
		 return false;
}
