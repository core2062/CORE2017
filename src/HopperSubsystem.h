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
    void openFlap();
    void closeFlap();
    bool flapIsOpen();
    bool flapIsClosed();
    bool hopperIsUp();
    bool hopperIsDown();
    void turnOnSweeper();
    void turnOffSweeper();
    bool sweeperIsOn();


private:
    COREMotor m_liftMotor, m_sweepMotor;
    Servo m_leftDumpFlapServo, m_rightDumpFlapServo;
    COREPID m_liftPID;
    COREConstant<double> m_liftBottomPos, m_liftTopPos, m_raiseVel, m_lowerVel, m_flapBottomPos, m_flapTopPos;
    bool m_flapIsOpen;
};

