#include "HopperSubsystem.h"
#include "Robot.h"

using namespace CORE;

HopperSubsystem::HopperSubsystem() : CORESubsystem("Hopper"),
									 m_liftMotor(LIFT_MOTOR_PORT, VICTOR),
									 m_intakeMotor(INTAKE_MOTOR_PORT, VICTOR),
									 m_leftDumpFlapServo(LEFT_DUMP_FLAP_SERVO_CHANNEL),
									 m_rightDumpFlapServo(RIGHT_DUMP_FLAP_SERVO_CHANNEL),
									 m_liftBottomPos("Lift Bottom Position", 1220),
									 m_liftHoldPos("Lift Hold Position", 1320),
									 m_liftTopPos("Lift Top Position", 3450),
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
									 m_requestedHopperState(MANUAL),
									 m_flapIsOpen(false) {
}

void HopperSubsystem::robotInit(){
	Robot->operatorJoystick.registerButton(COREJoystick::A_BUTTON);
	Robot->operatorJoystick.registerButton(COREJoystick::Y_BUTTON);
	Robot->operatorJoystick.registerButton(COREJoystick::B_BUTTON);
    Robot->operatorJoystick.registerButton(COREJoystick::X_BUTTON);
	Robot->operatorJoystick.registerButton(COREJoystick::DPAD_N);
	Robot->operatorJoystick.registerButton(COREJoystick::DPAD_S);
	Robot->operatorJoystick.registerAxis(COREJoystick::LEFT_STICK_Y);
	Robot->operatorJoystick.registerAxis(COREJoystick::RIGHT_STICK_Y);
	m_liftMotor.setDeadband(0.1);
}

void HopperSubsystem::teleopInit(){
	closeFlap();
	setLiftBottom();
	m_liftPID.setP(m_liftPIDUp_P.Get(), POS, UP);
	m_liftPID.setI(m_liftPIDUp_I.Get(), POS, UP);
	m_liftPID.setD(m_liftPIDUp_D.Get(), POS, UP);
	m_liftPID.setP(m_liftPIDDown_P.Get(), POS, DOWN);
	m_liftPID.setI(m_liftPIDDown_I.Get(), POS, DOWN);
	m_liftPID.setD(m_liftPIDDown_D.Get(), POS, DOWN);
}

void HopperSubsystem::teleop() {
/*	//m_liftPID.updateTime();

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
	}*/

    if(Robot->operatorJoystick.getRisingEdge(COREJoystick::A_BUTTON)) {
        m_lastPresedButton = COREJoystick::A_BUTTON;
    } else if (Robot->operatorJoystick.getRisingEdge(COREJoystick::Y_BUTTON)) {
        m_lastPresedButton = COREJoystick::Y_BUTTON;
    }

	if(abs(Robot->operatorJoystick.getAxis(COREJoystick::RIGHT_STICK_Y)) > 0.05) {
		m_requestedHopperState = MANUAL;
        m_lastPresedButton = -1;
	} else if (Robot->operatorJoystick.getButton(COREJoystick::X_BUTTON)) {
        m_requestedHopperState = SHAKE;
    } else if(m_lastPresedButton == COREJoystick::A_BUTTON
              || (Robot->driveSubsystem.getForwardPower() > 0
                  || Robot->operatorJoystick.getButton(COREJoystick::DPAD_S))) {
        m_requestedHopperState = INTAKE_BALLS;
	} else if(m_lastPresedButton == COREJoystick::A_BUTTON
              && (!Robot->driveSubsystem.getForwardPower() > 0
                  && !Robot->operatorJoystick.getButton(COREJoystick::DPAD_S))) {
        m_requestedHopperState = HOLD_BALLS;
    } else if(m_lastPresedButton == COREJoystick::Y_BUTTON) {
        m_requestedHopperState = DUMP;
    } else {
        m_requestedHopperState = MANUAL;
        m_lastPresedButton = -1;
    }

	double liftHeight = m_stringPot.GetValue();
	m_liftPID.setActualPos(liftHeight);

	switch(m_requestedHopperState) {
	case INTAKE_BALLS:
		setLiftBottom();
        setIntake(Robot->driveSubsystem.getForwardPower() + 0.1);
		break;
	case HOLD_BALLS:
		setLiftIntake();
		turnOffIntake();
		break;
	case DUMP:
		Robot->gearSubsystem.closeFlap();
		if(liftHeight > m_liftHoldPos.Get()) { //In intake zone
			turnOnIntake();
		} else { //Above intake zone
			turnOffIntake();
		}
		setLiftTop();
		break;
	case SHAKE:
		//TODO: Figure out best way to shake
		break;
	case MANUAL:
		m_liftPID.setPos(liftHeight);
        if(abs(Robot->operatorJoystick.getAxis(COREJoystick::RIGHT_STICK_Y)) < 0.05) {
            setLift(m_liftPID.calculate());
        } else {
            setLift(Robot->operatorJoystick.getAxis(COREJoystick::RIGHT_STICK_Y));
        }
        if(Robot->driveSubsystem.getForwardPower() > 0) {
			setIntake(Robot->driveSubsystem.getForwardPower() + 0.1);
		} else {
			setIntake(0);
		}

		if(Robot->operatorJoystick.getAxis(COREJoystick::RIGHT_STICK_Y) > 0) {
			Robot->gearSubsystem.closeFlap();
		}
		break;
	}
	if(Robot->operatorJoystick.getButton(COREJoystick::DPAD_N)){
		setIntake(-.5);
	} else if(Robot->operatorJoystick.getButton(COREJoystick::DPAD_S)){
		setIntake(.5);
	}
	m_actualHopperState = m_requestedHopperState;

}

void HopperSubsystem::setLiftTop() {
	m_liftPID.setPos(m_liftTopPos.Get());
	if(m_stringPot.GetValue() > m_liftTopPos.Get()) { //Need to go down
		setLift(m_liftPID.calculate(DOWN));
	} else { //Need to go up
		setLift(m_liftPID.calculate(UP));
	}
}

void HopperSubsystem::setLiftBottom() {
	m_liftPID.setPos(m_liftBottomPos.Get());
	if(m_stringPot.GetValue() > m_liftBottomPos.Get()) { //Need to go down
		setLift(m_liftPID.calculate(DOWN));
	} else { //Need to go up
		setLift(m_liftPID.calculate(UP));
	}
}

void HopperSubsystem::setLiftIntake() {
	m_liftPID.setPos(m_liftHoldPos.Get());
	if(m_stringPot.GetValue() > m_liftHoldPos.Get()) { //Need to go down
		setLift(m_liftPID.calculate(DOWN));
	} else { //Need to go up
		setLift(m_liftPID.calculate(UP));
	}
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

}

void IntakeController::disabledTask() {
	Robot->hopperSubsystem.setIntake(0.0);
}

bool HopperSubsystem::flapIsOpen() {
	return m_flapIsOpen;
}

