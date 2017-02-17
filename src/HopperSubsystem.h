#pragma once

#include "CORERobotLib.h"
#include "WPILib.h"

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
    void turnOnSweeper();
    void turnOffSweeper();
    void setSweeper(double val);
    bool sweeperIsOn();
    double getLiftSpeed();
    double getLiftEncoder();


private:
    COREMotor m_liftMotor, m_sweepMotor;
    Servo m_leftDumpFlapServo, m_rightDumpFlapServo;
    COREPID m_liftPID;
    COREConstant<double> m_liftBottomPos, m_liftTopPos, m_liftTolerance, m_raiseVel, m_lowerVel, m_flapBottomPos, m_flapTopPos, m_sweepSpeed;
    bool m_flapIsOpen;
};

class IntakeController : public CORETask {
public:
	IntakeController();
	void postLoopTask() override;
	void disabledTask() override;
};

