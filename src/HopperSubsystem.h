#pragma once

#include "CORERobotLib.h"
#include "WPILib.h"

using namespace CORE;

class HopperSubsystem : public CORESubsystem {
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
    void setLiftIntake();
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


private:
    COREMotor m_liftMotor, m_intakeMotor;
    //COREMotionProfile* m_liftController;
    Servo m_leftDumpFlapServo, m_rightDumpFlapServo;
    COREConstant<double> m_liftBottomPos, m_liftTopPos, m_liftHoldPos, m_intakeSpeed, m_liftPIDUp_P,
	m_liftPIDUp_I, m_liftPIDUp_D, m_liftPIDDown_P, m_liftPIDDown_I, m_liftPIDDown_D;
    COREPID m_liftPID;
    AnalogInput m_stringPot;
    int m_lastPresedButton;
    hopperState m_requestedHopperState;
	hopperState m_actualHopperState;

//    DigitalInput m_bottomLimit;
//    DigitalInput m_topLimit;
	enum pidProfileDirection {
		UP = 1,
		DOWN = 2
	};
    bool m_flapIsOpen;
};

class IntakeController : public CORETask {
public:
	IntakeController();
	void postLoopTask() override;
	void disabledTask() override;
};
