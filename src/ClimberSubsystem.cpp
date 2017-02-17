#include "ClimberSubsystem.h"
#include "Robot.h"

ClimberSubsystem::ClimberSubsystem() : CORESubsystem("Climber"),
										m_leftClimbMotor(LEFT_CLIMB_MOTOR_PORT),
										m_rightClimbMotor(RIGHT_CLIMB_MOTOR_PORT),
										m_climbMotorCurrentLimit("Climber Current Limit",-1),
										m_climbLimitSwitch(CLIMB_LIMIT_SWITCH_PORT),
										m_climbing(false){

}

void ClimberSubsystem::robotInit() {
	Robot::operatorJoystick->registerButton(COREJoystick::START_BUTTON);
	m_leftClimbMotor.setReversed(true);
	m_rightClimbMotor.setReversed(false);
}

void ClimberSubsystem::teleopInit() {
	m_climbing = false;
}

void ClimberSubsystem::teleop() {

	double leftCurrent = m_leftClimbMotor.getCurrent();
	double rightCurrent = m_rightClimbMotor.getCurrent();
	double currentLimit = m_climbMotorCurrentLimit.Get();
	if (Robot::operatorJoystick->getButtonState(COREJoystick::START_BUTTON) == COREJoystick::RISING_EDGE){
		if(isClimbing()){
			stopClimbing();
		}else{
			startClimbing();
		}
	}
	if (leftCurrent > currentLimit || rightCurrent > currentLimit){
			stopClimbing();
	}
	if (m_climbLimitSwitch.Get()) {
			stopClimbing();
	}

	if (isClimbing()){
		setClimber(1.0);
	} else {
		setClimber(0.0);
	}
}

bool ClimberSubsystem::isClimbing(){
	return m_climbing;
}

void ClimberSubsystem::startClimbing(){
    m_climbing = true;
}

void ClimberSubsystem::stopClimbing(){
    m_climbing = false;
}

void ClimberSubsystem::setClimber(double val) {
	m_leftClimbMotor.Set(val);
	m_rightClimbMotor.Set(val);
}
