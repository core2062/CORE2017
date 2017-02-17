#pragma once
#include "WPILib.h"
#include "CORERobotLib.h"

using namespace CORE;

class ClimberSubsystem : public CORESubsystem {
public:
    ClimberSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
private:
    COREMotor m_leftClimbMotor, m_rightClimbMotor;
    COREConstant<double> m_climbMotorCurrentLimit;
    DigitalInput m_climbLimitSwitch;
    bool m_climbing;


    bool isClimbing();
    void startClimbing();
    void stopClimbing();
    void setClimber(double val);
};
