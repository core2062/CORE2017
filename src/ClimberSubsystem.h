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
    shared_ptr<COREEncoder> getLiftEncoder();
    shared_ptr<CANTalon> getLiftEncoderMotor();
    void setClimber(double val);
    bool isClimbing();

private:
    COREMotor m_leftClimbMotor, m_rightClimbMotor;
    COREConstant<double> m_climbMotorCurrentLimit;
    DigitalInput m_climbLimitSwitch;
    bool m_climbing;
    bool m_climberOn = false;

    void startClimbing();
    void stopClimbing();

};
