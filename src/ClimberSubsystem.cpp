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
	if (Robot::operatorJoystick->getButtonState(COREJoystick::START_BUTTON) == COREJoystick::OFF){
		m_leftClimbMotor.Set(0);
		m_rightClimbMotor.Set(0);
	}

	double leftCurrent = m_leftClimbMotor.getCurrent();
	double rightCurrent = m_rightClimbMotor.getCurrent();
	double currentLimit = m_climbMotorCurrentLimit.Get();
	if (leftCurrent > currentLimit || rightCurrent > currentLimit){
			stopClimbing();
	}
	if (m_climbLimitSwitch.Get()) {
			stopClimbing();
	}
	if (Robot::operatorJoystick->getButtonState(COREJoystick::START_BUTTON) == COREJoystick::RISING_EDGE){
		startClimbing();
		if (isClimbing()){
		m_leftClimbMotor.Set(1.0);
		m_rightClimbMotor.Set(1.0);
	} else {
		m_leftClimbMotor.Set(0.0);
		m_rightClimbMotor.Set(0.0);
	}

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

