#include "HopperSubsystem.h"
#include "Robot.h"

using namespace CORE;

HopperSubsystem::HopperSubsystem() : liftGearFlapPos("Lift Gear Flap Position", 2930),
									 m_liftMotor(LIFT_MOTOR_PORT, VICTOR),
									 m_leftDumpFlapServo(LEFT_DUMP_FLAP_SERVO_CHANNEL),
									 m_rightDumpFlapServo(RIGHT_DUMP_FLAP_SERVO_CHANNEL),
									 m_liftBottomPos("Lift Bottom Position", 1180),
									 m_liftHoldPos("Lift Hold Position", 1220),
									 m_liftIntakePos("Lift Intake Position", 2215),
									 m_liftTopPos("Lift Top Position", 3465),
									 m_intakeSpeed("Intake Speed", 1),
									 m_liftPIDUp_P("Lift PID Up P Value", 0.007),
									 m_liftPIDUp_I("Lift PID Up I Value", 0),
									 m_liftPIDUp_D("Lift PID Up D Value", 0.0006),
									 m_liftPIDDown_P("Lift PID Down P Value", 0.007),
									 m_liftPIDDown_I("Lift PID Down I Value", 0),
									 m_liftPIDDown_D("Lift PID Down D Value", 0.0005),
									 m_shakeFrequency("Hopper Shake Frequency", 0.5),
									 m_liftPID(0, 0, 0),
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

	m_liftPID.setProportionalConstant(m_liftPIDUp_P.Get());
	m_liftPID.setIntegralConstant(m_liftPIDUp_I.Get());
	m_liftPID.setDerivativeConstant(m_liftPIDUp_D.Get());
	m_liftPID.setProportionalConstant(m_liftPIDDown_P.Get());
	m_liftPID.setIntegralConstant(m_liftPIDDown_I.Get());
	m_liftPID.setDerivativeConstant(m_liftPIDDown_D.Get());
}

void HopperSubsystem::teleopInit(){
	closeFlap();
	setLiftBottom();
	m_requestedHopperState = HOLD_BALLS;
	m_upProfile.kP = m_liftPIDUp_P.Get();
	m_upProfile.kI = m_liftPIDUp_I.Get();
	m_upProfile.kD = m_liftPIDUp_D.Get();
	m_downProfile.kP = m_liftPIDDown_P.Get();
	m_downProfile.kI = m_liftPIDDown_I.Get();
	m_downProfile.kD = m_liftPIDDown_D.Get();
}

void HopperSubsystem::teleop() {
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
	if(m_stringPot.GetValue() > height) { //Need to go down
		m_liftPID.setPIDProfile(m_downProfile);
		setLift(m_liftPID.calculate(getLiftPos(), height));
	} else { //Need to go up
		m_liftPID.setPIDProfile(m_upProfile);
		setLift(m_liftPID.calculate(getLiftPos(), height));
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
	double range = m_liftTopPos.Get() - m_liftBottomPos.Get();
	return (fabs((m_stringPot.GetValue() - m_liftTopPos.Get()) / range) < .05);
}
bool HopperSubsystem::hopperIsDown(){
	/*return (m_liftPID.getPos() < m_liftBottomPos.Get() + m_liftTolerance.Get() * 1.1);*/
	return true;
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

void HopperSubsystem::autonInitTask(){
	Robot->gearSubsystem.closeFlap();
}

void HopperSubsystem::postLoopTask() {
    double liftHeight = m_stringPot.GetValue();
    SmartDashboard::PutNumber("Lift Pot", liftHeight);
    switch(m_requestedHopperState) {
        case INTAKE_BALLS:
            setLiftBottom();
            break;
        case HOLD_BALLS:
            setLiftHold();
            break;
        case DUMP:
            Robot->gearSubsystem.closeFlap();
            setLiftTop();
            break;
        case SHAKE:
        	setLiftPos(liftGearFlapPos.Get());
            break;
        case MANUAL:
            if(abs(Robot->operatorJoystick.getAxis(COREJoystick::LEFT_STICK_Y)) < 0.05) {
                setLift(m_liftPID.calculate(getLiftPos(), liftHeight));
            } else {
                setLift(-Robot->operatorJoystick.getAxis(COREJoystick::LEFT_STICK_Y));
            }
            break;
    }

    if(liftHeight > m_liftTopPos.Get() && m_liftMotor.Get() > 0) { //Top limit
    	m_liftMotor.Set(0);
    } else if(liftHeight < m_liftBottomPos.Get() && m_liftMotor.Get() < 0) { //Bottom limit
    	m_liftMotor.Set(0);
    }
    if(((((m_lastLiftHeight + 30) < liftHeight) && m_actualHopperState != HOLD_BALLS) && m_actualHopperState != INTAKE_BALLS) && m_liftMotor.Get() > 0) {
		Robot->gearSubsystem.closeFlap();
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

