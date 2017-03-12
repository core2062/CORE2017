#include "HopperSubsystem.h"
#include "Robot.h"

using namespace CORE;

HopperSubsystem::HopperSubsystem() : CORESubsystem("Hopper"),
									 m_liftMotor(LIFT_MOTOR_PORT, VICTOR),
									 m_intakeMotor(INTAKE_MOTOR_PORT, VICTOR),
									 m_leftDumpFlapServo(LEFT_DUMP_FLAP_SERVO_CHANNEL),
									 m_rightDumpFlapServo(RIGHT_DUMP_FLAP_SERVO_CHANNEL),
									 m_liftBottomPos("Lift Bottom Position", 1250),
									 m_liftTopPos("Lift Top Position", 3420),
									 m_liftHoldPos("Lift Hold Position", 1350),
									 m_intakeSpeed("Intake Speed", .5),
									 m_liftPIDUp_P("Lift PID Up P Value", 0.001),
									 m_liftPIDUp_I("Lift PID Up I Value", 0),
									 m_liftPIDUp_D("Lift PID Up D Value", 0),
									 m_liftPIDDown_P("Lift PID P Down Value", 0.0075),
									 m_liftPIDDown_I("Lift PID I Down Value", 0),
									 m_liftPIDDown_D("Lift PID D Down Value", 0),
									 /*m_liftPID(POS, m_liftPIDUp_P.Get(), m_liftPIDUp_I.Get(), m_liftPIDUp_D.Get(), 1,
											 m_liftPIDDown_P.Get(), m_liftPIDDown_I.Get(), m_liftPIDDown_D.Get()),*/
									 m_liftPID(POS, 0, 0, 0, 1, 0, 0, 0, 1),
									 m_stringPot(0),
//									 m_bottomLimit(LIFT_BOTTOM_LIMIT_SWITCH_PORT),
//									 m_topLimit(LIFT_TOP_LIMIT_SWITCH_PORT),
									 m_flapIsOpen(false) {
}

void HopperSubsystem::robotInit(){
	Robot->operatorJoystick.registerButton(COREJoystick::A_BUTTON);
	Robot->operatorJoystick.registerButton(COREJoystick::Y_BUTTON);
	Robot->operatorJoystick.registerButton(COREJoystick::B_BUTTON);
	Robot->operatorJoystick.registerButton(COREJoystick::DPAD_N);
	Robot->operatorJoystick.registerButton(COREJoystick::DPAD_S);
	Robot->operatorJoystick.registerAxis(COREJoystick::LEFT_STICK_Y);
	Robot->operatorJoystick.registerAxis(COREJoystick::RIGHT_STICK_Y);
}

void HopperSubsystem::teleopInit(){
	closeFlap();
	setLiftBottom();
	m_liftPID.setP(m_liftPIDUp_P.Get(), POS, 1);
	m_liftPID.setI(m_liftPIDUp_I.Get(), POS, 1);
	m_liftPID.setD(m_liftPIDUp_D.Get(), POS, 1);
	m_liftPID.setP(m_liftPIDDown_P.Get(), POS, 2);
	m_liftPID.setI(m_liftPIDDown_I.Get(), POS, 2);
	m_liftPID.setD(m_liftPIDDown_D.Get(), POS, 2);
}

