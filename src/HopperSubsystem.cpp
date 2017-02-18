#include "HopperSubsystem.h"
#include "Robot.h"

using namespace CORE;

HopperSubsystem::HopperSubsystem() : CORESubsystem("Hopper"),
									 m_liftMotor(LIFT_MOTOR_PORT, VICTOR),
									 m_intakeMotor(INTAKE_MOTOR_PORT, VICTOR),
									 m_leftDumpFlapServo(LEFT_DUMP_FLAP_SERVO_CHANNEL),
									 m_rightDumpFlapServo(RIGHT_DUMP_FLAP_SERVO_CHANNEL),
									 //m_liftPID(m_liftMotor.Encoder.get(), &m_liftMotor, POS_VEL, 0, 0, 0),
									 m_liftBottomPos("Lift Bottom Position", -1.0),
									 m_liftTopPos("Lift Top Position", -1.0),
									 m_liftTolerance("Lift Position Tolerance", -1.0),
									 m_raiseVel("Lift Raise Velocity", -1.0),
									 m_lowerVel("Lift Lower Velocity", -1.0),
									 m_flapBottomPos("Flap Bottom Position", 0),
									 m_flapTopPos("Flap Top Position", 180),
									 m_intakeSpeed("Intake Speed", .5),
									 m_flapIsOpen(false) {
	//m_liftMotor.CANTalonController->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
}

void HopperSubsystem::robotInit(){
	Robot->operatorJoystick.registerButton(COREJoystick::A_BUTTON);
	Robot->operatorJoystick.registerButton(COREJoystick::Y_BUTTON);
	Robot->operatorJoystick.registerButton(COREJoystick::B_BUTTON);
	Robot->operatorJoystick.registerButton(COREJoystick::DPAD_N);
	Robot->operatorJoystick.registerButton(COREJoystick::DPAD_S);
	Robot->operatorJoystick.registerAxis(COREJoystick::LEFT_STICK_Y);
}

void HopperSubsystem::teleopInit(){
	closeFlap();
	setLiftBottom();
}

void HopperSubsystem::teleop(){
	if (Robot->operatorJoystick.getButtonState(COREJoystick::B_BUTTON) == COREJoystick::RISING_EDGE){
		m_flapIsOpen = !m_flapIsOpen;
	}
	if (m_flapIsOpen) {
		closeFlap();
	} else {
		openFlap();
	}

	double liftVal = -Robot->operatorJoystick.getAxis(COREJoystick::LEFT_STICK_Y);
	if(abs(liftVal) > .05){
		setLift(liftVal);
	} else {
		if (Robot->operatorJoystick.getButtonState(COREJoystick::A_BUTTON) == COREJoystick::RISING_EDGE){
			setLiftBottom();
		} else if (Robot->operatorJoystick.getButtonState(COREJoystick::Y_BUTTON) == COREJoystick::RISING_EDGE){
			setLiftTop();
		}
	}

	if(Robot->operatorJoystick.getButton(COREJoystick::DPAD_N)){
		setIntake(-.5);
	}
	if(Robot->operatorJoystick.getButton(COREJoystick::DPAD_S)){
		setIntake(.5);
	}
}

void HopperSubsystem::setLiftTop(){
	/*m_liftPID.disableTasks(false);
	m_liftPID.setPos(m_liftTopPos.Get());
	m_liftPID.setVel(m_raiseVel.Get());*/

}

void HopperSubsystem::setLiftBottom(){
	/*m_liftPID.disableTasks(false);
	m_liftPID.setPos(m_liftBottomPos.Get());
	m_liftPID.setVel(m_lowerVel.Get());*/

}

void HopperSubsystem::setLift(double val){
	/*m_liftPID.disableTasks(true);*/
	//m_liftMotor.Set(val);

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
}
bool HopperSubsystem::hopperIsDown(){
	/*return (m_liftPID.getPos() < m_liftBottomPos.Get() + m_liftTolerance.Get() * 1.1);*/
}

void HopperSubsystem::turnOnIntake() {
	setIntake(m_intakeSpeed.Get());
}

void HopperSubsystem::turnOffIntake() {
	setIntake(0.0);
}

void HopperSubsystem::setIntake(double val) {
	//m_intakeMotor.Set(val);
}

bool HopperSubsystem::intakeIsOn() {
	//return (m_intakeMotor.Get() > 0);
}

double HopperSubsystem::getLiftSpeed() {
	//return m_liftMotor.CANTalonController->GetSpeed();
}

double HopperSubsystem::getLiftEncoder() {
	//return m_liftMotor.Get();
}

IntakeController::IntakeController() : CORETask(){
	std::cout << "Intake Controller Added" << std::endl;
}

void IntakeController::postLoopTask() {
	if(Robot->operatorJoystick.getButton(COREJoystick::DPAD_N) || Robot->operatorJoystick.getButton(COREJoystick::DPAD_S)){
		return;
	}
	double pow = 0; //Robot->driveSubsystem.getForwardPower();
	if(pow > 0){
//		if(Robot->hopperSubsystem.hopperIsDown()){
//			Robot->hopperSubsystem.setIntake(pow + .1);
//		}
	}
}

void IntakeController::disabledTask() {
	//Robot->hopperSubsystem.setIntake(0.0);
}
