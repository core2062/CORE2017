#include "HopperSubsystem.h"
#include "Robot.h"

using namespace CORE;

HopperSubsystem::HopperSubsystem() : CORESubsystem("Hopper"),
									 m_liftMotor(LIFT_MOTOR_PORT, VICTOR),
									 m_intakeMotor(INTAKE_MOTOR_PORT, VICTOR),
									 m_leftDumpFlapServo(LEFT_DUMP_FLAP_SERVO_CHANNEL),
									 m_rightDumpFlapServo(RIGHT_DUMP_FLAP_SERVO_CHANNEL),
									 m_liftBottomPos("Lift Bottom Position", 100),
									 m_liftTopPos("Lift Top Position", 1000000),
									 m_liftRaiseVel("Lift Raise Velocity", 0.25),
									 m_liftLowerVel("Lift Lower Velocity", 0.75),
									 m_liftTolerance("Lift Position Tolerance", -1.0),
									 m_flapTopPos("Flap Top Position", 180),
									 m_flapBottomPos("Flap Bottom Position", 0),
									 m_intakeSpeed("Intake Speed", .5),
									 m_liftPID_P("Lift PID Up P Value", 0),
									 m_liftPID_I("Lift PID Up I Value", 0),
									 m_liftPID_D("Lift PID Up D Value", 0),
									 m_liftPID_Pa("Lift PID Down P Value", 0),
									 m_liftPID_Ia("Lift PID Down I Value", 0),
									 m_liftPID_Da("Lift PID Down D Value", 0),
//									 m_bottomLimit(LIFT_BOTTOM_LIMIT_SWITCH_PORT),
//									 m_topLimit(LIFT_TOP_LIMIT_SWITCH_PORT),
//									 m_liftPID(POS, m_liftPID_P.Get(), m_liftPID_I.Get(), m_liftPID_P.Get()),
									 m_flapIsOpen(false) {
	//m_liftMotor.getCANTalon()->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
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
	m_liftPID.PPos = m_liftPID_P.Get();
	m_liftPID.IPos = m_liftPID_I.Get();
	m_liftPID.DPos = m_liftPID_D.Get();
	m_liftPID.PNeg = m_liftPID_Pa.Get();
	m_liftPID.INeg = m_liftPID_Ia.Get();
	m_liftPID.DNeg = m_liftPID_Da.Get();

	m_liftPID.start(m_liftBottomPos.Get());
}

void HopperSubsystem::teleop(){
	m_liftPID.updateTime();

//	m_liftPID.setActualPos(Robot->climberSubsystem.getLiftEncoderMotor()->GetEncPosition());
	SmartDashboard::PutNumber("Lift Encoder", Robot->climberSubsystem.getLiftEncoderMotor()->GetEncPosition());
	if (Robot->operatorJoystick.getButtonState(COREJoystick::B_BUTTON) == COREJoystick::RISING_EDGE){
		m_flapIsOpen = !m_flapIsOpen;
	}
	if (m_flapIsOpen) {
		closeFlap();
	} else {
		openFlap();
	}

	double liftVal = -Robot->operatorJoystick.getAxis(COREJoystick::LEFT_STICK_Y);
	double liftEnc = Robot->climberSubsystem.getLiftEncoderMotor()->GetEncPosition();
	if(fabs(liftVal) > .05){
//		setLift(liftVal);
		m_liftPID.start(Robot->climberSubsystem.getLiftEncoderMotor()->GetEncPosition());
	} else {
		if (Robot->operatorJoystick.getButton(COREJoystick::A_BUTTON)){
//			setLiftBottom();
//			liftVal = m_liftPID.calculate(Robot->climberSubsystem.getLiftEncoderMotor()->GetEncPosition());
//			setLift(liftVal);
			double error = abs(liftEnc - m_liftBottomPos.Get());
			liftVal = -1.0;
			if(error < 30000){
				liftVal*=.5;
			}
			if(error < 15000){
				liftVal*=.5;
			}
		} else if (Robot->operatorJoystick.getButton(COREJoystick::Y_BUTTON)){
//			setLiftTop();
//			liftVal = m_liftPID.calculate(Robot->climberSubsystem.getLiftEncoderMotor()->GetEncPosition());
//			setLift(liftVal);
			double error = abs(liftEnc - m_liftTopPos.Get());
			liftVal = 1.0;
			if(error < 30000){
				liftVal*=.5;
			}
			if(error < 15000){
				liftVal*=.5;
			}
		} else {
			liftVal = 0;
//			setLift(0.0);
		}
	}

//	if(liftVal > 0 && m_topLimit.Get()){
//		liftVal = 0.0;
//	} else if (liftVal < 0 && m_bottomLimit.Get()){
//		liftVal = 0.0;
//	}
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

//	double liftSpeed = m_liftPID.calculate();
//    if(liftSpeed > 0 && (liftSpeed > m_liftRaiseVel.Get())) {
//        liftSpeed = m_liftRaiseVel.Get();
//    } else if (liftSpeed < 0 && (-liftSpeed > m_liftLowerVel.Get())) {
//        liftSpeed = -m_liftLowerVel.Get();
//    }
//    m_liftMotor.Set(liftSpeed);
}

void HopperSubsystem::setLiftTop(){
//	m_liftPID.disableTasks(false);
	m_liftPID.start(m_liftTopPos.Get());
}

void HopperSubsystem::setLiftBottom(){
//	m_liftPID.disableTasks(false);
	m_liftPID.start(m_liftBottomPos.Get());
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
	m_rightDumpFlapServo.Set(1);
	m_leftDumpFlapServo.Set(0);
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

	if(Robot->hopperSubsystem.getLiftSpeed()>0){
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
