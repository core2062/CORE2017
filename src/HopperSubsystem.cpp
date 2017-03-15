#include "HopperSubsystem.h"
#include "Robot.h"

using namespace CORE;

HopperSubsystem::HopperSubsystem() : CORESubsystem("Hopper"),
									 liftGearFlapPos("Lift Gear Flap Position", 3000),
									 m_liftMotor(LIFT_MOTOR_PORT, VICTOR),
									 m_intakeMotor(INTAKE_MOTOR_PORT, VICTOR),
									 m_leftDumpFlapServo(LEFT_DUMP_FLAP_SERVO_CHANNEL),
									 m_rightDumpFlapServo(RIGHT_DUMP_FLAP_SERVO_CHANNEL),
									 m_liftBottomPos("Lift Bottom Position", 1120),
									 m_liftHoldPos("Lift Hold Position", 1320),
									 m_liftIntakePos("Lift Intake Position", 2040),
									 m_liftTopPos("Lift Top Position", 3450),
									 m_intakeSpeed("Intake Speed", .5),
									 m_liftPIDUp_P("Lift PID Up P Value", 0.001),
									 m_liftPIDUp_I("Lift PID Up I Value", 0),
									 m_liftPIDUp_D("Lift PID Up D Value", 0.0006),
									 m_liftPIDDown_P("Lift PID Down P Value", 0.0075),
									 m_liftPIDDown_I("Lift PID Down I Value", 0),
									 m_liftPIDDown_D("Lift PID Down D Value", 0),
									 m_shakeFrequency("Hopper Shake Frequency", 0.5),
									 m_liftPID(POS, 0, 0, 0, 1, 0, 0, 0, 1),
									 m_stringPot(0),
									 m_lastPressedButton(-1),
									 m_requestedHopperState(MANUAL),
									 m_actualHopperState(MANUAL),
									 m_lastLiftHeight(0),
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

/*//	m_liftPID.setActualPos(Robot->climberSubsystem.getLiftEncoderMotor()->GetEncPosition());
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
				setLiftHold();
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
	}/*/

    if(Robot->operatorJoystick.getRisingEdge(COREJoystick::A_BUTTON)) {
        m_lastPressedButton = COREJoystick::A_BUTTON;
        closeFlap();
    } else if (Robot->operatorJoystick.getRisingEdge(COREJoystick::Y_BUTTON)
    		|| Robot->operatorJoystick.getRisingEdge(COREJoystick::X_BUTTON)) {
        m_lastPressedButton = -1;
    }

	if(abs(Robot->operatorJoystick.getAxis(COREJoystick::LEFT_STICK_Y)) > 0.05) {
		m_requestedHopperState = MANUAL;
        m_lastPressedButton = -1;
	} else if (Robot->operatorJoystick.getButton(COREJoystick::X_BUTTON)) {
        m_requestedHopperState = SHAKE;
    } else if(m_lastPressedButton == COREJoystick::A_BUTTON
              && (!Robot->driveSubsystem.getForwardPower() > 0
                  && !Robot->operatorJoystick.getButton(COREJoystick::DPAD_S))) {
        m_requestedHopperState = HOLD_BALLS;
    } else if(m_lastPressedButton == COREJoystick::A_BUTTON
              && (Robot->driveSubsystem.getForwardPower() > 0
                  || Robot->operatorJoystick.getButton(COREJoystick::DPAD_S))) {
        m_requestedHopperState = INTAKE_BALLS;
	} else if(Robot->operatorJoystick.getButton(COREJoystick::Y_BUTTON)) {
        m_requestedHopperState = DUMP;
    } else {
        m_requestedHopperState = MANUAL;
        m_lastPressedButton = -1;
    }

	if(Robot->operatorJoystick.getRisingEdge(COREJoystick::B_BUTTON)) {
		if(m_flapIsOpen) {
			closeFlap();
			m_flapIsOpen = false;
		} else {
			openFlap();
			m_flapIsOpen = true;
		}
	}
	m_liftPID.putToDashboard();
}

