#include "HopperSubsystem.h"
#include "Robot.h"

HopperSubsystem::HopperSubsystem() : CORESubsystem("Hopper"), m_liftMotor(LIFT_MOTOR_PORT),
									m_sweepMotor(SWEEP_MOTOR_PORT),
									m_leftDumpFlapServo(LEFT_DUMP_FLAP_SERVO_CHANNEL),
									m_rightDumpFlapServo(RIGHT_DUMP_FLAP_SERVO_CHANNEL),
									m_liftPID(&m_liftMotor, &m_liftMotor, POS_VEL, 0, 0, 0),
									m_liftBottomPos("Lift Bottom Position", -1.0),
									m_liftTopPos("Lift Top Position", -1.0),
									m_raiseVel("Lift Raise Velocity", -1.0),
									m_lowerVel("Lift Lower Velocity", -1.0),
									m_flapBottomPos("Flap Bottom Position", -1.0),
									m_flapTopPos("Flap Bottom Position", -1.0),
									m_flapIsOpen(false){

}

void HopperSubsystem::robotInit(){
	Robot::operatorJoystick->registerButton(COREJoystick::A_BUTTON);
	Robot::operatorJoystick->registerButton(COREJoystick::Y_BUTTON);
	Robot::operatorJoystick->registerButton(COREJoystick::B_BUTTON);
}

void HopperSubsystem::teleopInit(){
	closeFlap();
	setLiftBottom();
}

void HopperSubsystem::teleop(){
	//TODO:Setting the motors to an initial value belongs in teleopInit instead of teleop?
	/*(Robot::operatorJoystick->getButtonState(COREJoystick::B_BUTTON) == COREJoystick::OFF){
		m_leftDumpFlapServo.Set(0);
		m_rightDumpFlapServo.Set(0);
	}*/

	if (Robot::operatorJoystick->getButtonState(COREJoystick::B_BUTTON) == COREJoystick::RISING_EDGE){
		if (m_flapIsOpen){
			closeFlap();
		} else {
			openFlap();
		}
	}

	//TODO:Setting the motors to an initial value belongs in teleopInit instead of teleop?
	/*if (Robot::operatorJoystick->getButtonState(COREJoystick::A_BUTTON) == COREJoystick::OFF &&
		Robot::operatorJoystick->getButtonState(COREJoystick::Y_BUTTON) == COREJoystick::OFF){
		m_liftMotor.Set(0);
	}*/

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
	m_rightDumpFlapServo.SetAngle(m_flapBottomPos.Get());
	m_leftDumpFlapServo.SetAngle(m_flapBottomPos.Get());
	m_flapIsOpen = true;

}

void HopperSubsystem::closeFlap(){
	//m_dumpFlapMotor.Set(DoubleSolenoid::kReverse);
	m_rightDumpFlapServo.SetAngle(m_flapTopPos.Get());
	m_leftDumpFlapServo.SetAngle(m_flapTopPos.Get());
	m_flapIsOpen = false;
}
bool HopperSubsystem::flapIsOpen(){
	return (m_rightDumpFlapServo.GetAngle() == m_flapTopPos.Get()) &&
		   (m_leftDumpFlapServo.GetAngle() == m_flapTopPos.Get());
}
bool HopperSubsystem::flapIsClosed(){
	return (m_rightDumpFlapServo.GetAngle() == m_flapBottomPos.Get()) &&
			   (m_leftDumpFlapServo.GetAngle() == m_flapBottomPos.Get());
}
bool HopperSubsystem::hopperIsUp(){
	return (m_liftPID.getPos() == m_liftTopPos.Get() &&
			(m_liftPID.getVel() == 0));
}
bool HopperSubsystem::hopperIsDown(){
	return (m_liftPID.getPos() == m_liftBottomPos.Get() &&
				(m_liftPID.getVel() == 0));
}
