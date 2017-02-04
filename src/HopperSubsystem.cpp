#include "HopperSubsystem.h"
#include "Robot.h"

HopperSubsystem::HopperSubsystem() : CORESubsystem("Hopper"), m_liftMotor(LIFT_MOTOR_PORT),
									m_dumpFlapMotor(DUMP_FLAP_MOTOR_PORT),
									m_liftPID(&m_liftMotor, &m_liftMotor, POS_VEL, 0, 0, 0),
									m_liftBottomPos("Lift Bottom Position", -1.0),
									m_liftTopPos("Lift Top Position", -1.0),
									m_raiseVel("Lift Raise Velocity", -1.0),
									m_lowerVel("Lift Lower Velocity", -1.0),
									m_flapBottomPos("Flap Bottom Position", -1.0),
									m_flapTopPos("Flap Bottom Position", -1.0),
									m_flapPID(&m_dumpFlapMotor, &m_dumpFlapMotor, POS, 0, 0, 0),
									m_flapIsOpen(false){

}

void HopperSubsystem::robotInit(){
	Robot::operatorJoystick->registerButton(COREJoystick::A_BUTTON);
	Robot::operatorJoystick->registerButton(COREJoystick::Y_BUTTON);
	Robot::operatorJoystick->registerButton(COREJoystick::B_BUTTON);
}

void HopperSubsystem::teleopInit(){

}

void HopperSubsystem::teleop(){
	if(Robot::operatorJoystick->getButtonState(COREJoystick::B_BUTTON) == COREJoystick::OFF ||
	   Robot::operatorJoystick->getButtonState(COREJoystick::A_BUTTON) == COREJoystick::OFF ||
	   Robot::operatorJoystick->getButtonState(COREJoystick::Y_BUTTON) == COREJoystick::OFF){
		m_liftMotor.Set(0);
		m_dumpFlapMotor.Set(0);
	}

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
	m_liftPID.setPos(m_liftTopPos.Get());
	m_liftPID.setVel(m_raiseVel.Get());

}

void HopperSubsystem::setLiftBottom(){
	m_liftPID.setPos(m_liftBottomPos.Get());
	m_liftPID.setVel(m_lowerVel.Get());

}

void HopperSubsystem::openFlap(){
	//m_dumpFlapMotor.Set(DoubleSolenoid::kForward);
	m_flapPID.setPos(m_flapBottomPos.Get());
	m_flapIsOpen = true;

}

void HopperSubsystem::closeFlap(){
	//m_dumpFlapMotor.Set(DoubleSolenoid::kReverse);
	m_flapPID.setPos(m_flapTopPos.Get());
	m_flapIsOpen = false;
}


bool HopperSubsystem::flapIsOpen(){
	if (m_flapIsOpen)
		return true;
	else
		 return false;
}