void HopperSubsystem::teleop() {
	//m_liftPID.updateTime();
	m_liftPID.setActualPos(m_stringPot.GetValue());

//	m_liftPID.setActualPos(Robot->climberSubsystem.getLiftEncoderMotor()->GetEncPosition());
	SmartDashboard::PutNumber("Lift Encoder", Robot->climberSubsystem.getLiftEncoderMotor()->GetEncPosition());
	SmartDashboard::PutNumber("Lift Pot", m_stringPot.GetValue());
	if (Robot->operatorJoystick.getButtonState(COREJoystick::B_BUTTON) == COREJoystick::RISING_EDGE){
		m_flapIsOpen = !m_flapIsOpen;
	}
	if (m_flapIsOpen) {
		closeFlap();
	} else {
		openFlap();
	}

	double liftVal = -Robot->operatorJoystick.getAxis(COREJoystick::LEFT_STICK_Y);
	if(fabs(liftVal) > .05){
		m_liftPID.setPos(m_stringPot.GetValue());
		if (liftVal > 0.05 && (Robot->gearSubsystem.flapIsOpen())){
			Robot->gearSubsystem.closeFlap();
		}

	} else {
		if (Robot->operatorJoystick.getButton(COREJoystick::A_BUTTON)){
			if(m_intakeMotor.GetLast() != 0){
				setLiftIntake();
			} else {
				setLiftBottom();
			}
			liftVal = m_liftPID.calculate(2);
		} else if (Robot->operatorJoystick.getButton(COREJoystick::Y_BUTTON)) {
			setLiftTop();
			liftVal = m_liftPID.calculate(1);
		} else {
			m_liftPID.setPos(m_stringPot.GetValue());
			liftVal = 0;
		}
	}
	SmartDashboard::PutNumber("Lift Speed", liftVal);
	setLift(liftVal);


	if(Robot->operatorJoystick.getButton(COREJoystick::DPAD_N)){
		setIntake(-.5);
	}
	if(Robot->operatorJoystick.getButton(COREJoystick::DPAD_S)){
		setIntake(.5);
	}
	double intakeVal = -Robot->operatorJoystick.getAxis(COREJoystick::RIGHT_STICK_Y);
	if(fabs(intakeVal) > .05){
		setIntake(intakeVal);
	}

}

void HopperSubsystem::setLiftTop(){
//	m_liftPID.disableTasks(false);
	m_liftPID.setPos(m_liftTopPos.Get());
}

void HopperSubsystem::setLiftBottom(){
//	m_liftPID.disableTasks(false);
	m_liftPID.setPos(m_liftBottomPos.Get());
}

void HopperSubsystem::setLiftIntake(){
	m_liftPID.setPos(m_liftHoldPos.Get());
}

void HopperSubsystem::setLift(double val){
//	m_liftPID.disableTasks(true);
	m_liftMotor.Set(val);

}

void HopperSubsystem::openFlap(){
	m_rightDumpFlapServo.Set(0);
	m_leftDumpFlapServo.Set(1);

}

void HopperSubsystem::closeFlap(){
	m_rightDumpFlapServo.Set(.43);
	m_leftDumpFlapServo.Set(.57);
}

bool HopperSubsystem::hopperIsUp(){
	/*return (m_liftPID.getPos() == m_liftTopPos.Get() &&
			(m_liftPID.getVel() == 0));*/
	return true;
}
bool HopperSubsystem::hopperIsDown(){
	/*return (m_liftPID.getPos() < m_liftBottomPos.Get() + m_liftTolerance.Get() * 1.1);*/
	return true;
}

void HopperSubsystem::turnOnIntake() {
	setIntake(m_intakeSpeed.Get());
}

void HopperSubsystem::turnOffIntake() {
	setIntake(0.0);
}

void HopperSubsystem::setIntake(double val) {
	m_intakeMotor.Set(val);
}

bool HopperSubsystem::intakeIsOn() {
	//return (m_intakeMotor.Get() > 0);
	return false;
	//TODO Fill this in
}

double HopperSubsystem::getLiftSpeed() {
	return Robot->climberSubsystem.getLiftEncoderMotor()->GetSpeed();
	//return m_liftMotor.CANTalonController->GetSpeed();

}

double HopperSubsystem::getLiftEncoder() {
	//return m_liftMotor.Get();
	return false;
	//TODO Fill this in
}

IntakeController::IntakeController() : CORETask(){
	std::cout << "Intake Controller Added" << std::endl;
}

void IntakeController::postLoopTask() {

	if((Robot->operatorJoystick.getButton(COREJoystick::DPAD_N) || Robot->operatorJoystick.getButton(COREJoystick::DPAD_S)) || fabs(Robot->operatorJoystick.getAxis(COREJoystick::RIGHT_STICK_Y)) > .05){
		return;
	}

	if(Robot->hopperSubsystem.getLiftSpeed() > 0) {
		Robot->hopperSubsystem.setIntake(0.5);
		return;
	}

	double pow = Robot->driveSubsystem.getForwardPower();
	if(pow > 0){
//		if(Robot->hopperSubsystem.hopperIsDown()){
			Robot->hopperSubsystem.setIntake(pow + .1);
//		}
	} else {
			Robot->hopperSubsystem.setIntake(0);
	}
}

void IntakeController::disabledTask() {
	Robot->hopperSubsystem.setIntake(0.0);
}

bool HopperSubsystem::flapIsOpen() {
	return m_flapIsOpen;
}

