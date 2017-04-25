#include "ClimberSubsystem.h"
#include "Robot.h"

using namespace CORE;

ClimberSubsystem::ClimberSubsystem() : CORESubsystem("Climber"),
										m_leftClimbMotor(LEFT_CLIMB_MOTOR_PORT, CANTALON, PERCENTAGE),
										m_rightClimbMotor(RIGHT_CLIMB_MOTOR_PORT, CANTALON, PERCENTAGE),
										m_climbMotorCurrentLimit("Climber Current Limit",-1),
										m_climbLimitSwitch(CLIMB_LIMIT_SWITCH_PORT),
										m_climbing(false){
	shared_ptr<CANTalon> liftEncoder = m_leftClimbMotor.getCANTalon();
	liftEncoder->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	liftEncoder->SetSensorDirection(false);
	liftEncoder->ConfigEncoderCodesPerRev(1024);
}

void ClimberSubsystem::robotInit() {
	Robot->operatorJoystick.registerButton(COREJoystick::START_BUTTON);
	Robot->operatorJoystick.registerAxis(COREJoystick::RIGHT_STICK_Y);
	m_leftClimbMotor.setReversed(true);
	m_rightClimbMotor.setReversed(false);
}

void ClimberSubsystem::teleopInit() {
	m_climbing = false;
	m_leftClimbMotor.getCANTalon()->SetEncPosition(0);
}

void ClimberSubsystem::teleop() {
//	std::cout << "Lift Position" << m_leftClimbMotor.getCANTalon()->GetPosition() << std::endl;;
//	double leftCurrent = m_leftClimbMotor.getCurrent();
//	double rightCurrent = m_rightClimbMotor.getCurrent();
//	double currentLimit = m_climbMotorCurrentLimit.Get();
	if (Robot->operatorJoystick.getButtonState(COREJoystick::START_BUTTON) == COREJoystick::RISING_EDGE){
		if(isClimbing()){
			stopClimbing();
		} else {
			startClimbing();
		}
	}
	//if (leftCurrent > currentLimit || rightCurrent > currentLimit){
//			stopClimbing();
//	}
//	if (m_climbLimitSwitch.Get()) {
//			stopClimbing();
//	}

	if (isClimbing()){
		setClimber(1.0);
		m_climberOn = true;
		Robot->hopperSubsystem.disableIntake();
	} else {
		double stick = Robot->operatorJoystick.getAxis(COREJoystick::RIGHT_STICK_Y);
		stick = fabs(stick);
		if(stick > .1){
			m_climberOn = true;
			Robot->hopperSubsystem.disableIntake();
			setClimber(stick);
		}else {
			Robot->hopperSubsystem.enableIntake();
			m_climberOn = false;
			setClimber(0);
		}
	}
}

shared_ptr<COREEncoder> ClimberSubsystem::getLiftEncoder() {
	cout << "Getting lift encoder" << endl;
	return m_leftClimbMotor.getEncoder();
}

shared_ptr<CANTalon> ClimberSubsystem::getLiftEncoderMotor() {
	return m_leftClimbMotor.getCANTalon();
}

bool ClimberSubsystem::isClimbing() {
	return m_climbing;
}

void ClimberSubsystem::startClimbing() {
    m_climbing = true;
}

void ClimberSubsystem::stopClimbing() {
    m_climbing = false;
}

void ClimberSubsystem::setClimber(double val) {
	m_leftClimbMotor.Set(val);
	m_rightClimbMotor.Set(val);
}