void HopperSubsystem::setLiftTop() {
	setLiftPos(m_liftTopPos.Get());
}

void HopperSubsystem::setLiftBottom() {
	setLiftPos(m_liftBottomPos.Get());
}

void HopperSubsystem::setLiftHold() {
	setLiftPos(m_liftHoldPos.Get());
}

void HopperSubsystem::setLiftPos(double height) {
	m_liftPID.setPos(height);
	if(m_stringPot.GetValue() > height) { //Need to go down
		setLift(m_liftPID.calculate(DOWN));
	} else { //Need to go up
		setLift(m_liftPID.calculate(UP));
	}
}

void HopperSubsystem::setLift(double val){
//	m_liftPID.disableTasks(true);
	m_liftMotor.Set(val);

}

void HopperSubsystem::openFlap() {
	m_rightDumpFlapServo.Set(.43);
	m_leftDumpFlapServo.Set(.57);
}

void HopperSubsystem::closeFlap() {
	m_rightDumpFlapServo.Set(0);
	m_leftDumpFlapServo.Set(1);
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

double HopperSubsystem::getLiftPos() {
	return m_stringPot.GetValue();
}

bool HopperSubsystem::flapIsOpen() {
	return m_flapIsOpen;
}

void HopperSubsystem::postLoopTask() {
    double liftHeight = m_stringPot.GetValue();
    m_liftPID.setActualPos(liftHeight);
    SmartDashboard::PutNumber("Lift Pot", liftHeight);
    switch(m_requestedHopperState) {
        case INTAKE_BALLS:
            setLiftBottom();
            setIntake(Robot->driveSubsystem.getForwardPower() + 0.1);
            break;
        case HOLD_BALLS:
            setLiftHold();
            turnOffIntake();
            break;
        case DUMP:
            Robot->gearSubsystem.closeFlap();
            if(liftHeight < 2040) { //In intake zone
                turnOnIntake();
            } else { //Above intake zone
                //turnOffIntake();
                setIntake(-0.2);
            }
            setLiftTop();
            break;
        case SHAKE:
        	setLiftPos(liftGearFlapPos.Get());
            break;
        case MANUAL:
            m_liftPID.setPos(liftHeight);
            if(abs(Robot->operatorJoystick.getAxis(COREJoystick::LEFT_STICK_Y)) < 0.05) {
                setLift(m_liftPID.calculate());
                if(Robot->driveSubsystem.getForwardPower() > 0) {
                    setIntake(Robot->driveSubsystem.getForwardPower() + 0.1);
                } else {
                    setIntake(0);
                }
            } else {
                setLift(-Robot->operatorJoystick.getAxis(COREJoystick::LEFT_STICK_Y));
                if(liftHeight < 2040) { //In intake zone
    				turnOnIntake();
    			} else { //Above intake zone
    				setIntake(-0.2);
    			}
            }
            break;
    }
    if(Robot->operatorJoystick.getButton(COREJoystick::DPAD_N)){
        setIntake(-.5);
    } else if(Robot->operatorJoystick.getButton(COREJoystick::DPAD_S)){
        setIntake(.5);
    }

    if(liftHeight > m_liftTopPos.Get() && m_liftMotor.Get() > 0) { //Top limit
    	m_liftMotor.Set(0);
    } else if(liftHeight < m_liftBottomPos.Get() && m_liftMotor.Get() < 0) { //Bottom limit
    	m_liftMotor.Set(0);
    }
    if((m_lastLiftHeight + 5) < liftHeight) {
		Robot->gearSubsystem.closeFlap();
	}
	if(Robot->driveSubsystem.getForwardPower() > 0 && liftHeight > 2040) {
		setIntake(-0.2);
	}
    m_lastLiftHeight = liftHeight;
    m_actualHopperState = m_requestedHopperState;
}

void HopperSubsystem::setRequestedState(HopperSubsystem::hopperState requestedState) {
    m_requestedHopperState = requestedState;
}

HopperSubsystem::hopperState HopperSubsystem::getHopperState() {
    return m_actualHopperState;
}
