#include "HopperSubsystem.h"
#include "Robot.h"

HopperSubsystem::HopperSubsystem() : CORESubsystem("Hopper"), m_liftMotor(LIFT_MOTOR_PORT),
									m_sweepMotor(SWEEP_MOTOR_PORT),
									m_leftDumpFlapServo(LEFT_DUMP_FLAP_SERVO_CHANNEL),
									m_rightDumpFlapServo(RIGHT_DUMP_FLAP_SERVO_CHANNEL),
									m_liftPID(&m_liftMotor, &m_liftMotor, POS_VEL, 0, 0, 0),
									m_liftBottomPos("Lift Bottom Position", -1.0),
									m_liftTopPos("Lift Top Position", -1.0),
									m_liftTolerance("Lift Position Tolerance", -1.0),
									m_raiseVel("Lift Raise Velocity", -1.0),
									m_lowerVel("Lift Lower Velocity", -1.0),
									m_flapBottomPos("Flap Bottom Position", -1.0),
									m_flapTopPos("Flap Bottom Position", -1.0),
									m_sweepSpeed("Sweeper Speed", .5),
									m_flapIsOpen(false){
	m_liftMotor.CANTalonController->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
}

void HopperSubsystem::robotInit(){
	Robot::operatorJoystick->registerButton(COREJoystick::A_BUTTON);
	Robot::operatorJoystick->registerButton(COREJoystick::Y_BUTTON);
	Robot::operatorJoystick->registerButton(COREJoystick::B_BUTTON);
	Robot::operatorJoystick->registerButton(COREJoystick::DPAD_N);
	Robot::operatorJoystick->registerButton(COREJoystick::DPAD_S);
	Robot::operatorJoystick->registerAxis(COREJoystick::LEFT_STICK_Y);
}

void HopperSubsystem::teleopInit(){
	closeFlap();
	setLiftBottom();
}

void HopperSubsystem::teleop(){

	if (Robot::operatorJoystick->getButtonState(COREJoystick::B_BUTTON) == COREJoystick::RISING_EDGE){
		m_flapIsOpen = !m_flapIsOpen;
	}
	if (m_flapIsOpen){
		closeFlap();
	} else {
		openFlap();
	}

	double liftVal = -Robot::operatorJoystick->getAxis(COREJoystick::LEFT_STICK_Y);
	if(abs(liftVal) > .05){
		setLift(liftVal);
	}else{
		if (Robot::operatorJoystick->getButtonState(COREJoystick::A_BUTTON) == COREJoystick::RISING_EDGE){
			setLiftBottom();
		} else if (Robot::operatorJoystick->getButtonState(COREJoystick::Y_BUTTON) == COREJoystick::RISING_EDGE){
			setLiftTop();
		}
	}

	if(Robot::operatorJoystick->getButton(COREJoystick::DPAD_N)){
		setSweeper(-.5);
	}
	if(Robot::operatorJoystick->getButton(COREJoystick::DPAD_S)){
		setSweeper(.5);
	}
}

void HopperSubsystem::setLiftTop(){
	m_liftPID.disableTasks(false);
	m_liftPID.setPos(m_liftTopPos.Get());
	m_liftPID.setVel(m_raiseVel.Get());

}

void HopperSubsystem::setLiftBottom(){
	m_liftPID.disableTasks(false);
	m_liftPID.setPos(m_liftBottomPos.Get());
	m_liftPID.setVel(m_lowerVel.Get());

}

void HopperSubsystem::setLift(double val){
	m_liftPID.disableTasks(true);
	m_liftMotor.Set(val);

}

void HopperSubsystem::openFlap(){
	m_rightDumpFlapServo.SetAngle(m_flapBottomPos.Get());
	m_leftDumpFlapServo.SetAngle(m_flapBottomPos.Get());
	m_flapIsOpen = true;

}

void HopperSubsystem::closeFlap(){
	m_rightDumpFlapServo.SetAngle(m_flapTopPos.Get());
	m_leftDumpFlapServo.SetAngle(m_flapTopPos.Get());
	m_flapIsOpen = false;
}

bool HopperSubsystem::hopperIsUp(){
	return (m_liftPID.getPos() == m_liftTopPos.Get() &&
			(m_liftPID.getVel() == 0));
}
bool HopperSubsystem::hopperIsDown(){
	return (m_liftPID.getPos() < m_liftBottomPos.Get() + m_liftTolerance.Get() * 1.1);
}

void HopperSubsystem::turnOnSweeper() {
	setSweeper(m_sweepSpeed.Get());
}

void HopperSubsystem::turnOffSweeper() {
	setSweeper(0.0);
}

void HopperSubsystem::setSweeper(double val){
	m_sweepMotor.Set(val);
}

bool HopperSubsystem::sweeperIsOn() {
	return (m_sweepMotor.Get() > 0);
}

double HopperSubsystem::getLiftSpeed() {
	return m_liftMotor.CANTalonController->GetSpeed();
}

double HopperSubsystem::getLiftEncoder() {
	return m_liftMotor.Get();
}

IntakeController::IntakeController() : CORETask(){
}

void IntakeController::postLoopTask() {
	if(Robot::operatorJoystick->getButton(COREJoystick::DPAD_N) || Robot::operatorJoystick->getButton(COREJoystick::DPAD_S)){
		return;
	}
	double pow = Robot::driveSubsystem->getForwardPower();
	if(pow > 0){
		if(Robot::hopperSubsystem->hopperIsDown()){
			Robot::hopperSubsystem->setSweeper(pow + .1);
		}
	}
}

void IntakeController::disabledTask() {
	Robot::hopperSubsystem->setSweeper(0.0);
}
