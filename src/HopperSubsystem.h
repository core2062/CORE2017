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


private:
    COREMotor m_liftMotor;
    Servo m_leftDumpFlapServo, m_rightDumpFlapServo;
    COREPID m_liftPID;
    COREConstant<double> m_liftBottomPos, m_liftTopPos, m_raiseVel, m_lowerVel, m_flapBottomPos, m_flapTopPos;
    COREPID m_flapPID;
    bool m_flapIsOpen;
};

