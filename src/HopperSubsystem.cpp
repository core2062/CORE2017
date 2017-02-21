#include "HopperSubsystem.h"
#include "Robot.h"

using namespace CORE;

HopperSubsystem::HopperSubsystem() : CORESubsystem("Hopper"),
									 m_liftMotor(LIFT_MOTOR_PORT, VICTOR),
									 m_intakeMotor(INTAKE_MOTOR_PORT, VICTOR),
									 m_leftDumpFlapServo(LEFT_DUMP_FLAP_SERVO_CHANNEL),
									 m_rightDumpFlapServo(RIGHT_DUMP_FLAP_SERVO_CHANNEL),
									 //m_liftPID(m_liftMotor.m_encoder.get(), &m_liftMotor, POS_VEL, 0, 0, 0),
									 m_liftBottomPos("Lift Bottom Position", 0),
									 m_liftTopPos("Lift Top Position", 0),
									 m_liftTolerance("Lift Position Tolerance", -1.0),
									 m_raiseVel("Lift Raise Velocity", 0.1),
									 m_raiseAccel("Lift Raise Acceleration", 0.1),
									 m_lowerVel("Lift Lower Velocity", -1.0),
									 m_lowerAccel("Lift Lower Acceleration", -1.0),
									 m_flapTopPos("Flap Top Position", 0.1),
									 m_flapBottomPos("Flap Bottom Position", 0.5),
									 m_intakeSpeed("Intake Speed", .5),
									 m_flapIsOpen(false) {
	//m_liftMotor.m_CANTalonController->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	m_liftMotor.setReversed(true);
	m_intakeMotor.setReversed(true);
}

void HopperSubsystem::robotInit(){
	Robot->operatorJoystick.registerButton(COREJoystick::A_BUTTON);
	Robot->operatorJoystick.registerButton(COREJoystick::Y_BUTTON);
	Robot->operatorJoystick.registerButton(COREJoystick::B_BUTTON);
	Robot->operatorJoystick.registerButton(COREJoystick::DPAD_N);
	Robot->operatorJoystick.registerButton(COREJoystick::DPAD_S);
	Robot->operatorJoystick.registerAxis(COREJoystick::RIGHT_STICK_Y);
	Robot->operatorJoystick.registerAxis(COREJoystick::LEFT_STICK_Y);
	cout << "Hopper Robot Init" << endl;
}

void HopperSubsystem::teleopInit(){
//	m_liftController.setMaxVel(m_raiseVel.Get());
//	m_liftController.setMaxAccel(m_raiseAccel.Get());
	closeFlap();
	setLiftBottom();
	cout << "Initializing Lift Controller... ";
	m_liftController = new COREMotionProfile(m_raiseVel.Get(), m_raiseAccel.Get());
	cout << "Done!" << endl;
}

void HopperSubsystem::teleop() {
	m_liftController->setActual(Robot->climberSubsystem.getLiftEncoderMotor()->GetEncPosition());
	if (Robot->operatorJoystick.getButtonState(COREJoystick::B_BUTTON) == COREJoystick::RISING_EDGE){
		m_flapIsOpen = !m_flapIsOpen;
	}
	if (m_flapIsOpen) {
		closeFlap();
	} else {
		openFlap();
	}

	double liftVal = -Robot->operatorJoystick.getAxis(COREJoystick::RIGHT_STICK_Y);
	if(abs(liftVal) > .05){
		if(liftVal > 0 && Robot->gearSubsystem.flapIsOpen()){
			setLift(0);
		} else {
			setLift(liftVal);
		}
	} else {
		setLift(0);
		if (Robot->operatorJoystick.getButtonState(COREJoystick::A_BUTTON) == COREJoystick::RISING_EDGE){
			setLiftBottom();
		} else if (Robot->operatorJoystick.getButtonState(COREJoystick::Y_BUTTON) == COREJoystick::RISING_EDGE){
			setLiftTop();
		}
	}
	double intakeVal = Robot->operatorJoystick.getAxis(COREJoystick::LEFT_STICK_Y);
	if(Robot->operatorJoystick.getButton(COREJoystick::JoystickButton::DPAD_N)){
		setIntake(1.0);
	} else if(Robot->operatorJoystick.getButton(COREJoystick::JoystickButton::DPAD_S)){
		setIntake(-1.0);
	}
	if (fabs(intakeVal) > .1 ){
		setIntake(intakeVal);
	}
	m_liftController->update(1);
	m_liftMotor.Set(m_liftController->Get());

}

void HopperSubsystem::setLiftTop(){
	m_liftController->Set(m_liftTopPos.Get());
}

void HopperSubsystem::setLiftBottom(){
	m_liftController->Set(m_liftBottomPos.Get());
}

void HopperSubsystem::setLift(double val){
	/*m_liftPID.disableTasks(true);*/
	m_liftMotor.Set(val);

}

void HopperSubsystem::openFlap(){
	m_rightDumpFlapServo.Set(0);
	m_leftDumpFlapServo.Set(1);
}

void HopperSubsystem::closeFlap(){
	m_rightDumpFlapServo.Set(.5);
	m_leftDumpFlapServo.Set(.5);
}

bool HopperSubsystem::hopperIsUp(){
	/*return (m_liftPID.getPos() == m_liftTopPos.Get() &&
			(m_liftPID.getVel() == 0));*/
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
}

double HopperSubsystem::getLiftSpeed() {
	//return m_liftMotor.m_CANTalonController->GetSpeed();
}

double HopperSubsystem::getLiftEncoder() {
	//return m_liftMotor.Get();
}

IntakeController::IntakeController() : CORETask() {
	CORELog::logInfo("Intake Controller Added");
}

void IntakeController::postLoopTask() {
	if((Robot->operatorJoystick.getButton(COREJoystick::DPAD_N) || Robot->operatorJoystick.getButton(COREJoystick::DPAD_S)) || (fabs(Robot->operatorJoystick.getAxis(COREJoystick::LEFT_STICK_Y) > .1))){
		return;
	}
	double pow = Robot->driveSubsystem.getForwardPower();
	if(pow > 0){
		if(Robot->hopperSubsystem.hopperIsDown()){
			pow = (pow > .4) ? .4:pow;
			Robot->hopperSubsystem.setIntake(pow + .1);
		} else {
			Robot->hopperSubsystem.setIntake(0);
		}
	} else {
		Robot->hopperSubsystem.setIntake(0);
	}
}

void IntakeController::disabledTask() {
	//Robot->hopperSubsystem.setIntake(0.0);
}
