#pragma once

#include "CORERobotLib.h"
#include "WPILib.h"

using namespace CORE;

class HopperSubsystem : public CORESubsystem, public CORETask {
public:
	enum hopperState {
		INTAKE_BALLS, //When we want to intake balls
		HOLD_BALLS, //When we want to hold balls in hopper
		DUMP, //When we want to dump and in the range of the intake
		SHAKE, //When we are dumping and want to shake dump flap and lift
		MANUAL //When the lift height is manually controlled by a joystick
	};
    HopperSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void setLiftTop();
    void setLiftBottom();
    void setLiftHold();
    void setLiftPos(double height);
    void setLift(double val);
    void openFlap();
    void closeFlap();
    bool hopperIsUp();
    bool hopperIsDown();
    void turnOnIntake();
    void turnOffIntake();
    void setIntake(double val);
    bool intakeIsOn();
    double getLiftSpeed();
    double getLiftEncoder();
    bool flapIsOpen();
    void setRequestedState(hopperState requestedState);
    hopperState getHopperState();
    void postLoopTask();

private:
    COREMotor m_liftMotor, m_intakeMotor;
    Servo m_leftDumpFlapServo, m_rightDumpFlapServo;
    COREConstant<double> m_liftBottomPos, m_liftHoldPos, m_liftTopPos, m_intakeSpeed, m_liftPIDUp_P,
	m_liftPIDUp_I, m_liftPIDUp_D, m_liftPIDDown_P, m_liftPIDDown_I, m_liftPIDDown_D, m_shakeFrequency;
    COREPID m_liftPID;
    AnalogInput m_stringPot;
    int m_lastPressedButton;
    hopperState m_requestedHopperState;
	hopperState m_actualHopperState;
	CORETimer m_shakeTimer;
	enum pidProfileDirection {
		UP = 1,
		DOWN = 2
	};
    bool m_flapIsOpen;
};
