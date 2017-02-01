#include "HopperSubsystem.h"
#include "Robot.h"

HopperSubsystem::HopperSubsystem() : CORESubsystem("Hopper"), liftMotor(LIFT_MOTOR_PORT),
									dumpFlap(DUMP_FLAP_SOLENOID_OPEN_PORT, DUMP_FLAP_SOLENOID_CLOSE_PORT),
									liftPID(&liftMotor, &liftMotor, POS_VEL, 0, 0, 0),
									m_bottomPos("Lift Bottom Position", -1), m_topPos("Lift Top Position", -1),
									m_raiseVel("Lift Raise Velocity", -1), m_lowerVel("Lift Lower Velocity", -1){

}

void HopperSubsystem::robotInit(){
	Robot::operatorJoystick->registerButton(A_BUTTON);
	Robot::operatorJoystick->registerButton(Y_BUTTON);
	Robot::operatorJoystick->registerButton(B_BUTTON);
}

void HopperSubsystem::teleopInit(){

}

void HopperSubsystem::teleop(){
	if (Robot::operatorJoystick->getButtonState(B_BUTTON) == PRESSED){
		if (flapIsOpen()){
			closeFlap();
		} else {
			openFlap();
		}
	}

	if (Robot::operatorJoystick->getButtonState(A_BUTTON) == PRESSED){
		setLiftBottom();
	} else if (Robot::operatorJoystick->getButtonState(Y_BUTTON) == PRESSED){
		setLiftTop();
	}
}

void HopperSubsystem::setLiftTop(){
	liftPID.setPos(m_topPos.Get());
	liftPID.setVel(m_raiseVel.Get());

}

void HopperSubsystem::setLiftBottom(){
	liftPID.setPos(m_bottomPos.Get());
	liftPID.setVel(m_lowerVel.Get());

}

void HopperSubsystem::openFlap(){
	dumpFlap.Set(DoubleSolenoid::kForward);
}

void HopperSubsystem::closeFlap(){
	dumpFlap.Set(DoubleSolenoid::kReverse);
}


bool HopperSubsystem::flapIsOpen(){
	if (dumpFlap.Get() == DoubleSolenoid::kForward)
		return true;
	else
		 return false;
}
