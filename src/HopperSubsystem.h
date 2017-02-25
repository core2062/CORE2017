#pragma once

#include "CORERobotLib.h"
#include "WPILib.h"

using namespace CORE;

class HopperSubsystem : public CORESubsystem {
public:
    HopperSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void setLiftTop();
    void setLiftBottom();
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
    COREMotionProfile* m_liftController;
    Servo m_leftDumpFlapServo, m_rightDumpFlapServo;
    //COREPID m_liftPID;
    COREConstant<double> m_liftBottomPos, m_liftTopPos, m_liftTolerance, m_raiseVel, m_raiseAccel, m_lowerVel,
						 m_lowerAccel, m_flapTopPos, m_flapBottomPos, m_intakeSpeed;
    bool m_flapIsOpen;
};

class IntakeController : public CORETask {
public:
	IntakeController();
	void postLoopTask() override;
	void disabledTask() override;
};
